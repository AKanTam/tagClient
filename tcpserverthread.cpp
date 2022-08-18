#include "tcpserverthread.h"

tcpServerThread::tcpServerThread(QObject *parent) : QThread(parent)
{
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen(QHostAddress::Any,6666)){
        qDebug()<<"监听服务启动失败";
        return;
    }

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(ServerNewConnection()));

}

void tcpServerThread::run()
{

}

/*
{
  "RTU1": {
    "SDSD": {
      "value": "20",
      "time": ""
    },
    "SDXD": {
      "value": "20",
      "time": ""
    }
  }
}
*/
void tcpServerThread::ServerReadData()
{
    tcpSocket->read(readBuf,10240);
    if( strlen(readBuf) > 0)
    {
        //       QString showNsg = readBuf;
        jsondocument = QJsonDocument::fromJson(readBuf,&jsonError);
        if (!jsondocument.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            root = jsondocument.object(); // 转化为对象
            for (iteratorGroup = root.begin(); iteratorGroup != root.end(); iteratorGroup++)//遍历json对象
            {
                GroupName = iteratorGroup->toObject();
                for(iteratorTag = GroupName.begin(); iteratorTag != GroupName.end(); iteratorTag++){
                    if(tagIndexMap.contains(iteratorTag.key())){
                        emit freshValue(iteratorGroup.key(),iteratorTag.key(),iteratorTag->toObject().value("value").toString(),iteratorTag->toObject().value("time").toInt());
                    }else{
                        emit addTag(iteratorGroup.key(),iteratorTag.key(),iteratorTag->toObject().value("value").toString(),iteratorTag->toObject().value("time").toInt());
                    }
                    qDebug()<<iteratorTag.key()<<": "<<iteratorTag->toObject().value("value").toString();
                }
            }
        }
        //       qDebug()<<"QT网络通信接收消息: "<<readBuf;
    }
    else
    {
        qDebug()<<"QT网络通信"<< "未正确接收数据";
        return;
    }
}

void tcpServerThread::ServerNewConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();

    if(!tcpSocket)
    {
        qDebug()<<"QT网络通信"<< "未正确获取客户端连接！";
        return;
    }
    else
    {
        qDebug()<<"QT网络通信"<<"成功接受客户端的连接";
        connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ServerReadData()));
        connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(sServerDisConnection()));
    }

}

void tcpServerThread::sServerDisConnection()
{
    qDebug()<<"QT网络通信"<<"与客户端的连接断开";
    return;
}
