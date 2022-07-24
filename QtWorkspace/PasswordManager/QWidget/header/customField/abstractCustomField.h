#ifndef ABSTRACTCUSTOMFIELD_H
#define ABSTRACTCUSTOMFIELD_H
#include <QLabel>
#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
class AbstractCustomField :public QWidget{
    Q_OBJECT
public:
    //枚举类
    enum isRequiredChoices{
        OPTIONAL,
        REQUIRED
    };
    enum controllerTypeChoices{
        LINEEDIT,
        COMBOBOX,
        TEXTEDIT
    };
    enum dataTypeChoices{
        NORMAL,
        PASSWORD,
        MAIL,
        MOBILE,
        WEBSITE
    };
    Q_ENUM(dataTypeChoices)
    Q_ENUM(isRequiredChoices)
    Q_ENUM(controllerTypeChoices)
    //静态常量
    static const QRegExp websiteRegExp;
    static const QValidator* websiteValidator;
    static const QRegExp mobileRegExp;
    static const QValidator* mobileValidator;
    static const QRegExp mailRegExp;
    static const QValidator* mailValidator;
protected:
    //控件
    QWidget* parent;
    //基本属性
    QString fieldName;
    QString controllerFieldName;
    QString fieldTypeName;
    dataTypeChoices dataType;
    isRequiredChoices isRequired;
    controllerTypeChoices controllerType;
    //其他
    QString defaultPlaceholderText;
public:
    //构造函数
    explicit AbstractCustomField(const QString& fieldName,controllerTypeChoices controllerType,isRequiredChoices isRequired=OPTIONAL,dataTypeChoices dataType=NORMAL,QWidget* parent=nullptr);
    ~AbstractCustomField();
    //Getter与Setter
    const QString &getFieldName() const;
    QWidget *getParent() const;
    void setParent(QWidget *newParent);
    dataTypeChoices getDataType() const;
    controllerTypeChoices getControllerType() const;
    isRequiredChoices getIsRequired() const;
    void setIsRequired(isRequiredChoices newIsRequired);
    const QString &getFieldTypeName() const;
    void setFieldTypeName(const QString &newFieldTypeName);
    const QValidator* getValidator() const;
    //其他
    QString toString();
    //抽象函数
    virtual bool isValid()=0;
    virtual QString getPlaceholderText()=0;
    virtual AbstractCustomField* clone();
    virtual void setPlaceholderText(const QString& placeholderText)=0;
};

#endif // ABSTRACTCUSTOMFIELD_H
