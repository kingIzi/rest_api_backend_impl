#include <algorithm>
#include <QUrlQuery>
#include <QJsonObject>
#include "user.hpp"

User::User(QObject *parent)
    : RestApi{parent},
      reply_(nullptr),
      signUpErrorMsg_("")
{

}

const QString User::getEmail() const
{
    return this->authKeys_.value(KEYS::Keys::EMAIL).toString();
}

const QString User::getLocalId() const
{
    return this->authKeys_.value(KEYS::Keys::LOCAL_ID).toString();
}

const QString User::getUserType() const
{
    return this->authKeys_.value(KEYS::Keys::USER_TYPE).toString();
}

QString User::signUpErrorMsg() const
{
    return this->signUpErrorMsg_;
}

QString User::signInErrorMsg() const
{
    return this->signInErrorMsg_;
}

QVariantMap User::userProfile() const
{
    return QVariantMap(this->userProfile_);
}

void User::signUpUser(const QString username, const QString password)
{
    using namespace KEYS;
    enum{EMAIL,PASSWORD,RETURN_SECURE_TOKEN};

    QUrl url(Endpoints::SIGN_UP_WITH_EMAIL_PASSWORD);
    url.setQuery({
                     std::make_pair(QString(Params::KEY),QString(RestApi::FIREBASE_APIKEY))
                 });

    Request request(url);
    request.setHeader(Request::ContentTypeHeader,"application/json");

    const auto document = this->getSignUpDocument(std::make_tuple(username,password,true));
    this->reply_ = ReplyPointer(this->getNetworkAccessManager()->post(request, document.toJson()));

    QObject::connect(this->reply_.get(),&Reply::readyRead,this,[this](){
        const auto reply = qobject_cast<Reply*>(this->sender());
        if (reply){
            const auto doc = QJsonDocument::fromJson(reply->readAll());
            this->parseSignUpResponse(doc.object());
        }
    });
}

void User::signInUser(const QString username, const QString password)
{
    using namespace KEYS;
    enum{EMAIL,PASSWORD,RETURN_SECURE_TOKEN};

    QUrl url(Endpoints::SIGN_UP_WITH_EMAIL_PASSWORD);
    url.setQuery({
                     std::make_pair(QString(Params::KEY),QString(RestApi::FIREBASE_APIKEY))
                 });

    Request request(url);
    request.setHeader(Request::ContentTypeHeader,"application/json");

    const auto document = this->getSignUpDocument(std::make_tuple(username,password,true));
    this->reply_ = ReplyPointer(this->getNetworkAccessManager()->post(request, document.toJson()));

    QObject::connect(this->reply_.get(),&Reply::readyRead,this,[this](){
        const auto reply = qobject_cast<Reply*>(this->sender());
        if (reply){
            const auto doc = QJsonDocument::fromJson(reply->readAll());
            this->parseSignInResponse(doc.object());
            this->loginUser();
        }
    });

    QObject::connect(this->reply_.get(),&Reply::uploadProgress,this,[this](qint64 received,qint64 total){
        qDebug() << "Sign In User Request";
        qDebug() << "Received: " << received << "Total: " << total;
    });
}

void User::setSignUpErrorMsg(const QString &msg)
{
    if (this->signUpErrorMsg_.compare(msg) != 0){
        this->signUpErrorMsg_ = msg;
        emit User::signUpErrorMsgChanged();
    }
}

void User::setSignInErrorMsg(const QString &msg)
{
    if (this->signInErrorMsg_.compare(msg) != 0){
        this->signInErrorMsg_ = msg;
        emit User::signInErrorMsgChanged();
    }
}

void User::setUserProfile(const QVariantMap &resMap)
{
    const auto profile = resMap.toStdMap();
    if (this->userProfile_ != profile){
        std::copy(std::begin(profile),std::end(profile),std::inserter(this->userProfile_,std::begin(this->userProfile_)));
        emit User::userProfileChanged();
    }
}

void User::addSignedUpUser()
{
    using namespace KEYS;

    const auto endpoint = this->getMongoEndpoint(Endpoints::MONGO_INSERT_ONE);

    Request request((QUrl(endpoint)));
    request.setHeader(Request::ContentTypeHeader,"application/json");
    request.setRawHeader("api-key",RestApi::MONGO_DB_APIKEY);
    request.setRawHeader("Access-Control-Request-Headers","*");

    const auto data = this->getInsertNewUserDoc();
    const auto load = this->getMongoActionDoc(QString(MongoConfig::USERS),QString(Keys::DOCUMENT),data);
    this->reply_ = ReplyPointer(this->getNetworkAccessManager()->post(request, load.toJson()));

    QObject::connect(this->reply_.get(),&Reply::readyRead,this,[this](){
        const auto reply = qobject_cast<Reply*>(this->sender());
        if (reply){
            const auto res = QJsonDocument::fromJson(reply->readAll());
            this->parseAddSignedUpUser(res.object());
        }
    });
}

