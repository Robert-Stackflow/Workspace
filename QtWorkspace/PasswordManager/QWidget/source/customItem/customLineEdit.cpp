#include "customItem/customLineEdit.h"
#include "ui_customLineEdit.h"
#include <QDebug>
#include <QMetaEnum>
customLineEdit::customLineEdit(const QString& name,isRequiredChoices isRequired,dataTypeChoices dataType,QWidget* parent) :
    abstractCustomItem(name,COMBOBOX,isRequired,dataType,parent),
    ui(new Ui::customLineEdit)
{
    ui->setupUi(this);
    //设置controller
    QMetaEnum controllerTypeMeta = QMetaEnum::fromType<abstractCustomItem::controllerTypeChoices>();
    ui->controller->setObjectName(controllerTypeMeta.valueToKey(controllerType));
    //设置controllerLabel
    ui->controllerLabel->setText(this->name);
    ui->controllerLabel->setAlignment(Qt::AlignCenter);
    ui->controllerLabel->setStyleSheet("border:0px;background-color:transparent");
    ui->controllerLabel->setObjectName(controllerTypeMeta.valueToKey(controllerType)+QString("LABEL"));
    //设置controllerJudge
    ui->controllerJudge->setStyleSheet("border:0px;background-color:transparent");
    QMetaEnum dataTypeMeta = QMetaEnum::fromType<abstractCustomItem::dataTypeChoices>();
    ui->controllerJudge->setObjectName(dataTypeMeta.valueToKey(controllerType)+QString("JUDGE"));
    //根据dataType初始化
    if(dataType==WEBSITE||dataType==MOBILE||dataType==MAIL){
        //设置Validator
        const QValidator* validator=getValidator();
        ui->controller->setValidator(validator);
        //绑定槽函数
        connect(ui->controller,SIGNAL(textEdited(QString)),this,SLOT(controllerEdited(QString)));
    }else if(dataType==PASSWORD){
        //设置初始样式:不显示密码
        ui->controllerJudge->setIcon(QIcon(":/custom/icons/nosee.png"));
        ui->controllerJudge->setStatusTip("nosee");
        //绑定槽函数
        connect(ui->controllerJudge,SIGNAL(clicked()),this,SLOT(passwordJudgeClicked()));
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
    return (isRequired==REQUIRED&&value=="")||
            (dataType==MAIL&&QValidator::Acceptable!=abstractCustomItem::mailValidator->validate(value,position))||
            (dataType==MOBILE&&QValidator::Acceptable!=abstractCustomItem::mobileValidator->validate(value,position))||
            (dataType==WEBSITE&&QValidator::Acceptable!=abstractCustomItem::websiteValidator->validate(value,position));
}
void customLineEdit::controllerEdited(const QString &arg)
{
    int position=0;
    QString testValue=arg;
    if(testValue==""){
        ui->controllerJudge->setIcon(QIcon());
        ui->controllerJudge->setStatusTip("");
    }else if(QValidator::Acceptable!=getValidator()->validate(testValue,position)){
        ui->controllerJudge->setIcon(QIcon(":custom/icons/wrong.png"));
        ui->controllerJudge->setStatusTip("wrong");
    }else{
        ui->controllerJudge->setIcon(QIcon(":custom/icons/right.png"));
        ui->controllerJudge->setStatusTip("right");
    }
}
void customLineEdit::passwordJudgeClicked()
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
void customLineEdit::setPlaceholderText(const QString &placeholderText){
    ui->controller->setPlaceholderText(placeholderText);
}
