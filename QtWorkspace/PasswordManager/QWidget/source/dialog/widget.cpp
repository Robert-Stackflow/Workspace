#include "dialog/widget.h"
#include "ui_widget.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initFrame();
}
Widget::~Widget()
{
    delete ui;
}
void Widget::initFrame()
{
    //初始化列表
    itemTypes<<itemType("文本",abstractCustomItem::LINEEDIT,abstractCustomItem::NORMAL,abstractCustomItem::OPTIONAL);
    itemTypes<<itemType("密码",abstractCustomItem::LINEEDIT,abstractCustomItem::PASSWORD,abstractCustomItem::REQUIRED);
    itemTypes<<itemType("邮箱",abstractCustomItem::LINEEDIT,abstractCustomItem::MAIL,abstractCustomItem::OPTIONAL);
    itemTypes<<itemType("电话",abstractCustomItem::LINEEDIT,abstractCustomItem::MOBILE,abstractCustomItem::OPTIONAL);
    itemTypes<<itemType("网址",abstractCustomItem::LINEEDIT,abstractCustomItem::WEBSITE,abstractCustomItem::OPTIONAL);
    itemTypes<<itemType("可下拉选择-密码",abstractCustomItem::COMBOBOX,abstractCustomItem::PASSWORD,abstractCustomItem::REQUIRED);
    itemTypes<<itemType("可下拉选择-邮箱",abstractCustomItem::COMBOBOX,abstractCustomItem::MAIL,abstractCustomItem::OPTIONAL);
    itemTypes<<itemType("可下拉选择-电话",abstractCustomItem::COMBOBOX,abstractCustomItem::MOBILE,abstractCustomItem::OPTIONAL);
    itemTypes<<itemType("可下拉选择-网址",abstractCustomItem::COMBOBOX,abstractCustomItem::WEBSITE,abstractCustomItem::OPTIONAL);
    updateQSS();
    myHeaderList();
    this->setWindowTitle("Password Manager");
    this->setWindowIcon(QIcon(":custom/logos/logo.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    //添加自定义标题栏
    m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":custom/logos/logo.png");
    m_titleBar->setWindowTitle("Password Manager");
    m_titleBar->forbiddenMaxmizeButton();
    m_titleBar->setFixedWidth(this->width());
    this->setFixedSize(this->width(),this->height()+m_titleBar->height());

    stackedWidget=new QStackedWidget(this);
    stackedWidget->setGeometry(120,m_titleBar->height()+10,1000,680);

    groupCount=0;
    groupTypes=new class groupTypes();
    autofillInfo=new AUTOFILLINFO;
    optiondialog=new optionDialog(this);
    newitemdialog=new newItemDialog(this);
    newgroupdialog=new newGroupDialog(this);
    grouptypemanagerdialog=new groupTypeManagerDialog(this);
    //添加操作按钮
    int leftEdge=350;
    search=new QLineEdit(this);
    search->setPlaceholderText("键入以搜索/筛选");
    search->setStyleSheet("border-radius:5px");
    search->setGeometry(leftEdge,m_titleBar->height()+710,280,30);
    addGroup=new QPushButton("添加分组",this);
    addGroup->setGeometry(leftEdge+300,m_titleBar->height()+710,80,30);
    addItem=new QPushButton("添加条目",this);
    addItem->setGeometry(leftEdge+400,m_titleBar->height()+710,80,30);
    deleteGroup=new QPushButton("删除分组",this);
    deleteGroup->setGeometry(leftEdge+500,m_titleBar->height()+710,80,30);
    editGroup=new QPushButton("编辑分组",this);
    editGroup->setGeometry(leftEdge+600,m_titleBar->height()+710,80,30);
    save=new QToolButton(this);
    save->setPopupMode(QToolButton::MenuButtonPopup);
    save->setGeometry(leftEdge+700,m_titleBar->height()+710,130,30);
    saveAsMenu = new QMenu;
    saveAsPDF=new QAction("导出为pdf");
    saveAsExcel=new QAction("导出为excel");
    saveAsCSV=new QAction("导出为csv");
    saveAsMenu->addAction(saveAsPDF);
    saveAsMenu->addAction(saveAsCSV);
    saveAsMenu->addAction(saveAsExcel);
    saveAsMenu->setStyleSheet(styleSheet+"QMenu::item{padding-left:15px;}");
    save->setMenu(saveAsMenu);
    save->setDefaultAction(saveAsExcel);
    connect(saveAsExcel,SIGNAL(triggered()),this,SLOT(saveMenuTriggered()));
    connect(saveAsPDF,SIGNAL(triggered()),this,SLOT(saveMenuTriggered()));
    connect(saveAsCSV,SIGNAL(triggered()),this,SLOT(saveMenuTriggered()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveSlot()));

    connect(search,SIGNAL(textEdited(QString)),this,SLOT(searchSlot(QString)));
    connect(addGroup,SIGNAL(clicked()),this,SLOT(newGroupSlot()));
    connect(deleteGroup,SIGNAL(clicked()),this,SLOT(deleteGroupSlot()));
    connect(editGroup,SIGNAL(clicked()),this,SLOT(editGroupSlot()));
    connect(addItem,SIGNAL(clicked()),this,SLOT(newItemSlot()));
    connect(stackedWidget,SIGNAL(currentChanged(int)),this,SLOT(onTabIndexChanged(int)));
    connect(this,SIGNAL(groupCountChanged()),this,SLOT(onGroupCountChanged()));
    connect(m_titleBar->m_optionButton,SIGNAL(clicked()),this,SLOT(optionButtonClicked()));

    //    loadUserData();
}
