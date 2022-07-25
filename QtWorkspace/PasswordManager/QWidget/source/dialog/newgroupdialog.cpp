#include "dialog/newgroupdialog.h"
#include "ui_newgroupdialog.h"
#include "widget.h"
#include "util/data.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
using namespace Data;
newGroupDialog::newGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGroupDialog)
{
    ui->setupUi(this);
    //添加自定义控件
    newGroupName=new customLineEdit("分组名称",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
    newGroupName->setPlaceholderText("输入分组名称");
    ui->groupInfoLayout->addWidget(newGroupName);
    newGroupType=new customComboBox("分组类型",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
    ui->groupInfoLayout->addWidget(newGroupType);
    newGroupType->setEditable(false);
    newGroupType->addItems(sharedData.groupTypeList.getGroupTypeNames());
    //绑定槽函数
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(onConfirmClicked()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(onCancelClicked()));
    connect(ui->jumpToGroupTypeManager,SIGNAL(clicked()),this,SLOT(onJumpToGroupTypeManagerClicked()));
}
void newGroupDialog::InitDialog(){
    //删除标题栏
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义标题栏
    m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":/custom/logos/logo.png");
    //设置标题栏字体
    QFont font;
    font.setBold(true);
    font.setPointSize(11);
    font.setFamily("黑体");
    m_titleBar->m_titleLabel->setFont(font);
    //隐藏标题栏按钮
    m_titleBar->forbiddenUserButton();
    m_titleBar->forbiddenMaxmizeButton();
    //设定标题栏位置与大小
    m_titleBar->setFixedWidth(ui->frame->width());
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    //设定阴影效果
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor(128,128,128,255));
    shadow_effect->setBlurRadius(20);
    shadow_effect->setOffset(0, 0);
    ui->frame->setGraphicsEffect(shadow_effect);
    //隐藏tabWidget标题栏
    ui->tabWidget->tabBar()->hide();
    //加载QSS样式
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString temp = this->styleSheet;
        temp += QLatin1String(file.readAll());
        this->styleSheet=temp;
        this->setStyleSheet(styleSheet);
        file.close();
    }
}
newGroupDialog::~newGroupDialog()
{
    delete ui;
}
void newGroupDialog::setWindowTitle(const QString& title){
    m_titleBar->setWindowTitle(title);
}
void newGroupDialog::onConfirmClicked(){
    if(newGroupName->isValid()&&newGroupType->isValid())
    {
        newGroup=new Group(newGroupType->currentIndex(),newGroupName->text(),QDateTime::currentDateTime(),QDateTime::currentDateTime(),ui->describe->toPlainText());
        newGroup->setFlag(1);
        this->close();
    }else{
        QString message="";
        if(!newGroupName->isValid())
            message+="分组名称不合法!\n";
        if(!newGroupType->isValid())
            message+="分组类型不合法!\n";
        QMessageBox::warning(this,"警告",message);
    }
}
void newGroupDialog::onCancelClicked(){
    int choice=QMessageBox::question(this,"确认修改","是否放弃新建分组");
    if(choice==QMessageBox::Yes){
        newGroup=nullptr;
        this->close();
    }
}
void newGroupDialog::setCurrentMode(mode newCurrentMode){
    this->currentMode=newCurrentMode;
    if(currentMode==NEWGROUP)
        newGroupType->setEnable(false);
}

void newGroupDialog::onJumpToGroupTypeManagerClicked()
{
    Widget* parent=(Widget*)this->parent();
    newGroupTypeDialog* grouptypemanagerdialog=parent->newgrouptypedialog;
    grouptypemanagerdialog->setModal(true);
    grouptypemanagerdialog->setGeometry(this->geometry().x()+this->width()/2-grouptypemanagerdialog->width()/2+10,this->geometry().y()+this->height()/2-grouptypemanagerdialog->height()/2-10,grouptypemanagerdialog->width(),grouptypemanagerdialog->height());
    grouptypemanagerdialog->exec();
}

