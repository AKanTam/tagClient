#ifndef TAGMODEL_H
#define TAGMODEL_H

#include <QAbstractListModel>
#include "tcpserverthread.h"

struct tagInfo{
    QString m_groupName;
    QString m_tagName;
    QString m_value;
    uint32_t m_time;
    int m_index;
};

class tagModel : public QAbstractListModel
{
    Q_OBJECT

public:

    enum TagRoleName{
        GROUPNAME,
        TAGNAME,
        TAGTIME,
        TAGVALUE
    };

    explicit tagModel(QObject *parent = nullptr);

    static tagModel * getInstance(tcpServerThread *myThread);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int,QByteArray> roleNames() const override;

private:
    QMap<int,tagInfo> tagInfoMap;
    struct tagInfo tempTag;


public:
    tcpServerThread *tcpThread;


public slots:
    void freshValue(QString groupName,QString tagName,QString tagvalue,uint32_t tagtime);
    void addTag(QString groupName,QString tagName,QString tagvalue,uint32_t tagtime);
};

extern QMap<QString,int> tagIndexMap;
#endif // TAGMODEL_H
