#include <exception>
#include <stdexcept>
#include "restapi.hpp"

RestApi::RestApi(QObject *parent)
    : QObject{parent},
      manager_(std::make_unique<Manager>(this))
{

}


RestApi::Manager *RestApi::getNetworkAccessManager()
{
    return this->manager_.get();
}

const QString RestApi::getMongoEndpoint(const char* action) const
{
    return (QString(KEYS::Endpoints::MONGO_DB) + QString(action));
}

const QJsonDocument RestApi::getMongoActionDoc(const QString &collection, const QString &key, const QVariantMap &data) const
{
    using namespace KEYS;
    const QVariantMap dataRaw = {
        {QString(Keys::COLLECTION),collection},
        {QString(Keys::DATABASE),QString(MongoConfig::DATABASE)},
        {QString(Keys::DATA_SOURCE),QString(MongoConfig::DATA_SOURCE)},
        {key,data}
    };
    return QJsonDocument::fromVariant(dataRaw);
}

void RestApi::fetchFinished()
{
    const auto reply = qobject_cast<Reply*>(this->sender());
    if (reply){
        const auto response = QJsonDocument::fromJson(reply->readAll());
        emit RestApi::fetchedResponse(response);
    }
}

