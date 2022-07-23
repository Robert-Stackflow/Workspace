#include "util/groupType.h"
GroupType::GroupType(QString GroupTypeName,QString describe,QList<AbstractCustomField*> customFieldList){
    this->groupTypeName=GroupTypeName;
    this->describe=describe;
    this->customFieldList=customFieldList;
    this->createTime=QDateTime::currentDateTime();
    this->lastEditTime=QDateTime::currentDateTime();
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
//CustomFields& CustomFields::operator=(const CustomFields& c){
//    CustomFields* customFieldsTemp=new CustomFields();
//    for(int i=0;i<c.fieldList.count();i++){
//        AbstractCustomField* temp=nullptr;
//        if(c.fieldList[i]->getControllerType()==AbstractCustomField::LINEEDIT){
//            temp=new customLineEdit(c.fieldList[i]->getFieldName(),c.fieldList[i]->getIsRequired(),c.fieldList[i]->getDataType(),c.fieldList[i]->getParent());
//        }else if(c.fieldList[i]->getControllerType()==AbstractCustomField::COMBOBOX){
//            temp=new customComboBox(c.fieldList[i]->getFieldName(),c.fieldList[i]->getIsRequired(),c.fieldList[i]->getDataType(),c.fieldList[i]->getParent());
//        }
//        customFieldsTemp->append(temp);
//    }
//    return *customFieldsTemp;
//}
