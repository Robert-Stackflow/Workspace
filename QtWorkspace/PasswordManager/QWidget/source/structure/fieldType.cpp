#include "structure/fieldType.h"
#include <QDebug>
FieldType::FieldType(QString itemTypeName,AbstractCustomField::controllerTypeChoices itemControllerType,AbstractCustomField::dataTypeChoices itemDataType,AbstractCustomField::isRequiredChoices itemIsRequired){
    this->fieldTypeName=itemTypeName;
    this->fieldControllerType=itemControllerType;
    this->fieldDataType=itemDataType;
    this->fieldIsRequired=itemIsRequired;
}
const QString &FieldType::getFieldTypeName() const
{
    return fieldTypeName;
}

void FieldType::setFieldTypeName(const QString &newFieldTypeName)
{
    fieldTypeName = newFieldTypeName;
}

const AbstractCustomField::isRequiredChoices &FieldType::getFieldIsRequired() const
{
    return fieldIsRequired;
}

void FieldType::setFieldIsRequired(const AbstractCustomField::isRequiredChoices &newFieldIsRequired)
{
    fieldIsRequired = newFieldIsRequired;
}

const AbstractCustomField::controllerTypeChoices &FieldType::getFieldControllerType() const
{
    return fieldControllerType;
}

void FieldType::setFieldControllerType(const AbstractCustomField::controllerTypeChoices &newFieldControllerType)
{
    fieldControllerType = newFieldControllerType;
}

const AbstractCustomField::dataTypeChoices &FieldType::getFieldDataType() const
{
    return fieldDataType;
}

void FieldType::setFieldDataType(const AbstractCustomField::dataTypeChoices &newFieldDataType)
{
    fieldDataType = newFieldDataType;
}
