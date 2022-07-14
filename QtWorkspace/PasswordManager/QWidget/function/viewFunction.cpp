#include "widget.h"
#include "ui_widget.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
void Widget::updateQSS()
{
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
}
void Widget::updateTableWidgetView(int index)
{
    for(int i=0;i<tableWidgets[index]->rowCount();i++)
        for(int j=0;j<tableWidgets[index]->columnCount();j++)
            tableWidgets[index]->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}
void Widget::changeTab()
{
    for(int i=0;i<tableCount;i++)
        buttons[i]->setStyleSheet("");
    QPushButton* send=(QPushButton*)sender();
    stackedWidget->setCurrentIndex(send->objectName().toInt());
    send->setStyleSheet("background-color:#00b7c3");
    tableWidgetMenu= new QMenu(tableWidgets[stackedWidget->currentIndex()]);
    QList<QAction*> tableMenu;
    QAction *removeItem=new QAction("删除密码");
    QAction *openWebsite=new QAction("访问官网");
    QAction *copyAll=new QAction("复制到剪切板");
    QMenu* moveMenu=new QMenu("移动至");
    QMenu* copyMenu=new QMenu("复制至");
    moveMenu->setStyleSheet(styleSheet+"QMenu::item{padding-left:15px;}");
    int count1=fillMoveMenu(moveMenu,tables[stackedWidget->currentIndex()]->type,0);
    copyMenu->setStyleSheet(styleSheet+"QMenu::item{padding-left:15px;}");
    int count2=fillMoveMenu(copyMenu,tables[stackedWidget->currentIndex()]->type,1);
    connect(removeItem,SIGNAL(triggered()),this,SLOT(removeItemSlot()));
    connect(openWebsite,SIGNAL(triggered()),this,SLOT(openWebsiteSlot()));
    connect(copyAll,SIGNAL(triggered()),this,SLOT(copyAllSlot()));
    tableMenu<<removeItem<<openWebsite<<copyAll;
    tableWidgetMenu->addActions(tableMenu);
    if(count1>0)
        tableWidgetMenu->addMenu(moveMenu);
    else
        delete moveMenu;
    if(count2>0)
        tableWidgetMenu->addMenu(copyMenu);
    else
        delete copyMenu;
    tableWidgets[stackedWidget->currentIndex()]->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tableWidgets[stackedWidget->currentIndex()],SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(tableWidgetContextMenuRequested(QPoint)));
}
int Widget::fillMoveMenu(QMenu * menu, int type, int mode)
{
    int count=0;
    for(int i=0;i<tables.size();i++)
    {
        if(tables[i]->type==type&&tables[i]->name!=tables[stackedWidget->currentIndex()]->name)
        {
            count++;
            QAction* temp=new QAction(tables[i]->name);
            menu->addAction(temp);
            if(mode==0)
                connect(temp,SIGNAL(triggered()),this,SLOT(moveMenuSlot()));
            else if(mode==1)
                connect(temp,SIGNAL(triggered()),this,SLOT(copyMenuSlot()));
        }
    }
    return count;
}
void Widget::onTabIndexChanged(int index)
{
    for(int i=0;i<tableCount;i++)
        buttons[i]->setStyleSheet("");
    buttons[index]->setStyleSheet("background-color:#00b7c3");
}
void Widget::onTableCountChanged()
{
    if(tableCount==0)
        stackedWidget->hide(),addItem->hide(),deleteTable->hide(),editTableName->hide(),save->hide();
    else
    {
        buttons[0]->click();
        stackedWidget->show(),addItem->show(),deleteTable->show(),editTableName->show(),save->show();
    }
    if(tableCount==1)
        deleteTable->setEnabled(false);
    else
        deleteTable->setEnabled(true);
}
void Widget::myHeaderList()
{
    QStringList commonHeader;
    commonHeader<<"应用名称"<<"昵称"<<"用户名"<<"密码"<<"手机"<<"邮箱"<<"官网"<<"备注"<<"创建时间"<<"修改时间";
    QStringList mailHeader;
    mailHeader<<"名称"<<"邮箱"<<"邮箱别名"<<"邮箱密码"<<"官网"<<"备注"<<"创建时间"<<"修改时间";
    QStringList jianguoyunHeader;
    jianguoyunHeader<<"名称"<<"邮箱"<<"网址"<<"授权码"<<"备注"<<"创建时间"<<"修改时间";
    QStringList otherHeader;
    otherHeader<<"名称"<<"密码"<<"备注"<<"创建时间"<<"修改时间";
    header<<commonHeader<<mailHeader<<jianguoyunHeader<<otherHeader;
}
void Widget::optionButtonClicked()
{
    optiondialog->setModal(true);
    optiondialog->setGeometry(this->geometry().x()+this->width()/2-additemdialog->width()/2+10,this->geometry().y()+this->height()/2-additemdialog->height()/2+20,additemdialog->width(),additemdialog->height());
    optiondialog->exec();
}
