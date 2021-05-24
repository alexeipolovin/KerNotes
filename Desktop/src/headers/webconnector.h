/*
 * Copyright (c) 2021 Alexei Polovin (alexeipolovin@gmail.com)

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
