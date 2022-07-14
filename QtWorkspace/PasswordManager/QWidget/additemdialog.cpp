#include "additemdialog.h"
#include "ui_additemdialog.h"
#include "widget.h"
#include <QDebug>
#include <QFile>
#include <QCompleter>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
addItemDialog::addItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItemDialog)
{
    ui->setupUi(this);
    InitFrame();
}
void addItemDialog::InitFrame()
{
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":/application/qrc/icon.png");
    m_titleBar->forbiddenMaxmizeButton();
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(11);
    font.setBold(true);
    m_titleBar->m_titleLabel->setFont(font);
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    m_titleBar->setFixedWidth(ui->frame->width());
    m_titleBar->forbiddenUserButton();

    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor());
    shadow_effect->setBlurRadius(20);
    shadow_effect->setOffset(0, 0);
    ui->frame->setGraphicsEffect(shadow_effect);

    ui->tabWidget->tabBar()->hide();

    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString temp = this->styleSheet;
        temp+= QLatin1String(file.readAll());
        this->styleSheet=temp;
        this->setStyleSheet(styleSheet);
        file.close();
    }
    InitCommon();
    InitJGY();
    InitMail();
    InitOther();
    InitGroup();
}
void addItemDialog::InitCommon()
{
    ui->password->setEchoMode(QLineEdit::Password);
    ui->password->setObjectName("password");
    ui->passwordJudge->setObjectName("passwordJudge");
    ui->passwordJudge->setStyleSheet("border:0px;background-color:transparent");
    ui->passwordJudge->setIcon(QIcon(":/application/qrc/nosee.png"));
    ui->passwordJudge->setStatusTip("nosee");

    QRegExp websiteReg("^(http|https)://([\\w-]+\\.)+[\\w-]+(/[\\w-./?%&=]*)?$");
    QValidator* websiteValidator=new QRegExpValidator(websiteReg,0);
    ui->website->setValidator(websiteValidator);
    ui->website->setObjectName("website");
    ui->websiteJudge->setObjectName("websiteJudge");
    ui->websiteJudge->setStyleSheet("border:0px;background-color:transparent");

    QRegExp mobileReg("^1(3\\d|4[5-9]|5[0-35-9]|6[2567]|7[0-8]|8\\d|9[0-35-9])\\d{8}$");
    QValidator* mobileValidator=new QRegExpValidator(mobileReg,0);
    ui->mobile->setEditable(true);
    ui->mobile->lineEdit()->setValidator(mobileValidator);
    ui->mobile->setObjectName("mobile");
    ui->mobileJudge->setObjectName("mobileJudge");
    ui->mobileJudge->setStyleSheet("border:0px;background-color:transparent");

    QRegExp mailReg("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
    QValidator* mailValidator=new QRegExpValidator(mailReg,0);
    ui->mail->setEditable(true);
    ui->mail->lineEdit()->setValidator(mailValidator);
    ui->mail->setObjectName("mail");
    ui->mailJudge->setObjectName("mailJudge");
    ui->mailJudge->setStyleSheet("border:0px;background-color:transparent");

    ui->mobile->lineEdit()->setStyleSheet(styleSheet);
    ui->mobile->lineEdit()->setStyleSheet("border:0px");
    ui->mail->lineEdit()->setStyleSheet(styleSheet);
    ui->mail->lineEdit()->setStyleSheet("border:0px");
    ui->nickName->setStyleSheet(styleSheet);

    ui->mail->setCompleter(new QCompleter(ui->mail->model(),this));
    ui->mobile->setCompleter(new QCompleter(ui->mobile->model(),this));

    connect(ui->yes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->no,SIGNAL(clicked()),this,SLOT(no_clicked()));
    connect(ui->passwordJudge,SIGNAL(clicked()),this,SLOT(passwordJudge_clicked()));
    connect(ui->mobile,SIGNAL(currentTextChanged(QString)),this,SLOT(mobileJudge_edited(QString)));
    connect(ui->mail,SIGNAL(currentTextChanged(QString)),this,SLOT(mailJudge_edited(QString)));
    connect(ui->website,SIGNAL(textEdited(QString)),this,SLOT(websiteJudge_edited(QString)));

    boxes<<ui->wechat<<ui->qq<<ui->weibo<<ui->github<<ui->alipay<<ui->huawei<<ui->xiaomi<<ui->taobao;
}
void addItemDialog::InitMail()
{
    ui->mail_password->setEchoMode(QLineEdit::Password);
    ui->mail_password->setObjectName("mail_password");
    ui->mail_passwordJudge->setObjectName("mail_passwordJudge");
    ui->mail_passwordJudge->setStyleSheet("border:0px;background-color:transparent");
    ui->mail_passwordJudge->setIcon(QIcon(":/application/qrc/nosee.png"));
    ui->mail_passwordJudge->setStatusTip("nosee");

    QRegExp mailReg("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
    QValidator* mailValidator=new QRegExpValidator(mailReg,0);
    ui->mail_mail->setEditable(true);
    ui->mail_mail->lineEdit()->setValidator(mailValidator);
    ui->mail_mail->lineEdit()->setStyleSheet(styleSheet);
    ui->mail_mail->lineEdit()->setStyleSheet("border:0px");
    ui->mail_mail->setObjectName("mail_mail");
    ui->mail_mailJudge->setObjectName("mail_mailJudge");
    ui->mail_mailJudge->setStyleSheet("border:0px;background-color:transparent");

    ui->mail_subName->setValidator(mailValidator);
    ui->mail_subName->setStyleSheet(styleSheet);
    ui->mail_subName->setObjectName("mail_subName");
    ui->mail_subNameJudge->setObjectName("mail_subNameJudge");
    ui->mail_subNameJudge->setStyleSheet("border:0px;background-color:transparent");

    QRegExp websiteReg("^(http|https)://([\\w-]+\\.)+[\\w-]+(/[\\w-./?%&=]*)?$");
    QValidator* websiteValidator=new QRegExpValidator(websiteReg,0);
    ui->mail_website->setEditable(true);
    ui->mail_website->lineEdit()->setValidator(websiteValidator);
    ui->mail_website->setObjectName("mail_website");
    ui->mail_websiteJudge->setObjectName("mail_websiteJudge");
    ui->mail_website->setObjectName("mail_website");
    ui->mail_websiteJudge->setObjectName("mail_websiteJudge");
    ui->mail_websiteJudge->setStyleSheet("border:0px;background-color:transparent");
    ui->mail_website->lineEdit()->setStyleSheet(styleSheet);
    ui->mail_website->lineEdit()->setStyleSheet("border:0px");

    connect(ui->mail_yes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->mail_no,SIGNAL(clicked()),this,SLOT(no_clicked()));
    connect(ui->mail_passwordJudge,SIGNAL(clicked()),this,SLOT(passwordJudge_clicked()));
    connect(ui->mail_mail,SIGNAL(currentTextChanged(QString)),this,SLOT(mailJudge_edited(QString)));
    connect(ui->mail_subName,SIGNAL(textEdited(QString)),this,SLOT(mailJudge_edited(QString)));
    connect(ui->mail_website,SIGNAL(currentTextChanged(QString)),this,SLOT(websiteJudge_edited(QString)));
}
void addItemDialog::InitJGY()
{
    ui->jgy_password->setEchoMode(QLineEdit::Password);
    ui->jgy_password->setObjectName("jgy_password");
    ui->jgy_passwordJudge->setObjectName("jgy_passwordJudge");
    ui->jgy_passwordJudge->setStyleSheet("border:0px;background-color:transparent");
    ui->jgy_passwordJudge->setIcon(QIcon(":/application/qrc/nosee.png"));
    ui->jgy_passwordJudge->setStatusTip("nosee");

    QRegExp mailReg("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
    QValidator* mailValidator=new QRegExpValidator(mailReg,0);
    ui->jgy_mail->setEditable(true);
    ui->jgy_mail->lineEdit()->setValidator(mailValidator);
    ui->jgy_mail->setObjectName("jgy_mail");
    ui->jgy_mailJudge->setObjectName("jgy_mailJudge");
    ui->jgy_mailJudge->setStyleSheet("border:0px;background-color:transparent");

    QRegExp websiteReg("^(http|https)://([\\w-]+\\.)+[\\w-]+(/[\\w-./?%&=]*)?$");
    QValidator* websiteValidator=new QRegExpValidator(websiteReg,0);
    ui->jgy_website->setEditable(true);
    ui->jgy_website->lineEdit()->setValidator(websiteValidator);
    ui->jgy_website->setObjectName("jgy_website");
    ui->jgy_websiteJudge->setObjectName("jgy_websiteJudge");
    ui->jgy_websiteJudge->setStyleSheet("border:0px;background-color:transparent");
    ui->jgy_website->lineEdit()->setStyleSheet(styleSheet);
    ui->jgy_website->lineEdit()->setStyleSheet("border:0px");

    ui->jgy_mail->lineEdit()->setStyleSheet(styleSheet);
    ui->jgy_mail->lineEdit()->setStyleSheet("border:0px");

    connect(ui->jgy_yes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->jgy_no,SIGNAL(clicked()),this,SLOT(no_clicked()));
    connect(ui->jgy_passwordJudge,SIGNAL(clicked()),this,SLOT(passwordJudge_clicked()));
    connect(ui->jgy_mail,SIGNAL(currentTextChanged(QString)),this,SLOT(mailJudge_edited(QString)));
    connect(ui->jgy_website,SIGNAL(currentTextChanged(QString)),this,SLOT(websiteJudge_edited(QString)));
}
void addItemDialog::InitOther()
{
    ui->other_password->setEchoMode(QLineEdit::Password);
    ui->other_password->setObjectName("other_password");
    ui->other_passwordJudge->setObjectName("other_passwordJudge");
    ui->other_passwordJudge->setStyleSheet("border:0px;background-color:transparent");
    ui->other_passwordJudge->setIcon(QIcon(":/application/qrc/nosee.png"));
    ui->other_passwordJudge->setStatusTip("nosee");

    connect(ui->other_yes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->other_no,SIGNAL(clicked()),this,SLOT(no_clicked()));
    connect(ui->other_passwordJudge,SIGNAL(clicked()),this,SLOT(passwordJudge_clicked()));
}
void addItemDialog::InitGroup()
{
    ui->groupNameJudge->setStyleSheet("border:0px;background-color:transparent");
    QStringList typeList;
    typeList.append("普通密码");
    typeList.append("邮箱密码");
    typeList.append("网络共享服务授权码");
    typeList.append("其他密码");
    ui->groupType->addItems(typeList);
    connect(ui->groupName,SIGNAL(textEdited(QString)),this,SLOT(groupNameJudge_edited(QString)));
    connect(ui->group_yes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->group_no,SIGNAL(clicked()),this,SLOT(no_clicked()));
}
addItemDialog::~addItemDialog()
{
    delete ui;
}
void addItemDialog::yes_clicked()
{
    Widget *p= (Widget *)parentWidget();
    switch(ui->tabWidget->currentIndex())
    {
    case 0:
        if(ui->name->text()==""||ui->nickName->text()==""||ui->password->text()==""||ui->mailJudge->statusTip()=="wrong"||ui->mobileJudge->statusTip()=="wrong"||ui->websiteJudge->statusTip()=="wrong")
            return;
        else
        {
            p->newKey=new KEY;
            p->newKey->flag=1;
            p->newKey->type=0;
            p->newKey->name=ui->name->text();
            p->newKey->nickName=ui->nickName->text();
            p->newKey->id=ui->id->text();
            p->newKey->password=ui->password->text();
            p->newKey->mobile=ui->mobile->currentText();
            p->newKey->mail=ui->mail->currentText();
            p->newKey->website=ui->website->text();
            p->newKey->remark=ui->remark->toPlainText();
            p->newKey->createTime=QDateTime::currentDateTime();
            p->newKey->lastEditTime=QDateTime::currentDateTime();
            for(int i=0;i<8;i++)
                p->newKey->account[i]=boxes[i]->isChecked();
            p->addItemFunction(p->tables[p->stackedWidget->currentIndex()]->name,1);
        }
        break;
    case 1:
        if(ui->mail_mail->currentText()==""||ui->mail_name->text()==""||ui->mail_password->text()==""||ui->mail_website->currentText()==""||ui->mail_mailJudge->statusTip()=="wrong"||ui->mail_subNameJudge->statusTip()=="wrong"||ui->mail_websiteJudge->statusTip()=="wrong")
            return;
        else
        {
            p->newKey=new KEY;
            p->newKey->flag=1;
            p->newKey->type=1;
            p->newKey->name=ui->mail_name->text();
            p->newKey->subName=ui->mail_subName->text();
            p->newKey->password=ui->mail_password->text();
            p->newKey->mail=ui->mail_mail->currentText();
            p->newKey->website=ui->mail_website->currentText();
            p->newKey->remark=ui->mail_remark->toPlainText();
            p->newKey->createTime=QDateTime::currentDateTime();
            p->newKey->lastEditTime=QDateTime::currentDateTime();
            p->addItemFunction(p->tables[p->stackedWidget->currentIndex()]->name,1);
        }
        break;
    case 2:
        if(ui->jgy_name->text()==""||ui->jgy_password->text()==""||ui->jgy_mail->currentText()==""||ui->jgy_website->currentText()==""||ui->jgy_mailJudge->statusTip()=="wrong"||ui->jgy_websiteJudge->statusTip()=="wrong")
            return;
        else
        {
            p->newKey=new KEY;
            p->newKey->flag=1;
            p->newKey->type=2;
            p->newKey->name=ui->jgy_name->text();
            p->newKey->password=ui->jgy_password->text();
            p->newKey->mail=ui->jgy_mail->currentText();
            p->newKey->website=ui->jgy_website->currentText();
            p->newKey->remark=ui->jgy_remark->toPlainText();
            p->newKey->createTime=QDateTime::currentDateTime();
            p->newKey->lastEditTime=QDateTime::currentDateTime();
            p->addItemFunction(p->tables[p->stackedWidget->currentIndex()]->name,1);
        }
        break;
    case 3:
        if(ui->other_name->text()==""||ui->other_password->text()=="")
            return;
        else
        {
            p->newKey=new KEY;
            p->newKey->flag=1;
            p->newKey->type=3;
            p->newKey->name=ui->other_name->text();
            p->newKey->password=ui->other_password->text();
            p->newKey->remark=ui->other_remark->toPlainText();
            p->newKey->createTime=QDateTime::currentDateTime();
            p->newKey->lastEditTime=QDateTime::currentDateTime();
            p->addItemFunction(p->tables[p->stackedWidget->currentIndex()]->name,1);
        }
        break;
    case 4:
        if(ui->groupName->text()==""||ui->groupType->currentText()==""||ui->groupNameJudge->statusTip()=="wrong")
            return;
        else
        {
            p->newGroup=new Table;
            p->newGroup->flag=1;
            p->newGroup->createTime=QDateTime::currentDateTime();
            p->newGroup->lastEditTime=QDateTime::currentDateTime();
            p->newGroup->name=ui->groupName->text();
            p->newGroup->count=0;
            p->newGroup->type=ui->groupType->currentIndex();
            p->newGroup->remark=ui->group_remark->toPlainText();
            if(isNewGroup)
                p->addTableFunction(p->newGroup->name,p->newGroup->type);
            else
                p->editTableNameFunction(p->tables[p->stackedWidget->currentIndex()]->name);
            delete p->newGroup;
        }
        break;
    }
    this->close();
}
void addItemDialog::no_clicked()
{
    Widget *p= (Widget *)parentWidget();
    p->newKey=new KEY;
    p->newKey->flag=0;
    this->close();
}
void addItemDialog::closeEvent(QCloseEvent *e)
{
    e->accept();
    Widget *p= (Widget *)parentWidget();
    p->newKey=new KEY;
    p->newKey->flag=0;
    this->close();
}
void addItemDialog::passwordJudge_clicked()
{
    QPushButton* send=(QPushButton*)sender();
    passwordJudgeFunction(send);
}
void addItemDialog::passwordJudgeFunction(QPushButton* button)
{
    QLineEdit* lineEdit=this->findChild<QLineEdit *>(button->objectName().split("Judge")[0]);
    if(button->statusTip()=="nosee")
    {
        button->setIcon(QIcon(":/application/qrc/see.png"));
        button->setStatusTip("see");
        lineEdit->setEchoMode(QLineEdit::Normal);
    }
    else if(button->statusTip()=="see")
    {
        button->setIcon(QIcon(":/application/qrc/nosee.png"));
        button->setStatusTip("nosee");
        lineEdit->setEchoMode(QLineEdit::Password);
    }
}
void addItemDialog::websiteJudge_edited(const QString &arg)
{
    QString testValue=arg;
    QPushButton* button=this->findChild<QPushButton *>(sender()->objectName()+"Judge");
    QRegExp websiteReg("^(http|https)://([\\w-]+\\.)+[\\w-]+(/[\\w-./?%&=]*)?$");
    QRegExpValidator websiteValidator(websiteReg,0);
    int pos=0;
    if(testValue=="")
    {
        button->setIcon(QIcon());
        button->setStatusTip("");
    }
    else if(QValidator::Acceptable!=websiteValidator.validate(testValue,pos))
    {
        button->setIcon(QIcon(":application/qrc/wrong.png"));
        button->setStatusTip("wrong");
    }
    else
    {
        button->setIcon(QIcon(":application/qrc/right.png"));
        button->setStatusTip("right");
    }
}
void addItemDialog::mailJudge_edited(const QString& arg)
{
    QString testValue=arg;
    QPushButton* button=this->findChild<QPushButton *>(sender()->objectName()+"Judge");
    QRegExp mailReg("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
    QRegExpValidator mailValidator(mailReg,0);
    int pos=0;
    if(testValue=="")
    {
        button->setIcon(QIcon());
        button->setStatusTip("");
    }
    else if(QValidator::Acceptable!=mailValidator.validate(testValue,pos))
    {
        button->setIcon(QIcon(":application/qrc/wrong.png"));
        button->setStatusTip("wrong");
    }
    else
    {
        button->setIcon(QIcon(":application/qrc/right.png"));
        button->setStatusTip("right");
    }
}
void addItemDialog::mobileJudge_edited(const QString &arg)
{
    QString testValue=arg;
    QPushButton* button=this->findChild<QPushButton *>(sender()->objectName()+"Judge");
    QRegExp mobileReg("^1(3\\d|4[5-9]|5[0-35-9]|6[2567]|7[0-8]|8\\d|9[0-35-9])\\d{8}$");
    QRegExpValidator mobileValidator(mobileReg,0);
    int pos=0;
    if(testValue=="")
    {
        button->setIcon(QIcon());
        button->setStatusTip("");
    }
    else if(QValidator::Acceptable!=mobileValidator.validate(testValue,pos))
    {
        button->setIcon(QIcon(":application/qrc/wrong.png"));
        button->setStatusTip("wrong");
    }
    else
    {
        button->setIcon(QIcon(":application/qrc/right.png"));
        button->setStatusTip("right");
    }
}
void addItemDialog::groupNameJudge_edited(const QString &arg)
{
    QString name=arg;
    Widget *p= (Widget *)parentWidget();
    QPushButton* button=this->findChild<QPushButton *>(sender()->objectName()+"Judge");
    bool isValid=true;
    if(name=="")
    {
        isValid=false;
        button->setIcon(QIcon(":application/qrc/wrong.png"));
        button->setStatusTip("wrong");
        ui->groupNameWarning->setText("分组名称不能为空");
    }
    else if(name[0].isDigit())
    {
        isValid=false;
        button->setIcon(QIcon(":application/qrc/wrong.png"));
        button->setStatusTip("wrong");
        ui->groupNameWarning->setText("第一个字符不能为数字");
    }
    else
    {
        for(int i=0;i<p->tableCount;i++)
            if(p->tables[i]->name==name&&isNewGroup)
            {
                isValid=false;
                button->setIcon(QIcon(":application/qrc/wrong.png"));
                button->setStatusTip("wrong");
                ui->groupNameWarning->setText("分组名称\""+name+"\"已存在");
            }
    }
    if(isValid)
    {
        ui->groupNameWarning->clear();
        button->setIcon(QIcon(":application/qrc/right.png"));
        button->setStatusTip("right");
    }
}
