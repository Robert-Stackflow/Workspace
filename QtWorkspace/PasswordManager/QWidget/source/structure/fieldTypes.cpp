#include "structure/fieldTypes.h"
QStringList FieldTypes::getNames(){
    QStringList names;
    for(int i=0;i<fieldTypeList.count();i++)
        names<<fieldTypeList[i].getFieldTypeName();
    return names;
}
AbstractCustomField::isRequiredChoices FieldTypes::getIsRequired(const QString& itemTypeName){
    return fieldTypeList[getNames().indexOf(itemTypeName)].getFieldIsRequired();
}
AbstractCustomField::controllerTypeChoices FieldTypes::getControllerType(const QString& itemTypeName){
    return fieldTypeList[getNames().indexOf(itemTypeName)].getFieldControllerType();
}
AbstractCustomField::dataTypeChoices FieldTypes::getDataType(const QString& itemTypeName){
    return fieldTypeList[getNames().indexOf(itemTypeName)].getFieldDataType();
}
FieldTypes FieldTypes::operator<<(FieldType newFieldType){
    fieldTypeList<<newFieldType;
    return *this;
}
int FieldTypes::count(){
    return fieldTypeList.count();
}
FieldType FieldTypes::operator[](int index){
    return fieldTypeList[index];
}

FieldType FieldTypes::at(int index){
    return fieldTypeList[index];
}
void FieldTypes::append(FieldType newField){
    fieldTypeList<<newField;
}
