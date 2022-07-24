#include "customField/abstractCustomField.h"
#include <QMetaEnum>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
const QRegExp AbstractCustomField::websiteRegExp=QRegExp("^(http|https)://([\\w-]+\\.)+[\\w-]+(/[\\w-./?%&=]*)?$");
const QValidator* AbstractCustomField::websiteValidator=new QRegExpValidator(AbstractCustomField::websiteRegExp,0);
const QRegExp AbstractCustomField::mobileRegExp=QRegExp("^1(3\\d|4[5-9]|5[0-35-9]|6[2567]|7[0-8]|8\\d|9[0-35-9])\\d{8}$");
const QValidator* AbstractCustomField::mobileValidator=new QRegExpValidator(AbstractCustomField::mobileRegExp,0);
const QRegExp AbstractCustomField::mailRegExp=QRegExp("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
const QValidator* AbstractCustomField::mailValidator=new QRegExpValidator(AbstractCustomField::mailRegExp,0);
AbstractCustomField::AbstractCustomField(const QString& fieldName,controllerTypeChoices controllerType,isRequiredChoices isRequired,dataTypeChoices dataType,QWidget* parent):QWidget(parent){
    this->parent=parent;
    this->fieldName=fieldName;
    this->controllerFieldName=fieldName;
    if(isRequired==REQUIRED){
        this->controllerFieldName='*'+this->controllerFieldName;
    }
    this->controllerFieldName+=':';
    this->controllerType=controllerType;
    this->isRequired=isRequired;
    this->dataType=dataType;
    switch(dataType){
    case NORMAL:
        defaultPlaceholderText=QString("Enter Text");
        break;
    case PASSWORD:
        defaultPlaceholderText=QString("Enter Password");
        break;
    case WEBSITE:
        defaultPlaceholderText=QString("Enter website");
        break;
    case MAIL:
        defaultPlaceholderText=QString("Enter email");
        break;
    case MOBILE:
        defaultPlaceholderText=QString("Enter phone number");
        break;
    }
}
const QValidator* AbstractCustomField::getValidator() const{
    const QValidator* validator=nullptr;
    if(dataType==MOBILE)
        validator=AbstractCustomField::mobileValidator;
    else if(dataType==MAIL)
        validator=AbstractCustomField::mailValidator;
    else if(dataType==WEBSITE)
        validator=AbstractCustomField::websiteValidator;
    return validator;
}
QString AbstractCustomField::toString(){
    QMetaEnum controllerTypeMeta = QMetaEnum::fromType<AbstractCustomField::controllerTypeChoices>();
    QMetaEnum isRequiredMeta = QMetaEnum::fromType<AbstractCustomField::isRequiredChoices>();
    QMetaEnum dataTypeMeta = QMetaEnum::fromType<AbstractCustomField::dataTypeChoices>();
    return QString(QString("{fieldName}:")+QString(fieldName)
                   +QString(",{controllerType}:")+QString(controllerTypeMeta.valueToKey(controllerType))
                   +QString(",{isRequired}:")+QString(isRequiredMeta.valueToKey(isRequired))
                   +QString(",{dataType}:")+QString(dataTypeMeta.valueToKey(dataType)));
}
AbstractCustomField::~AbstractCustomField(){
}
const QString &AbstractCustomField::getFieldName() const
{
    return fieldName;
}

AbstractCustomField::isRequiredChoices AbstractCustomField::getIsRequired() const
{
    return isRequired;
}

AbstractCustomField::dataTypeChoices AbstractCustomField::getDataType() const
{
    return dataType;
}

AbstractCustomField::controllerTypeChoices AbstractCustomField::getControllerType() const
{
    return controllerType;
}
QWidget *AbstractCustomField::getParent() const
{
    return parent;
}

void AbstractCustomField::setParent(QWidget *newParent)
{
    parent = newParent;
}

void AbstractCustomField::setIsRequired(isRequiredChoices newIsRequired)
{
    isRequired = newIsRequired;
    if(isRequired==REQUIRED)
        controllerFieldName="*"+controllerFieldName;
    else
        controllerFieldName=controllerFieldName.right(this->controllerFieldName.length()-1);
}
const QString &AbstractCustomField::getFieldTypeName() const
{
    return fieldTypeName;
}

void AbstractCustomField::setFieldTypeName(const QString &newFieldTypeName)
{
    fieldTypeName = newFieldTypeName;
}
AbstractCustomField* AbstractCustomField::clone(){
    return nullptr;
}
