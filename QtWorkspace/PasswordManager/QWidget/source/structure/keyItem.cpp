#include "structure/keyItem.h"
#include <QDateTime>
#pragma warning (disable:4100)
KeyItem::KeyItem(int groupType,QDateTime createTime,QDateTime lastEditTime,QStringList fieldNameList){
    this->groupType=groupType;
    this->createTime=createTime;
    this->lastEditTime=lastEditTime;
    this->fieldNameList=fieldNameList;
}
int KeyItem::getFlag() const
{
    return flag;
}

void KeyItem::setFlag(int newFlag)
{
    flag = newFlag;
}

int KeyItem::getGroupType() const
{
    return groupType;
}

const QDateTime &KeyItem::getCreateTime() const
{
    return createTime;
}

const QDateTime &KeyItem::getLastEditTime() const
{
    return lastEditTime;
}

void KeyItem::setLastEditTime()
{
    lastEditTime = QDateTime::currentDateTime();
}
QString KeyItem::toString(){
    QString result;
    return result;
}
