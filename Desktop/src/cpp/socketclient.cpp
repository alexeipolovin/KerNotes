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

#include "src/headers/socketclient.h"
#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

SocketClient::SocketClient(QUrl url, bool debug, QObject *parent) :
        QObject(parent),
        m_url(url),
        m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &SocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &SocketClient::closed);
    m_webSocket.open(url);
}

void SocketClient::closeConnection()
{
    m_webSocket.close();
}

void SocketClient::setUrl(QString url)
{
    this->m_url = QUrl(url);

    m_webSocket.close();
    m_webSocket.open(url);
}

void SocketClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &SocketClient::onTextMessageReceived);
}

void SocketClient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;

    doc = QJsonDocument::fromJson(message.toUtf8());

    auto root = doc.object();

    filePath = root.find("file").value().toString();

    noteText = root.find("text").value().toString();

    if(filePath != "" and noteText != "")
    {
        emit newNoteReceived();
    }
}

QString SocketClient::getFilePath() const
{
    return this->filePath;
}

void SocketClient::setFilePath(QString &filePath)
{
    this->filePath = filePath;
}

QString SocketClient::getNoteText() const
{
    return noteText;
}

void SocketClient::setNoteText(QString &noteText)
{
    this->noteText = noteText;
}