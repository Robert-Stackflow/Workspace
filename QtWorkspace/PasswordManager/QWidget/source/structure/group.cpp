#include "structure/group.h"
#include <QDateTime>
Group::Group(int groupType,QString groupName,QDateTime createTime,QDateTime lastEditTime,QString describe){
    this->groupType=groupType;
    this->groupName=groupName;
    this->createTime=createTime;
    this->lastEditTime=lastEditTime;
    this->describe=describe;
}
int Group::count(){
    return keyItemList.count();
}
void Group::clear(){
    keyItemList.clear();
}
Group* Group::operator<<(KeyItem* newKeyItem){
    keyItemList<<newKeyItem;
    return this;
}
KeyItem* Group::operator[](int index){
    return keyItemList[index];
}
KeyItem* Group::at(int index){
    return keyItemList[index];
}
bool Group::removeAt(int index){
    if(index<0||index>=count()){
        return false;
    }
    else{
        keyItemList.removeAt(index);
        return true;
    }
}
void Group::append(KeyItem* newKeyItem){
    keyItemList.append(newKeyItem);
}

int Group::getFlag() const
{
    return flag;
}

void Group::setFlag(int newFlag)
{
    flag = newFlag;
}

int Group::getGroupType() const
{
    return groupType;
}
const QString &Group::getGroupName() const
{
    return groupName;
}

void Group::setGroupName(const QString &newGroupName)
{
    groupName = newGroupName;
}

const QString &Group::getDescribe() const
{
    return describe;
}

void Group::setDescribe(const QString &newDescribe)
{
    describe = newDescribe;
}

const QDateTime &Group::getCreateTime() const
{
    return createTime;
}
const QDateTime &Group::getLastEditTime() const
{
    return lastEditTime;
}

void Group::setLastEditTime()
{
    lastEditTime = QDateTime::currentDateTime();
}
