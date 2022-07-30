#ifndef FIELDTYPE_H
#define FIELDTYPE_H
#include"customField/abstractCustomField.h"
class FieldType{
private:
    //字段类型名称
    QString fieldTypeName;
    //字段类型属性
    AbstractCustomField::dataTypeChoices fieldDataType;
    AbstractCustomField::isRequiredChoices fieldIsRequired;
    AbstractCustomField::controllerTypeChoices fieldControllerType;
public:
    FieldType(QString fieldTypeName,AbstractCustomField::controllerTypeChoices fieldControllerType,AbstractCustomField::dataTypeChoices fieldDataType,AbstractCustomField::isRequiredChoices fieldIsRequired=AbstractCustomField::OPTIONAL);
    const QString &getFieldTypeName() const;
    void setFieldTypeName(const QString &newFieldTypeName);
    const AbstractCustomField::isRequiredChoices &getFieldIsRequired() const;
    void setFieldIsRequired(const AbstractCustomField::isRequiredChoices &newFieldIsRequired);
    const AbstractCustomField::controllerTypeChoices &getFieldControllerType() const;
    void setFieldControllerType(const AbstractCustomField::controllerTypeChoices &newFieldControllerType);
    const AbstractCustomField::dataTypeChoices &getFieldDataType() const;
    void setFieldDataType(const AbstractCustomField::dataTypeChoices &newFieldDataType);
};
#endif // FIELDTYPE_H
