#include "widget.h"
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
    updateQSS();
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

    optiondialog=new optionDialog(this);
    newitemdialog=new newItemDialog(this);
    newgroupdialog=new newGroupDialog(this);
    newgrouptypedialog=new newGroupTypeDialog(this);
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
    connect(addItem,SIGNAL(clicked()),this,SLOT(newKeyItemSlot()));
    connect(stackedWidget,SIGNAL(currentChanged(int)),this,SLOT(onTabIndexChanged(int)));
    connect(this,SIGNAL(groupCountChanged()),this,SLOT(onGroupCountChanged()));
    connect(m_titleBar->m_optionButton,SIGNAL(clicked()),this,SLOT(onOptionButtonClicked()));

    loadUserData();
}
