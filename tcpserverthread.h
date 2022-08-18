#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include <QJsonObject>
#include <QJsonDocument>

class tcpServerThread : public QThread
{
    Q_OBJECT
public:
    explicit tcpServerThread(QObject *parent = nullptr);

protected:
    void run();

private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

    char readBuf[10240] = {0};

    QJsonParseError jsonError;
    QJsonDocument jsondocument;
    QJsonObject::Iterator iteratorGroup;
    QJsonObject::Iterator iteratorTag;
    QJsonObject root;
    QJsonObject GroupName;

private slots:
    void ServerReadData();
    void ServerNewConnection();
    void sServerDisConnection();

signals:
    // 自定义信号, 传递数据
    void freshValue(QString groupName,QString tagName,QString tagvalue,uint32_t tagtime);
    void addTag(QString groupName,QString tagName,QString tagvalue,uint32_t tagtime);
};

extern QMap<QString,int> tagIndexMap;
#endif // TCPSERVERTHREAD_H
