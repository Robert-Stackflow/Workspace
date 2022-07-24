#include "util/groupType.h"
void GroupType::setCustomFieldList(const QList<AbstractCustomField *> &newCustomFieldList)
{
    customFieldList = newCustomFieldList;
}

GroupType::GroupType(QString groupTypeName,QString describe,QList<AbstractCustomField*> customFieldList){
    this->groupTypeName=groupTypeName;
    this->describe=describe;
    this->customFieldList=customFieldList;
    this->createTime=QDateTime::currentDateTime();
    this->lastEditTime=QDateTime::currentDateTime();
}
GroupType::GroupType(QString groupTypeName,QDateTime createTime,QDateTime lastEditTime,QString describe){
    this->groupTypeName=groupTypeName;
    this->describe=describe;
    this->createTime=createTime;
    this->lastEditTime=lastEditTime;
}
bool GroupType::has(const QString &name)
{
    if(index(name)==-1)
        return false;
    return true;
}
int GroupType::count()
{
    return customFieldList.count();
}
int GroupType::index(const QString &name){
    for(int i=0;i<customFieldList.count();i++)
        if(customFieldList[i]->getFieldName()==name)
            return i;
    return -1;
}
void GroupType::clear(){
    customFieldList.clear();
}
bool GroupType::removeOne(const QString &name){
    int i=index(name);
    if(i==-1){
        return false;
    }else{
        customFieldList.removeAt(i);
        return true;
    }
}
bool GroupType::removeAt(int index){
    if(index<0&&index>=count()){
        return false;
    }else{
        customFieldList.removeAt(index);
        return true;
    }
}
bool GroupType::remove(const QStringList &names){
    bool flag=true;
    for(int i=0;i<names.count();i++)
        if(!removeAt(i))
            flag=false;
    return flag;
}
GroupType* GroupType::operator<<(AbstractCustomField* newField)
{
    customFieldList<<newField;
    return this;
}
AbstractCustomField* GroupType::operator[](int index){
    return customFieldList.at(index);
}
void GroupType::append(AbstractCustomField* newItem){
    customFieldList<<newItem;
}
AbstractCustomField* GroupType::at(int index){
    return customFieldList.at(index);
}
void GroupType::setLastEditTime(){
    this->lastEditTime=QDateTime::currentDateTime();
}
const QString &GroupType::getDescribe() const
{
    return describe;
}

void GroupType::setDescribe(const QString &newDescribe)
{
    describe = newDescribe;
}

const QDateTime &GroupType::getCreateTime() const
{
    return createTime;
}

const QDateTime &GroupType::getLastEditTime() const
{
    return lastEditTime;
}

const QString &GroupType::getGroupTypeName() const
{
    return groupTypeName;
}
QStringList GroupType::getFieldNames(){
    QStringList list;
    for(int i=0;i<count();i++)
        list<<customFieldList[i]->getFieldName();
    return list;
}
void GroupType::setGroupTypeName(const QString &newGroupTypeName)
{
    groupTypeName = newGroupTypeName;
}
GroupType* GroupType::clone(){
    QList<AbstractCustomField*> copyFieldList;
    for(int i=0;i<count();i++){
        AbstractCustomField* copyField=customFieldList[i]->clone();
        copyFieldList<<copyField;
    }
    GroupType* copy=new GroupType(groupTypeName,describe,copyFieldList);
    return copy;
}
