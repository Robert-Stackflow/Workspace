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
    bool isValid();
private:
    Ui::customComboBox *ui;
public slots:
    void controllerEdited(const QString &arg);
};

#endif // CUSTOMCOMBOBOX_H
