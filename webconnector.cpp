#include "webconnector.h"

#include <QtNetwork/QNetworkReply>

WebConnector::WebConnector()
{

}

void WebConnector::setServerUrl(const QUrl &value)
{
    serverUrl = value;
}

QUrl WebConnector::getServerUrl() const
{
    return serverUrl;
}

void WebConnector::sendRequest(QNetworkRequest &request, WebConnector::REQUEST_TYPE type)
{
    switch (type)
    {
        case WebConnector::CHECK_DATA_UPDATES:
        {
            manager->get(request);
            // от безжалостных уличных драмм
            connect(manager, &QNetworkReply::finished, )
        }

    }
}

QNetworkRequest* WebConnector::createRequest(WebConnector::REQUEST_TYPE type)
{
    QNetworkRequest *request = new QNetworkRequest();
    request->setUrl(this->serverUrl.toString() + "?type=" + type);
    return request;
}
