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
    customTitleBar=new class CustomTitleBar(this);
    customTitleBar->setWindowIcon(":custom/logos/logo.png");
    customTitleBar->setWindowTitle("Password Manager");
    customTitleBar->setFixedWidth(this->width());
    userButton=new QPushButton(this);
    userButton->setObjectName("userButton");
    userButton->setIcon(QIcon(":custom/icons/unlogged.png"));
    optionButton=new QPushButton(this);
    optionButton->setObjectName("optionButton");
    optionButton->setIcon(QIcon(":custom/icons/setting.png"));
    customTitleBar->addCustomButton(userButton);
    customTitleBar->addCustomButton(optionButton);
//    this->setFixedSize(this->width(),this->height()+customTitleBar->height());
    //dialog
    optiondialog=new optionDialog(this);
    newitemdialog=new newItemDialog(this);
    newgroupdialog=new newGroupDialog(this);
    newgrouptypedialog=new newGroupTypeDialog(this);
    //    //主要布局
    //    QVBoxLayout* mainLayout=new QVBoxLayout(this);
    //    //头部布局
    //    QHBoxLayout* topLayout=new QHBoxLayout(this);
    //    //左栏布局
    //    listWidget->setGeometry(20,customTitleBar->height()+10,150,680);
    //    //右栏布局
    //    QVBoxLayout* rightLayout=new QVBoxLayout(this);
    //    //右栏分组信息布局
    //    QHBoxLayout* groupInfoLayout=new QHBoxLayout(this);
    //    groupNameLabel=new QLabel(this);
    //    groupNameLabel->setGeometry(180,customTitleBar->height()+10,200,50);
    ui->groupNameLabel->setFont(QFont("Microsoft YaHei", 13, 75));
    ui->groupNameLabel->setScaledContents(true);
    //    groupDescribeLabel=new QLabel(this);
    //    groupDescribeLabel->setGeometry(groupNameLabel->geometry().x()+groupNameLabel->width()+10,customTitleBar->height()+10,1050,50);
    ui->groupDescribeLabel->setFont(QFont("Microsoft YaHei", 10, 25));
    ui->groupDescribeLabel->setScaledContents(true);
    ui->groupDescribeLabel->setWordWrap(true);
    ui->groupDescribeLabel->setAlignment(Qt::AlignBottom);
    ui->groupDescribeLabel->setMargin(8);
//    ui->groupNameLabel->setStyleSheet("border:1px solid white");
//    ui->groupDescribeLabel->setStyleSheet("border:1px solid white");
    //    groupInfoLayout->addWidget(groupNameLabel);
    //    groupInfoLayout->addWidget(groupDescribeLabel);
    //    //右栏分组内容布局
    //    tabWidget=new QTabWidget(this);
    //    tabWidget->setGeometry(170,customTitleBar->height()+50,1020,650);
    ui->tabWidget->tabBar()->hide();
//    ui->tabWidget->setStyleSheet("QTabWidget::pane{border:0px;}");
    //    rightLayout->addLayout(groupInfoLayout);
    //    rightLayout->addWidget(tabWidget);
    //    topLayout->addWidget(listWidget);
    //    topLayout->addLayout(rightLayout);
    //    //底部操作布局
    //    QHBoxLayout* bottomLayout=new QHBoxLayout(this);
    //    int leftEdge=330;
    //    search=new QLineEdit(this);
    ui->search->setPlaceholderText("键入以搜索/筛选");
    ui->search->setStyleSheet("border-radius:5px");
    ui->addGroup->setText("添加分组");
    ui->deleteGroup->setText("删除分组");
    ui->editGroup->setText("编辑分组");
    ui->addItem->setText("添加条目");
    ui->addGroup->setText("添加分组");
    //    search->setGeometry(leftEdge,customTitleBar->height()+710,280,30);
    //    addGroup=new QPushButton("添加分组",this);
    //    addGroup->setGeometry(leftEdge+300,customTitleBar->height()+710,80,30);
    //    addItem=new QPushButton("添加条目",this);
    //    addItem->setGeometry(leftEdge+400,customTitleBar->height()+710,80,30);
    //    deleteGroup=new QPushButton("删除分组",this);
    //    deleteGroup->setGeometry(leftEdge+500,customTitleBar->height()+710,80,30);
    //    editGroup=new QPushButton("编辑分组",this);
    //    editGroup->setGeometry(leftEdge+600,customTitleBar->height()+710,80,30);
    //    save=new QToolButton(this);
    ui->save->setPopupMode(QToolButton::MenuButtonPopup);
    //        save->setGeometry(leftEdge+700,customTitleBar->height()+710,130,30);

    saveAsMenu = new QMenu;
    saveAsPDF=new QAction("导出为pdf");
    saveAsExcel=new QAction("导出为excel");
    saveAsCSV=new QAction("导出为csv");
    saveAsMenu->addAction(saveAsPDF);
    saveAsMenu->addAction(saveAsCSV);
    saveAsMenu->addAction(saveAsExcel);
    saveAsMenu->setStyleSheet(styleSheet+"QMenu::item{padding-left:15px;}");
    ui->save->setMenu(saveAsMenu);
    ui->save->setDefaultAction(saveAsExcel);
    connect(saveAsExcel,SIGNAL(triggered()),this,SLOT(saveMenuTriggered()));
    connect(saveAsPDF,SIGNAL(triggered()),this,SLOT(saveMenuTriggered()));
    connect(saveAsCSV,SIGNAL(triggered()),this,SLOT(saveMenuTriggered()));
    connect(ui->save,SIGNAL(clicked()),this,SLOT(saveSlot()));
    connect(ui->search,SIGNAL(textEdited(QString)),this,SLOT(searchSlot(QString)));
    connect(ui->addGroup,SIGNAL(clicked()),this,SLOT(newGroupSlot()));
    connect(ui->deleteGroup,SIGNAL(clicked()),this,SLOT(deleteGroupSlot()));
    connect(ui->editGroup,SIGNAL(clicked()),this,SLOT(editGroupSlot()));
    connect(ui->addItem,SIGNAL(clicked()),this,SLOT(newKeyItemSlot()));
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(onTabIndexChanged(int)));
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(onListWidgetIndexChanged(int)));
    connect(this,SIGNAL(groupCountChanged()),this,SLOT(onGroupCountChanged()));
    connect(optionButton,SIGNAL(clicked()),this,SLOT(onOptionButtonClicked()));

    loadUserData();
}