void User::loginUser()
{
    using namespace KEYS;

    const auto endpoint = this->getMongoEndpoint(Endpoints::MONGO_FIND_ONE);

    Request request((QUrl(endpoint)));
    request.setHeader(Request::ContentTypeHeader,"application/json");
    request.setRawHeader("api-key",RestApi::MONGO_DB_APIKEY);
    request.setRawHeader("Access-Control-Request-Headers","*");

    const QVariantMap findOne = {
        {QString(Keys::LOCAL_ID),this->getLocalId()}
    };
    const auto data = this->getMongoActionDoc(QString(MongoConfig::USERS),Keys::FILTER,findOne);
    this->reply_ = ReplyPointer(this->getNetworkAccessManager()->post(request, data.toJson()));

    QObject::connect(this->reply_.get(),&Reply::readyRead,this,[this](){
        const auto reply = qobject_cast<Reply*>(this->sender());
        if (reply){
            const auto doc = QJsonDocument::fromJson(reply->readAll());
            const auto profile = doc.object().value(Keys::DOCUMENT).toObject().toVariantMap();
            this->setUserProfile(profile);
        }
    });
}

void User::parseSignUpResponse(const QJsonObject &resObj)
{
    using namespace KEYS;
    if (resObj.contains(QString(Keys::ERROR))){
        const auto error = resObj.value(QString(QString(Keys::ERROR))).toObject();
        const auto message = (error.value(QString(Keys::MESSAGE)).toString()).replace("_"," ").toLower();
        this->setSignUpErrorMsg(message);
    }
    else{
        const QStringList keys = {Keys::EMAIL,Keys::ID_TOKEN,Keys::REFRESH_TOKEN,Keys::LOCAL_ID};
        std::for_each(keys.begin(),keys.end(),[resObj,this](const QString& key){
            this->authKeys_.insert(key,resObj.value(key).toVariant());
        });
        this->addSignedUpUser();
    }
}

void User::parseSignInResponse(const QJsonObject &resObj)
{
    using namespace KEYS;
    if (resObj.contains(QString(Keys::ERROR))){
        const auto error = resObj.value(QString(QString(Keys::ERROR))).toObject();
        const auto message = (error.value(QString(Keys::MESSAGE)).toString()).replace("_"," ").toLower();
        this->setSignInErrorMsg(message);
    }
    else{
        const QStringList keys = {Keys::EMAIL,Keys::ID_TOKEN,Keys::REFRESH_TOKEN,Keys::LOCAL_ID};
        std::for_each(keys.begin(),keys.end(),[resObj,this](const QString& key){
            this->authKeys_.insert(key,resObj.value(key).toVariant());
        });
    }
}

void User::parseAddSignedUpUser(const QJsonObject &res)
{
    if (res.value(QString(KEYS::Keys::INSERTED_ID)).isUndefined()){
        qDebug() << "Could not add signed up user";
    }
    else{
        qDebug() << "Added New User: " << res.value(QString(KEYS::Keys::INSERTED_ID)).toString();
        this->loginUser();
    }
}

const QVariantMap User::getInsertNewUserDoc() const
{
    using namespace KEYS;
    const QVariantMap newUser = {
        {QString(Keys::EMAIL),this->getEmail()},
        {QString(Keys::USER_TYPE),this->getUserType()},
        {QString(Keys::LOCAL_ID),this->getLocalId()}
    };
    return newUser;
}

const QJsonDocument User::getSignUpDocument(const SignUpTuple &signUpTuple) const
{
    using namespace KEYS;
    enum{EMAIL,PASSWORD,RETURN_SECURE_TOKEN};
    const QVariantMap signUpLoad = {
        {QString(KEYS::Keys::EMAIL),std::get<EMAIL>(signUpTuple)},
        {QString(KEYS::Keys::PASSWORD),std::get<PASSWORD>(signUpTuple)},
        {QString(KEYS::Keys::RETURN_SECURE_TOKEN),std::get<RETURN_SECURE_TOKEN>(signUpTuple)}
    };
    return QJsonDocument::fromVariant(signUpLoad);
}

void User::onFindResponse(const QJsonDocument &doc)
{
    qDebug() << doc;
}
