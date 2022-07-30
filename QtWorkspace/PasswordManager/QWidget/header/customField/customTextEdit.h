#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H
#include "abstractCustomField.h"
namespace Ui {
class customTextEdit;
}

class customTextEdit : public AbstractCustomField
{
    Q_OBJECT
private:
    Ui::customTextEdit *ui;
public:
    //构造函数与析构函数
    explicit customTextEdit(const QString& fieldName,isRequiredChoices isRequired=OPTIONAL,dataTypeChoices dataType=NORMAL,QWidget* parent=nullptr);
    ~customTextEdit();
    //属性
    void clear();
    bool isValid();
    QString text();
    AbstractCustomField* clone();
    QString getPlaceholderText();
    void setPlaceholderText(const QString& placeholderText);
    QString toPlainText();
    void setText(const QString &text);
public slots:
    void onControllerEdited();
};

#endif // CUSTOMTEXTEDIT_H
