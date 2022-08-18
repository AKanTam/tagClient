#include "tagmodel.h"

QMap<QString,int> tagIndexMap;

tagModel::tagModel(QObject *parent)
    : QAbstractListModel(parent)
{
    tagIndexMap.clear();
    tagInfoMap.clear();
}

tagModel *tagModel::getInstance(tcpServerThread *myThread)
{
    tagModel *tempModel = new tagModel;
    tempModel->tcpThread = myThread;
    connect(tempModel->tcpThread,SIGNAL(freshValue(QString,QString,QString,uint32_t)),tempModel,SLOT(freshValue(QString,QString,QString,uint32_t)));
    connect(tempModel->tcpThread,SIGNAL(addTag(QString,QString,QString,uint32_t)),tempModel,SLOT(addTag(QString,QString,QString,uint32_t)));
    return tempModel;
}

int tagModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return tagInfoMap.count();

    // FIXME: Implement me!
}

QVariant tagModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role){
    case TagRoleName::GROUPNAME:
        return tagInfoMap[index.row()].m_groupName;
        break;
    case TagRoleName::TAGNAME:
        return tagInfoMap[index.row()].m_tagName;
        break;
    case TagRoleName::TAGTIME:
        return tagInfoMap[index.row()].m_time;
        break;
    case TagRoleName::TAGVALUE:
        return tagInfoMap[index.row()].m_value;
        break;
    default:
        break;
    }

    // FIXME: Implement me!
    return QVariant();
}

QHash<int, QByteArray> tagModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles.insert(TagRoleName::GROUPNAME,"groupName");
    roles.insert(TagRoleName::TAGNAME,"tagName");
    roles.insert(TagRoleName::TAGTIME,"tagTime");
    roles.insert(TagRoleName::TAGVALUE,"tagValue");

    return roles;
}

void tagModel::freshValue(QString groupName, QString tagName, QString tagvalue, uint32_t tagtime)
{
    tempTag.m_groupName = groupName;
    tempTag.m_tagName = tagName;
    tempTag.m_time = tagtime;
    tempTag.m_value = tagvalue;
    tempTag.m_index = tagIndexMap.value(tagName);

    beginResetModel();

    tagInfoMap.insert(tempTag.m_index,tempTag);

    endResetModel();
}

void tagModel::addTag(QString groupName, QString tagName, QString tagvalue, uint32_t tagtime)
{


    tempTag.m_groupName = groupName;
    tempTag.m_tagName = tagName;
    tempTag.m_time = tagtime;
    tempTag.m_value = tagvalue;
    tempTag.m_index = tagIndexMap.end().value() + 1;

    beginResetModel();

    tagIndexMap.insert(tagName,tempTag.m_index);
    tagInfoMap.insert(tempTag.m_index,tempTag);

    endResetModel();
}
