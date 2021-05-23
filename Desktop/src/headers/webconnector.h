#ifndef WEBCONNECTOR_H
#define WEBCONNECTOR_H

#include <QtNetwork/QNetworkAccessManager>
#include <QSettings>
#include <QUrl>
#include <QObject>

class WebConnector : public QObject
{
Q_OBJECT
public:

    WebConnector();

    enum REQUEST_TYPE
    {
        CHECK_SELF_UPDATES,
        CHECK_DATA_UPDATES,
        UPDATE_SERVER_INFO,
    };

    QUrl getServerUrl() const;

    void setServerUrl(const QUrl &value);

    QNetworkRequest* createRequest(REQUEST_TYPE type);

    void sendRequest(QNetworkRequest *request, REQUEST_TYPE type);

    void checkUpdates();
private:
    QJsonObject parseReply(QNetworkReply *reply, WebConnector::REQUEST_TYPE type);

    QNetworkAccessManager *manager;

    QSettings *settings;

    QUrl serverUrl;
signals:
    void newVersionAvailable();
    void autoUpdatesUnknown();
    void newDataReceived();
};

#endif // WEBCONNECTOR_H
