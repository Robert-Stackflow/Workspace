#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H
#include"abstractCustomItem.h"
namespace Ui {
class customComboBox;
}

class customComboBox :public abstractCustomItem
{
    Q_OBJECT
public:
    explicit customComboBox(const QString& name,isRequiredChoices isRequired=OPTIONAL,dataTypeChoices dataType=NORMAL,QWidget* parent=nullptr);
    ~customComboBox();
    void setPlaceholderText(const QString &placeholderText);
    QString getPlaceholderText();
    bool isValid();
    void addItem(const QString& item);
    void addItems(const QStringList& items);
    void clear();
    int currentIndex();
    QString currentText();
    void setCurrentIndex(int index);
    void setCurrentText(const QString& text);
    void setEnable(bool enable);
private:
    Ui::customComboBox *ui;
public slots:
    void controllerEdited(const QString &arg);
};

#endif // CUSTOMCOMBOBOX_H
