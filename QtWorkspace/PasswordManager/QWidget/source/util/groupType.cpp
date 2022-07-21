#include "util/groupType.h"
groupType::groupType(QString groupTypeName,QString describe,customItems* items){
    this->groupTypeName=groupTypeName;
    this->describe=describe;
    this->items=items;
    this->createTime=QDateTime::currentDateTime();
    this->lastEditTime=QDateTime::currentDateTime();
}
bool groupType::has(const QString &name)
{
    return items->has(name);
}
int groupType::count()
{
    return items->count();
}
int groupType::index(const QString &name){
    return items->index(name);
}
void groupType::clear(){
    items->clear();
}
bool groupType::removeOne(const QString &name){
    return items->removeOne(name);
}
bool groupType::remove(const QStringList &names){
    return items->remove(names);
}
groupType* groupType::operator<<(abstractCustomItem* newItem)
{
    items->append(newItem);
    return this;
}
abstractCustomItem* groupType::operator[](int index){
    return items->at(index);
}
void groupType::append(abstractCustomItem* newItem){
    items->append(newItem);
}
abstractCustomItem* groupType::at(int index){
    return items->at(index);
}
void groupType::setLastEditTime(){
    this->lastEditTime=QDateTime::currentDateTime();
}
const QString &groupType::getDescribe() const
{
    return describe;
}

void groupType::setDescribe(const QString &newDescribe)
{
    describe = newDescribe;
}

const QDateTime &groupType::getCreateTime() const
{
    return createTime;
}

const QDateTime &groupType::getLastEditTime() const
{
    return lastEditTime;
}

const QString &groupType::getGroupTypeName() const
{
    return groupTypeName;
}
QStringList groupType::getItemNames(){
    return items->getItemNames();
}
void groupType::setGroupTypeName(const QString &newGroupTypeName)
{
    groupTypeName = newGroupTypeName;
}

int groupTypes::index(const QString& groupTypeName){
    for(int i=0;i<groupTypeList.count();i++)
        if(groupTypeList[i]->getGroupTypeName()==groupTypeName)
            return i;
    return -1;
}
bool groupTypes::has(const QString& groupTypeName){
    if(index(groupTypeName)==-1)
        return false;
    else
        return true;
}
groupType* groupTypes::at(int index){
    return groupTypeList[index];
}
void groupTypes::append(groupType* newGroupType){
    groupTypeList<<newGroupType;
}
bool groupTypes::removeOne(const QString& groupTypeName){
    int i=index(groupTypeName);
    if(i==-1){
        return false;
    }else{
        groupTypeList.removeAt(i);
        return true;
    }
}
bool groupTypes::remove(const QStringList& groupTypeNames){
    bool flag=true;
    for(int i=0;i<groupTypeNames.count();i++)
        if(!removeOne(groupTypeNames[i]))
            flag=false;
    return flag;
}
int groupTypes::count(){
    return groupTypeList.count();
}
groupType *groupTypes::operator [](int index){
    return groupTypeList[index];
}
groupTypes* groupTypes::operator<<(groupType* newGroupType){
    groupTypeList<<newGroupType;
    return this;
}
QStringList groupTypes::getGroupTypeNames(){
    QStringList list;
    for(int i=0;i<groupTypeList.count();i++)
        list<<groupTypeList[i]->getGroupTypeName();
    return list;
}
