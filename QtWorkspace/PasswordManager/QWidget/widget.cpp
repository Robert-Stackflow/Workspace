#include "widget.h"
#include "ui_widget.h"
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
    myHeaderList();
    this->setWindowTitle("Password Manager");
    this->setWindowIcon(QIcon(":/application/qrc/icon.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);

    m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":/application/qrc/icon.png");
    m_titleBar->setWindowTitle("Password Manager");
    m_titleBar->forbiddenMaxmizeButton();
    m_titleBar->setFixedWidth(this->width());
    this->setFixedSize(this->width(),this->height()+m_titleBar->height());

    stackedWidget=new QStackedWidget(this);
    stackedWidget->setGeometry(120,m_titleBar->height()+10,1000,680);

    tableCount=0;
    personInfo=new INFO;
    additemdialog=new addItemDialog(this);
    optiondialog=new optionDialog(this);

    search=new QLineEdit(this);
    search->setPlaceholderText("键入以搜索/筛选");
    search->setStyleSheet("border-radius:5px");
    search->setGeometry(400,m_titleBar->height()+710,280,30);
    addTable=new QPushButton("添加分组",this);
    addTable->setGeometry(700,m_titleBar->height()+710,80,30);
    addItem=new QPushButton("添加条目",this);
    addItem->setGeometry(800,m_titleBar->height()+710,80,30);
    deleteTable=new QPushButton("删除分组",this);
    deleteTable->setGeometry(900,m_titleBar->height()+710,80,30);
    editTableName=new QPushButton("编辑名称",this);
    editTableName->setGeometry(1000,m_titleBar->height()+710,80,30);
    save=new QToolButton(this);
    save->setPopupMode(QToolButton::MenuButtonPopup);
    save->setGeometry(1100,m_titleBar->height()+710,80,30);
    menu = new QMenu;
    saveAsPDF=new QAction("pdf");
    saveAsExcel=new QAction("excel");
    saveAsCSV=new QAction("txt");
    menu->addAction(saveAsPDF);
    menu->addAction(saveAsCSV);
    menu->addAction(saveAsExcel);
    menu->setStyleSheet(styleSheet+"QMenu::item{padding-left:15px;}");
    save->setMenu(menu);
    save->setDefaultAction(saveAsExcel);
    connect(saveAsExcel,SIGNAL(triggered()),this,SLOT(saveMenuTriggered()));
    connect(saveAsPDF,SIGNAL(triggered()),this,SLOT(saveMenuTriggered()));
    connect(saveAsCSV,SIGNAL(triggered()),this,SLOT(saveMenuTriggered()));
    connect(save,SIGNAL(clicked()),this,SLOT(saveSlot()));

    connect(search,SIGNAL(textEdited(QString)),this,SLOT(searchSlot(QString)));
    connect(addTable,SIGNAL(clicked()),this,SLOT(addTableSlot()));
    connect(deleteTable,SIGNAL(clicked()),this,SLOT(deleteTableSlot()));
    connect(editTableName,SIGNAL(clicked()),this,SLOT(editTableNameSlot()));
    connect(addItem,SIGNAL(clicked()),this,SLOT(addItemSlot()));
    connect(stackedWidget,SIGNAL(currentChanged(int)),this,SLOT(onTabIndexChanged(int)));
    connect(this,SIGNAL(tableCountChanged()),this,SLOT(onTableCountChanged()));
    connect(m_titleBar->m_optionButton,SIGNAL(clicked()),this,SLOT(optionButtonClicked()));

    loadUserData();
}
