#ifndef FIELDTYPES_H
#define FIELDTYPES_H
#include "fieldType.h"
class FieldTypes{
private:
    QList<FieldType> fieldTypeList;
public:
    FieldTypes();
    //Getter和Setter
    AbstractCustomField::isRequiredChoices getIsRequired(const QString& fieldTypeName);
    AbstractCustomField::controllerTypeChoices getControllerType(const QString& fieldTypeName);
    AbstractCustomField::dataTypeChoices getDataType(const QString& fieldTypeName);
    //重载运算符
    FieldType operator[](int index);
    FieldTypes operator<<(FieldType newFieldType);
    //基本操作
    int count();
    FieldType at(int index);
    void append(FieldType newField);
    //获取字段类型名称列表
    QStringList getNames();
};
#endif // FIELDTYPES_H
