#ifndef FIELDTYPE_H
#define FIELDTYPE_H
#include"customField/abstractCustomField.h"
class FieldType{
private:
    QString fieldTypeName;
    AbstractCustomField::isRequiredChoices fieldIsRequired;
    AbstractCustomField::controllerTypeChoices fieldControllerType;
    AbstractCustomField::dataTypeChoices fieldDataType;
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
