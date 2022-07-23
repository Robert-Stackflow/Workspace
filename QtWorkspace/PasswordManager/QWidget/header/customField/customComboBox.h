#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H
#include "abstractCustomField.h"
namespace Ui {
class customComboBox;
}

class customComboBox :public AbstractCustomField
{
    Q_OBJECT
private:
    Ui::customComboBox *ui;
public:
    //构造函数/析构函数
    explicit customComboBox(const QString& fieldName,isRequiredChoices isRequired=OPTIONAL,dataTypeChoices dataType=NORMAL,QWidget* parent=nullptr);
    ~customComboBox();
    //属性
    void clear();
    bool isValid();
    QString getPlaceholderText();
    void setPlaceholderText(const QString &placeholderText);
    void addItem(const QString& item);
    void addItems(const QStringList& items);
    int currentIndex();
    void setCurrentIndex(int index);
    QString currentText();
    void setCurrentText(const QString& text);
    void setEnable(bool enable);
    bool isEnable();
public slots:
    void onControllerEdited(const QString &arg);
};

#endif // CUSTOMCOMBOBOX_H
