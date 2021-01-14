#ifndef WEBCONNECTOR_H
#define WEBCONNECTOR_H

#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>

class WebConnector : public QObject
{
private:

    QNetworkAccessManager *manager;

    QUrl serverUrl;

public:
    Q_OBJECT

    WebConnector();

    enum REQUEST_TYPE {
        CHECK_SELF_UPDATES,
        CHECK_DATA_UPDATES,
        UPDATE_SERVER_INFO,
    };

    QUrl getServerUrl() const;

    void setServerUrl(const QUrl &value);

    QNetworkRequest* createRequest(REQUEST_TYPE type);

    void sendRequest(QNetworkRequest &request, REQUEST_TYPE type);
};

#endif // WEBCONNECTOR_H
