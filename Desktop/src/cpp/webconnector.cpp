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
   case CHECK_DATA_UPDATES:
   {
       QString text = root.find("text").value().toString();
        emit newDataReceived();
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
