#include "customItem/customLineEdit.h"
#include "ui_customLineEdit.h"
#include <QDebug>
#include <QMetaEnum>
customLineEdit::customLineEdit(const QString& name,int isRequired,int dataType,QWidget* parent) :
    abstractCustomItem(name,COMBOBOX,isRequired,dataType,parent),
    ui(new Ui::customLineEdit)
{
    ui->setupUi(this);
    //初始化controller与对应Label
    controller=new QLineEdit();
    controllerLabel=new QLabel(this->name);
    controllerLabel->setAlignment(Qt::AlignCenter);
    controllerLabel->setFixedSize(60,40);
    //初始化布局
    mainLayout=new QHBoxLayout();
    mainLayout->addWidget(controllerLabel);
    mainLayout->addWidget(controller);
    setLayout(mainLayout);
    if(dataType==NORMAL){
        //初始化Judge控件
        QLabel* controllerJudge=new QLabel();
        abstractControllerJudge=controllerJudge;
        mainLayout->addWidget(controllerJudge);
        //设置Judge控件样式
        controllerJudge->setFixedSize(35,35);
        controllerJudge->setObjectName("normalJudge");
        controllerJudge->setStyleSheet("border:0px;background-color:transparent");
    }
    else if(dataType==WEBSITE||dataType==MOBILE||dataType==MAIL){
        //为controller控件设置Validator
        const QValidator* validator=getValidator();
        controller->setValidator(validator);
        QMetaEnum dataTypeMeta = QMetaEnum::fromType<abstractCustomItem::dataTypeChoices>();
        QMetaEnum controllerTypeMeta = QMetaEnum::fromType<abstractCustomItem::controllerTypeChoices>();
        controller->setObjectName(controllerTypeMeta.valueToKey(controllerType));
        //初始化Judge控件
        QPushButton* controllerJudge=new QPushButton();
        abstractControllerJudge=controllerJudge;
        mainLayout->addWidget(controllerJudge);
        //设置Judge控件样式
        controllerJudge->setFixedSize(35,35);
        controllerJudge->setStyleSheet("border:0px;background-color:transparent");
        controllerJudge->setObjectName(dataTypeMeta.valueToKey(controllerType)+QString("JUDGE"));
        //绑定Judge按钮槽函数
        connect(controller,SIGNAL(textEdited(QString)),this,SLOT(controllerEdited(QString)));
    }else if(dataType==PASSWORD){
        //为controller控件设置Validator
        QMetaEnum dataTypeMeta = QMetaEnum::fromType<abstractCustomItem::dataTypeChoices>();
        QMetaEnum controllerTypeMeta = QMetaEnum::fromType<abstractCustomItem::controllerTypeChoices>();
        controller->setObjectName(controllerTypeMeta.valueToKey(controllerType));
        //初始化Judge控件
        QPushButton* controllerJudge=new QPushButton();
        abstractControllerJudge=controllerJudge;
        mainLayout->addWidget(controllerJudge);
        //设置Judge控件样式
        controllerJudge->setFixedSize(35,35);
        controllerJudge->setStyleSheet("border:0px;background-color:transparent");
        controllerJudge->setObjectName(dataTypeMeta.valueToKey(controllerType)+QString("JUDGE"));
        controllerJudge->setIcon(QIcon(":/custom/icons/nosee.png"));
        controllerJudge->setStatusTip("nosee");
        //绑定Judge按钮槽函数
        connect(controllerJudge,SIGNAL(clicked()),this,SLOT(passwordJudgeClicked()));
    }
}

customLineEdit::~customLineEdit()
{
    delete ui;
}
bool customLineEdit::isValid(){
    bool flag=true;
    int position=0;
    QString value=QString(controller->text());
    if((isRequired==REQUIRED&&value=="")||
            (dataType==MAIL&&QValidator::Acceptable!=abstractCustomItem::mailValidator->validate(value,position))||
            (dataType==MOBILE&&QValidator::Acceptable!=abstractCustomItem::mobileValidator->validate(value,position))||
            (dataType==WEBSITE&&QValidator::Acceptable!=abstractCustomItem::websiteValidator->validate(value,position)))
        flag=false;
    return flag;
}
void customLineEdit::controllerEdited(const QString &arg)
{
    qDebug()<<sender()->objectName();
    int position=0;
    QString testValue=arg;
    QPushButton* button=(QPushButton*)abstractControllerJudge;
    if(testValue=="")
    {
        button->setIcon(QIcon());
        button->setStatusTip("");
    }
    else if(QValidator::Acceptable!=getValidator()->validate(testValue,position))
    {
        button->setIcon(QIcon(":custom/icons/wrong.png"));
        button->setStatusTip("wrong");
    }
    else
    {
        button->setIcon(QIcon(":custom/icons/right.png"));
        button->setStatusTip("right");
    }
}
void customLineEdit::passwordJudgeClicked()
{
    QPushButton* button=(QPushButton*)abstractControllerJudge;
    if(button->statusTip()=="nosee")
    {
        button->setIcon(QIcon(":/custom/icons/see.png"));
        button->setStatusTip("see");
        controller->setEchoMode(QLineEdit::Normal);
    }
    else if(button->statusTip()=="see")
    {
        button->setIcon(QIcon(":/custom/icons/nosee.png"));
        button->setStatusTip("nosee");
        controller->setEchoMode(QLineEdit::Password);
    }
}
