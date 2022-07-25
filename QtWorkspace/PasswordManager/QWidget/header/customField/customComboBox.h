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
    AbstractCustomField* clone();
    QString getPlaceholderText();
    void setPlaceholderText(const QString &placeholderText);
    void addItem(const QString& item);
    void addItems(const QStringList& items);
    void addItems(const QList<QString>& items);
    int currentIndex();
    void setCurrentIndex(int index);
    QString currentText();
    void setCurrentText(const QString& text);
    void setEnable(bool enable);
    void setEditable(bool editable);
    bool isEnable();
    void setCompleter(QCompleter* completer);
public slots:
    void onControllerCurrentIndexChanged(int);
    void onControllerEdited(const QString &arg);
signals:
    void currentIndexChanged();
};

#endif // CUSTOMCOMBOBOX_H
