#include "structure/keyItem.h"
#include <QDateTime>
#pragma warning (disable:4100)
KeyItem::KeyItem(int groupType,QStringList fieldValueList){
    this->groupType=groupType;
    this->createTime=QDateTime::currentDateTime();
    this->lastEditTime=QDateTime::currentDateTime();
    this->fieldValueList=fieldValueList;
}
KeyItem::KeyItem(int groupType,QDateTime createTime,QDateTime lastEditTime,QStringList fieldValueList){
    this->groupType=groupType;
    this->createTime=createTime;
    this->lastEditTime=lastEditTime;
    this->fieldValueList=fieldValueList;
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
//重载运算符
QString KeyItem::operator[](int index){
    return fieldValueList[index];
}
KeyItem KeyItem::operator<<(QString newFieldValue){
    fieldValueList<<newFieldValue;
    setLastEditTime();
    return *this;
}
//增删元素与返回索引
QString KeyItem::at(int index){
    return fieldValueList[index];
}
void KeyItem::append(QString newFieldValue){
    fieldValueList<<newFieldValue;
    setLastEditTime();
}
