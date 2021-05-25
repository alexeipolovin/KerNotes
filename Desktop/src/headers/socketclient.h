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

#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H
#include <QTcpSocket>
#include <QtWebSockets/QWebSocket>

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>

class SocketClient : public QObject
{
Q_OBJECT
public:
    explicit SocketClient(QUrl url = QUrl("ws://localhost:12345"), bool debug = false, QObject *parent = Q_NULLPTR);

    void closeConnection();

    QString getFilePath() const;
    void setFilePath(QString &filePath);

    QString getNoteText() const;
    void setNoteText(QString &noteText);


    void syncNotes (QString data)
    {
        m_webSocket.sendTextMessage(QString(data));
    }

    void syncNotes (QByteArray data)
    {
        m_webSocket.sendBinaryMessage(data);
    }
//    template <typename T>
//    void syncNotes(T data)
//    {
//#include <type_traits>
//        if(std::is_same<T, QString>::value)
//        {
//            m_webSocket.sendTextMessage(QString(data));
//        } else if(std::is_same<T, QByteArray>::value) {
//            m_webSocket.sendBinaryMessage(data);
//        }
//    }

    void setUrl(QString url);

Q_SIGNALS:
    void closed();
    void newNoteReceived();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QString noteText = "";
    QString filePath = "";
    QJsonDocument doc;
    QString commitHistory;
    QString lastMessage;
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;



};
#endif // SOCKETCLIENT_H