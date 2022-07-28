#ifndef FIELDTYPES_H
#define FIELDTYPES_H
#include "fieldType.h"
class FieldTypes{
private:
    QList<FieldType> fieldTypeList;
public:
    FieldTypes();
    QStringList getNames();
    AbstractCustomField::isRequiredChoices getIsRequired(const QString& fieldTypeName);
    AbstractCustomField::controllerTypeChoices getControllerType(const QString& fieldTypeName);
    AbstractCustomField::dataTypeChoices getDataType(const QString& fieldTypeName);
    FieldTypes operator<<(FieldType newFieldType);
    int count();
    FieldType operator[](int index);
    FieldType at(int index);
    void append(FieldType newField);
};
#endif // FIELDTYPES_H
