#include "customField/customTextEdit.h"
#include "ui_customTextEdit.h"
#include <QDebug>
#include <QMetaEnum>
#pragma warning (disable:4100)
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
customTextEdit::customTextEdit(const QString& fieldName,isRequiredChoices isRequired,dataTypeChoices dataType,QWidget* parent):
    AbstractCustomField(fieldName,TEXTEDIT,isRequired,dataType,parent),
    ui(new Ui::customTextEdit)
{
    ui->setupUi(this);
    //设置controller
    QMetaEnum controllerTypeMeta = QMetaEnum::fromType<AbstractCustomField::controllerTypeChoices>();
    ui->controller->setObjectName(controllerTypeMeta.valueToKey(controllerType));
    //设置controllerLabel
    ui->controllerLabel->setText(this->controllerFieldName);
    ui->controllerLabel->setAlignment(Qt::AlignCenter);
    ui->controllerLabel->setStyleSheet("border:0px;background-color:transparent");
    ui->controllerLabel->setObjectName(controllerTypeMeta.valueToKey(controllerType)+QString("LABEL"));
    //设置controllerJudge
    ui->controllerJudge->setStyleSheet("border:0px;background-color:transparent");
    QMetaEnum dataTypeMeta = QMetaEnum::fromType<AbstractCustomField::dataTypeChoices>();
    ui->controllerJudge->setObjectName(dataTypeMeta.valueToKey(controllerType)+QString("JUDGE"));
    //根据dataType初始化
    if(dataType==NORMAL){
        //绑定槽函数
        connect(ui->controller,SIGNAL(textChanged()),this,SLOT(onControllerEdited()));
    }
    setPlaceholderText(defaultPlaceholderText);
}
void customTextEdit::onControllerEdited(){
    QString arg=ui->controller->toPlainText();
    if(isRequired==AbstractCustomField::OPTIONAL&&dataType==NORMAL){
        ui->controllerJudge->setIcon(QIcon());
        ui->controllerJudge->setStatusTip("");
    }else if(!isValid()){
        ui->controllerJudge->setIcon(QIcon(":custom/icons/wrong.png"));
        ui->controllerJudge->setStatusTip("wrong");
    }else{
        ui->controllerJudge->setIcon(QIcon(":custom/icons/right.png"));
        ui->controllerJudge->setStatusTip("right");
    }
}
void customTextEdit::clear(){
    ui->controller->clear();
}
void customTextEdit::setPlaceholderText(const QString& placeholderText){
    ui->controller->setPlaceholderText(placeholderText);
}
QString customTextEdit::toPlainText(){
    return ui->controller->toPlainText();
}
void customTextEdit::setText(const QString &text){
    ui->controller->setText(text);
}
QString customTextEdit::getPlaceholderText(){
    return ui->controller->placeholderText();
}
bool customTextEdit::isValid(){
    if(isRequired==AbstractCustomField::REQUIRED&&toPlainText()=="")
        return false;
    return true;
}

customTextEdit::~customTextEdit(){
    delete ui;
}
AbstractCustomField* customTextEdit::clone(){
    AbstractCustomField* copy=new customTextEdit(fieldName,isRequired,dataType,parent);
    return copy;
}
