#ifndef ABSTRACTCUSTOMITEM_H
#define ABSTRACTCUSTOMITEM_H
#include <QLabel>
#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QCheckBox>
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
    friend struct item;
    isRequiredChoices isRequired;
    controllerTypeChoices controllerType;
    dataTypeChoices dataType;
    QString defaultPlaceholderText;
    QWidget* parent;
    QCheckBox* isRequiredCheckBox;
    QString itemTypeName;
    QString name;
public:
    abstractCustomItem(const QString& name,controllerTypeChoices controllerType,isRequiredChoices isRequired=OPTIONAL,dataTypeChoices dataType=NORMAL,QWidget* parent=nullptr);
    const QString &getName() const;
    isRequiredChoices getIsRequired() const;
    dataTypeChoices getDataType() const;
    controllerTypeChoices getControllerType() const;
    const QValidator* getValidator() const;
    QString toString();
public:
    virtual bool isValid()=0;
    virtual void setPlaceholderText(const QString& placeholderText)=0;
    virtual QString getPlaceholderText()=0;
    QWidget *getParent() const;
    void setParent(QWidget *newParent);
    void setIsRequired(isRequiredChoices newIsRequired);
    QCheckBox *getIsRequiredCheckBox() const;
    void setIsRequiredCheckBox(QCheckBox *newIsRequiredCheckBox);
    const QString &getItemTypeName() const;
    void setItemTypeName(const QString &newItemTypeName);
};
class customItems{
private:
    QList<abstractCustomItem*> itemList;
    QString remark;
public:
    //构造函数
    customItems();
    customItems(const customItems& c);
    //重载运算符
    customItems& operator=(const customItems& c);
    customItems operator<<(abstractCustomItem* newItem);
    abstractCustomItem* operator[](int index);
    //增删元素与返回索引
    bool removeOne(const QString &name);
    bool remove(const QStringList &names);
    void append(abstractCustomItem* newItem);
    abstractCustomItem* at(int index);
    //辅助函数
    int count();
    void clear();
    int index(const QString& name);
    bool has(const QString& name);
    QStringList getItemNames();
};

#endif // ABSTRACTCUSTOMITEM_H
