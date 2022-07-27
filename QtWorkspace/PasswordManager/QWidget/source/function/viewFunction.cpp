#include "widget.h"
#include "ui_widget.h"
#include "util/databasetablenamegetter.h"
#include "util/datapathgetter.h"
#include "util/shareddata.h"
#include "QsLog.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
void Widget::updateQSS()
{
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen()){
        QString temp = this->styleSheet;
        temp+= QLatin1String(file.readAll());
        this->styleSheet=temp;
        this->setStyleSheet(styleSheet);
        file.close();
    }
}
void Widget::updateTableWidgetView(int index)
{
    for(int i=0;i<tableWidgets[index]->rowCount();i++)
        for(int j=0;j<tableWidgets[index]->columnCount();j++)
            tableWidgets[index]->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}
void Widget::changeTab()
{
    SharedData& sharedData = SharedData::instace();
    for(int i=0;i<sharedData.groupList.count();i++)
        buttons[i]->setStyleSheet("");
    QPushButton* send=(QPushButton*)sender();
    int index=stackedWidget->currentIndex();
    Group* currentGroup=sharedData.groupList[index];
    send->setStyleSheet("background-color:#00b7c3");
    stackedWidget->setCurrentIndex(send->objectName().toInt());
    tableWidgetMenu=new QMenu(tableWidgets[index]);
    QList<QAction*> tableMenu;
    QAction *removeItem=new QAction("删除密码");
    QAction *openWebsite=new QAction("访问官网");
    QAction *copyItemInfo=new QAction("复制到剪切板");
    connect(removeItem,SIGNAL(triggered()),this,SLOT(removeKeyItemSlot()));
    connect(openWebsite,SIGNAL(triggered()),this,SLOT(openWebsiteSlot()));
    connect(copyItemInfo,SIGNAL(triggered()),this,SLOT(copyKeyItemInfoSlot()));
    tableMenu<<removeItem<<openWebsite<<copyItemInfo;
    tableWidgetMenu->addActions(tableMenu);
    QMenu* moveMenu=new QMenu("移动至");
    QMenu* copyMenu=new QMenu("复制至");
    moveMenu->setStyleSheet(styleSheet+"QMenu::item{padding-left:15px;}");
    int count1=fillMoveMenu(moveMenu,currentGroup->getGroupType(),0);
    copyMenu->setStyleSheet(styleSheet+"QMenu::item{padding-left:15px;}");
    int count2=fillMoveMenu(copyMenu,currentGroup->getGroupType(),1);
    if(count1>0)
        tableWidgetMenu->addMenu(moveMenu);
    else
        delete moveMenu;
    if(count2>0)
        tableWidgetMenu->addMenu(copyMenu);
    else
        delete copyMenu;
    tableWidgets[index]->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tableWidgets[index],SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(tableWidgetContextMenuRequested(QPoint)));
}
void Widget::onTabIndexChanged(int index)
{
    SharedData& sharedData = SharedData::instace();
    for(int i=0;i<sharedData.groupList.count();i++)
        buttons[i]->setStyleSheet("");
    buttons[index]->setStyleSheet("background-color:#00b7c3");
}
void Widget::onGroupTypeCountChanged()
{
    SharedData& sharedData = SharedData::instace();
    this->newgroupdialog->newGroupType->clear();
    this->newgroupdialog->newGroupType->addItems(sharedData.groupTypeList.getGroupTypeNames());
}
void Widget::onGroupCountChanged()
{
    SharedData& sharedData = SharedData::instace();
    if(sharedData.groupList.count()==0){
        stackedWidget->hide(),addItem->hide(),deleteGroup->hide(),editGroup->hide(),save->hide(),search->hide();
    }else{
        buttons[0]->click();
        stackedWidget->show(),addItem->show(),deleteGroup->show(),editGroup->show(),save->show(),search->show();
    }
    if(sharedData.groupList.count()<=1)
        deleteGroup->setEnabled(false);
    else
        deleteGroup->setEnabled(true);
}
void Widget::onOptionButtonClicked()
{
    //    optiondialog->setModal(true);
    //    optiondialog->setGeometry(this->geometry().x()+this->width()/2-newitemdialog->width()/2+10,this->geometry().y()+this->height()/2-newitemdialog->height()/2+20,newitemdialog->width(),newitemdialog->height());
    //    optiondialog->exec();
    newgrouptypedialog->setModal(true);
    newgrouptypedialog->setGeometry(this->geometry().x()+this->width()/2-newgrouptypedialog->width()/2+10,this->geometry().y()+this->height()/2-newgrouptypedialog->height()/2-10,newgrouptypedialog->width(),newgrouptypedialog->height());
    newgrouptypedialog->exec();
}
