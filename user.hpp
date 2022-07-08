#ifndef USER_HPP
#define USER_HPP

#include <map>
#include <tuple>
#include <QObject>
#include <QVariantMap>

#include "restapi.hpp"

class User : public RestApi
{
    Q_OBJECT
    Q_PROPERTY(QString signUpErrorMsg READ signUpErrorMsg WRITE setSignUpErrorMsg NOTIFY signUpErrorMsgChanged);
    Q_PROPERTY(QString signInErrorMsg READ signInErrorMsg WRITE setSignInErrorMsg NOTIFY signInErrorMsgChanged);
    Q_PROPERTY(QVariantMap userProfile READ userProfile WRITE setUserProfile NOTIFY userProfileChanged);
public:
    explicit User(QObject *parent = nullptr);
    using SignUpTuple = std::tuple<QString,QString,bool>;
    using Map = std::map<QString,QVariant>;
public:
    const QString getEmail() const;
    const QString getLocalId() const;
    const QString getUserType() const;
    QString signUpErrorMsg() const;
    QString signInErrorMsg() const;
    QVariantMap userProfile() const;
public: //Q_INVOKABLES
    Q_INVOKABLE void signUpUser(const QString username,const QString password);
    Q_INVOKABLE void signInUser(const QString username,const QString password);
public slots:
    void setSignUpErrorMsg(const QString& msg);
    void setSignInErrorMsg(const QString& msg);
    void setUserProfile(const QVariantMap& profile);
signals:
    void signUpErrorMsgChanged();
    void signInErrorMsgChanged();
    void userProfileChanged();
private:
    void addSignedUpUser();
    void loginUser();
    void parseSignUpResponse(const QJsonObject& res);
    void parseSignInResponse(const QJsonObject& res);
    void parseAddSignedUpUser(const QJsonObject& res);
    const QVariantMap getInsertNewUserDoc() const;
    const QJsonDocument getSignUpDocument(const SignUpTuple& signUpTuple) const;
private slots:
    void onFindResponse(const QJsonDocument&);
private:
    QVariantMap authKeys_ = {{KEYS::Keys::USER_TYPE,QString("ADMIN")}};
    User::Map userProfile_;
    ReplyPointer reply_;
    QString signUpErrorMsg_;
    QString signInErrorMsg_;
};

#endif // USER_HPP
