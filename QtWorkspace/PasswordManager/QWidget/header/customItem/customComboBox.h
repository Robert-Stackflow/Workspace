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
    QComboBox* controller;
    QLabel* controllerLabel;
    QObject* abstractControllerJudge;
    QHBoxLayout* mainLayout;
public:
    explicit customComboBox(const QString& name,int isRequired=OPTIONAL,int dataType=NORMAL,QWidget* parent=nullptr);
    ~customComboBox();
    bool isValid();
private:
    Ui::customComboBox *ui;
public slots:
    void controllerEdited(const QString &arg);
};

#endif // CUSTOMCOMBOBOX_H
