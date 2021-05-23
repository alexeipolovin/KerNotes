#include <iostream>
#include <QUrl>
#include <QString>
#include <QJsonDocument>
#define DEFAULT_URL "localhost"
#define DEFAULT_PORT "1234"
class SocketClient 
{
public:
    bool m_debug;
    
    explicit SocketClient(QUrl url, bool m_debug);
    ~SocketClient() = default;

    bool isRightData(QJsonDocument &doc);
signals:
    void newFileReceived();

private:
    QString fileText;
    QString filePath;
};