#include "customField/customLineEdit.h"
#include "ui_customLineEdit.h"
#include <QDebug>
#include <QMetaEnum>
#pragma warning (disable:4100)
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
customLineEdit::customLineEdit(const QString& fieldName,isRequiredChoices isRequired,dataTypeChoices dataType,QWidget* parent) :
    AbstractCustomField(fieldName,LINEEDIT,isRequired,dataType,parent),
    ui(new Ui::customLineEdit)
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
        connect(ui->controller,SIGNAL(textChanged(QString)),this,SLOT(onControllerEdited(QString)));
    }else if(dataType==WEBSITE||dataType==MOBILE||dataType==MAIL){
        //设置Validator
        const QValidator* validator=getValidator();
        ui->controller->setValidator(validator);
        //绑定槽函数
        connect(ui->controller,SIGNAL(textEdited(QString)),this,SLOT(onControllerEdited(QString)));
    }else if(dataType==PASSWORD){
        //设置初始样式:不显示密码
        ui->controller->setEchoMode(QLineEdit::Password);
        ui->controllerJudge->setIcon(QIcon(":/custom/icons/nosee.png"));
        ui->controllerJudge->setStatusTip("nosee");
        //绑定槽函数
        connect(ui->controllerJudge,SIGNAL(clicked()),this,SLOT(onPasswordJudgeClicked()));
    }
    setPlaceholderText(defaultPlaceholderText);
}

customLineEdit::~customLineEdit()
{
    delete ui;
}
bool customLineEdit::isValid(){
    int position=0;
    QString value=QString(ui->controller->text());
    return ((value!=""&&isRequired==REQUIRED)||(getValidator()!=nullptr&&QValidator::Acceptable==getValidator()->validate(value,position)));
}
void customLineEdit::onControllerEdited(const QString &arg)
{
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
void customLineEdit::onPasswordJudgeClicked()
{
    if(ui->controllerJudge->statusTip()=="nosee"){
        ui->controllerJudge->setIcon(QIcon(":/custom/icons/see.png"));
        ui->controllerJudge->setStatusTip("see");
        ui->controller->setEchoMode(QLineEdit::Normal);
    }else if(ui->controllerJudge->statusTip()=="see"){
        ui->controllerJudge->setIcon(QIcon(":/custom/icons/nosee.png"));
        ui->controllerJudge->setStatusTip("nosee");
        ui->controller->setEchoMode(QLineEdit::Password);
    }
}
void customLineEdit::setPlaceholderText(const QString &placeholderText)
{
    ui->controller->setPlaceholderText(placeholderText);
}
QString customLineEdit::text(){
    return ui->controller->text();
}
void customLineEdit::setText(const QString &text)
{
    ui->controller->setText(text);
}
void customLineEdit::clear()
{
    ui->controller->clear();
    if(dataType!=PASSWORD){
        ui->controllerJudge->setIcon(QIcon());
        ui->controllerJudge->setStatusTip("");
    }
}
void customLineEdit::setMaxLength(int length){
    ui->controller->setMaxLength(length);
}
QString customLineEdit::getPlaceholderText(){
    return ui->controller->placeholderText();
}
AbstractCustomField* customLineEdit::clone(){
    AbstractCustomField* copy=new customLineEdit(fieldName,isRequired,dataType,parent);
    return copy;
}
