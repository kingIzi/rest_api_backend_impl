#ifndef RESTAPI_HPP
#define RESTAPI_HPP

#include <memory>

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QByteArray>

namespace KEYS{

struct Params{
    Params() = delete;
    static constexpr const char* KEY = "key";
    static constexpr const char* AUTH = "auth";
};

struct Keys{
    Keys() = delete;
    //Authentication
    static constexpr const char* LOCAL_ID = "localId";
    static constexpr const char* REFRESH_TOKEN = "refreshToken";
    static constexpr const char* ID_TOKEN = "idToken";
    static constexpr const char* REQUEST_TYPE = "requestType";
    static constexpr const char* EMAIL = "email";
    static constexpr const char* PASSWORD = "password";
    static constexpr const char* RETURN_SECURE_TOKEN = "returnSecureToken";
    static constexpr const char* USER_TYPE = "userType";
    static constexpr const char* PHONE_NO = "phoneNo";
    static constexpr const char* ADDRESS = "address";
    static constexpr const char* ERROR = "error";
    static constexpr const char* MESSAGE = "message";

    //Mongo keys
    static constexpr const char* DATABASE = "database";
    static constexpr const char* COLLECTION = "collection";
    static constexpr const char* DATA_SOURCE = "dataSource";
    static constexpr const char* DOCUMENT = "document";
    static constexpr const char* FILTER = "filter";
    static constexpr const char* INSERTED_ID = "insertedId";
};

struct MongoConfig{
    static constexpr const char* USERS = "users";
    static constexpr const char* DATABASE = "project_database";
    static constexpr const char* DATA_SOURCE = "Cluster0";
};

struct Endpoints{
    Endpoints() = delete;
    static constexpr const char* SIGN_UP_WITH_EMAIL_PASSWORD = "https://identitytoolkit.googleapis.com/v1/accounts:signUp";
    static constexpr const char* SIGN_IN_WITH_EMAIL_PASSWORD = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword";
    static constexpr const char* SEND_VERIFICATION_EMAIL = "https://identitytoolkit.googleapis.com/v1/accounts:sendOobCode";
    static constexpr const char* GET_USER_DATA = "https://identitytoolkit.googleapis.com/v1/accounts:lookup";
    static constexpr const char* CHANGE_EMAIL = "https://identitytoolkit.googleapis.com/v1/accounts:update";
    static constexpr const char* CHANGE_PASSWORD = "https://identitytoolkit.googleapis.com/v1/accounts:update";
    static constexpr const char* REMOVE_USER = "https://identitytoolkit.googleapis.com/v1/accounts:delete";

    static constexpr const char* REALTIME_DATABASE = "https://hair-stylist-scheduler-default-rtdb.europe-west1.firebasedatabase.app/";
    static constexpr const char* MONGO_DB = "https://data.mongodb-api.com/app/data-gxvdg/endpoint/data/v1";

    static constexpr const char* MONGO_FIND = "/action/find";
    static constexpr const char* MONGO_FIND_ONE = "/action/findOne";
    static constexpr const char* MONGO_INSERT_ONE = "/action/insertOne";
    static constexpr const char* MONGO_INSERT_MANY = "/action/insertMany";
    static constexpr const char* MONGO_UPDATE_ONE = "/action/updateOne";
    static constexpr const char* MONGO_UPDATE_MANY = "/action/updateMany";
    static constexpr const char* MONGO_REPLACE_ONE = "/action/replaceOne";
    static constexpr const char* MONGO_DELETE_ONE = "/action/deleteOne";
    static constexpr const char* MONGO_DELETE_MANY = "/action/deleteMany";
};

};

class RestApi : public QObject
{
    Q_OBJECT
public:
    explicit RestApi(QObject* parent = nullptr);
    using Reply = QNetworkReply;
    using Manager = QNetworkAccessManager;
    using Request = QNetworkRequest;
    struct DeleteLaterDeallocator
    {
        void operator()(QObject *object) const
        {
            if(object) {
                object->deleteLater();
            }
        }
    };
    using ReplyPointer = std::unique_ptr<RestApi::Reply, DeleteLaterDeallocator>;
public:
    template <class T>
    using UniPtr = std::unique_ptr<T>;
    template <class T>
    using ShaPtr = std::shared_ptr<T>;
    static constexpr const char* FIREBASE_APIKEY = "AIzaSyCub1UD4lsZTvpZ5FZT3fWKIKkjoN-c9fc";
    static constexpr const char* MONGO_DB_APIKEY = "yBaITYPGTX9IXOXgMQO2XxhAZpPN8ViCmmvRm2Mls8jwTJ9ej59inozUFMKER0ZG";
    Manager* getNetworkAccessManager();
    const QString getMongoEndpoint(const char* action) const;
    const QJsonDocument getMongoActionDoc(const QString& collection,const QString& key,const QVariantMap& data) const;
signals:
    void fetchedResponse(const QJsonDocument&);
private:
private slots:
    void fetchFinished();
private:
    UniPtr<Manager> manager_;
};

#endif // RESTAPI_HPP
