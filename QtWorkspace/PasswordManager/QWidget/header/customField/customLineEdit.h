#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H
#include "abstractCustomField.h"
namespace Ui {
class customLineEdit;
}

class customLineEdit : public AbstractCustomField
{
    Q_OBJECT
private:
    Ui::customLineEdit *ui;
public:
    //构造函数/析构函数
    explicit customLineEdit(const QString& fieldName,isRequiredChoices isRequired=OPTIONAL,dataTypeChoices dataType=NORMAL,QWidget* parent=nullptr);
    ~customLineEdit();
    //属性
    void clear();
    bool isValid();
    AbstractCustomField* clone();
    void setPlaceholderText(const QString &placeholderText);
    QString getPlaceholderText();
    QString text();
    void setText(const QString &text);
    int maxLength();
    void setMaxLength(int length);
public slots:
    void onPasswordJudgeClicked();
    void onControllerEdited(const QString &arg);
};

#endif // CUSTOMLINEEDIT_H
