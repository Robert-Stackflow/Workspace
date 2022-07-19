#ifndef ABSTRACTCUSTOMITEM_H
#define ABSTRACTCUSTOMITEM_H
#include <QLabel>
#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
class abstractCustomItem :public QWidget{
    Q_OBJECT
public:
    enum isRequiredChoices{
        OPTIONAL,
        REQUIRED
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
    Q_ENUM(isRequiredChoices)
    Q_ENUM(controllerTypeChoices)
    Q_ENUM(dataTypeChoices)
    static const QRegExp websiteRegExp;
    static const QValidator* websiteValidator;
    static const QRegExp mobileRegExp;
    static const QValidator* mobileValidator;
    static const QRegExp mailRegExp;
    static const QValidator* mailValidator;
protected:
    isRequiredChoices isRequired;
    controllerTypeChoices controllerType;
    dataTypeChoices dataType;
    QString defaultPlaceholderText;
    QWidget* parent;
    QString name;
public:
    abstractCustomItem(const QString& name,controllerTypeChoices controllerType,isRequiredChoices isRequired=OPTIONAL,dataTypeChoices dataType=NORMAL,QWidget* parent=nullptr);
    const QString &getName() const;
    int getIsRequired() const;
    int getDataType() const;
    int getControllerType() const;
    const QValidator* getValidator() const;
    QString toString();
public:
    virtual bool isValid()=0;
};
#endif // ABSTRACTCUSTOMITEM_H
