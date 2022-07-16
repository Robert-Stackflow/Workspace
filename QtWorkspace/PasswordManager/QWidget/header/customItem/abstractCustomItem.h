#ifndef ABSTRACTCUSTOMITEM_H
#define ABSTRACTCUSTOMITEM_H
#include <QString>
#include <QWidget>
class abstractCustomItem{
public:
    abstractCustomItem(QWidget* parent,QString& name,int controllerType,int isRequired=OPTIONAL,int isAutofillable=NOTAutofillable,int dataType=NORMAL);

    const QString &getName() const;
    int getIsRequired() const;
    int getIsAutofillable() const;
    int getDataType() const;
    int getControllerType() const;

protected:
    enum isRequiredChoices{
        OPTIONAL,
        REQUIRED
    };
    enum isAutofillableChoices{
        NOTAutofillable,
        Autofillable
    };
    enum controllerTypeChoices{
        LINEEDIT,
        COMBOBOX,
        CHECKBOX,
        RADIO,
        TEXTEDIT
    };
    enum dataTypeChoices{
        NORMAL,
        PASSWORD,
        MAIL,
        MOBILE,
        WEBSITE
    };
    QWidget* parent;
    QString name;
    QString hex;
    int isRequired;
    int isAutofillable;
    int dataType;
    int controllerType;
};
abstractCustomItem::abstractCustomItem(QWidget* parent,QString& name,int controllerType,int isRequired,int isAutofillable,int dataType){
    if(isRequired==REQUIRED){
        name+='*';
    }
    this->parent=parent;
    this->name=name;
    this->controllerType=controllerType;
    this->isRequired=isRequired;
    this->isAutofillable=isAutofillable;
    this->dataType=dataType;
}

inline const QString &abstractCustomItem::getName() const
{
    return name;
}

inline int abstractCustomItem::getIsRequired() const
{
    return isRequired;
}

inline int abstractCustomItem::getIsAutofillable() const
{
    return isAutofillable;
}

inline int abstractCustomItem::getDataType() const
{
    return dataType;
}

inline int abstractCustomItem::getControllerType() const
{
    return controllerType;
}
#endif // ABSTRACTCUSTOMITEM_H
