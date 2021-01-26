#include "src/headers/webconnector.h"

#include <QtNetwork/QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

#define AUTO_UPDATES "AUTO_UPDATES_AVAILABLE"

WebConnector::WebConnector()
{
    qDebug() << "WebConnector initialized";
    settings = new QSettings("Kernux", "KerNotes");
}

void WebConnector::checkUpdates()
{
    // Auto Updates setup checking (Win/Mac solution only?)
    if(this->settings->value(AUTO_UPDATES).toString() != "")
    {
        qDebug() << settings->value(AUTO_UPDATES).toString();
        if(settings->value(AUTO_UPDATES).toBool() == true)
        {
            QNetworkRequest *request = createRequest(CHECK_SELF_UPDATES);

            sendRequest(request, CHECK_SELF_UPDATES);
        }
    } else {
        // Try something different
        qDebug() << "Unknown state";
        qDebug() << settings->value(AUTO_UPDATES).toString();
        emit autoUpdatesUnknown();
    }

}

void WebConnector::setServerUrl(const QUrl &value)
{
    serverUrl = value;
}

QUrl WebConnector::getServerUrl() const
{
    return serverUrl;
}

QJsonObject WebConnector::parseReply(QNetworkReply *reply, WebConnector::REQUEST_TYPE type)
{
   QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
   QJsonObject root = document.object();
   switch(type)
   {
   case CHECK_SELF_UPDATES:
   {
      int version = root.find("version").value().toInt();

      if(settings->value("version") != "")
        if(version != settings->value("version").toInt())
        {
            emit newVersionAvailable();
        }
      break;
   }
   case CHECK_DATA_UPDATES: {
       // What the fuck?
        break;
   }
   default:
       break;
   }
   return root;
}

void WebConnector::sendRequest(QNetworkRequest *request, WebConnector::REQUEST_TYPE type)
{
    switch (type)
    {
        case CHECK_SELF_UPDATES:
        {
            QNetworkReply *reply = manager->get(*request);
            // от безжалостных уличных драмм
            connect(reply, &QNetworkReply::finished,this, [this, reply, type]() {
               QJsonObject doc = parseReply(reply, type);
            });
            break;
        }
        default:
            return;

    }
}

QNetworkRequest* WebConnector::createRequest(WebConnector::REQUEST_TYPE type)
{
    QNetworkRequest *request = new QNetworkRequest();
    request->setUrl(this->serverUrl.toString() + "?type=" + type);
    return request;
}
