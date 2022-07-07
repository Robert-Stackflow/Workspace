#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDesktopServices>
int times=0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initFrame();
}
void MainWindow::initFrame()
{
    mainWidget = new QWidget();
    this->setCentralWidget(mainWidget);
    updateQSS();
    myHeaderList();
    this->setWindowTitle("Password Manager");
    this->setWindowIcon(QIcon(":/application/qrc/icon.png"));
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);

    m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":/application/qrc/icon.png");
    m_titleBar->setWindowTitle("Password Manager");
    m_titleBar->forbiddenMaxmizeButton();
    m_titleBar->setFixedWidth(this->width());
    this->setFixedSize(this->width(),this->height()+m_titleBar->height());

    stackedWidget=new QStackedWidget(mainWidget);
    stackedWidget->setGeometry(120,m_titleBar->height()+20,1000,680);

    tableCount=0;
    personInfo=new INFO;
    additemdialog=new addItemDialog(mainWidget);

    addTable=new QPushButton("添加分组",mainWidget);
    addTable->setGeometry(700,m_titleBar->height()+710,80,30);
    addItem=new QPushButton("添加条目",mainWidget);
    addItem->setGeometry(800,m_titleBar->height()+710,80,30);
    deleteTable=new QPushButton("删除分组",mainWidget);
    deleteTable->setGeometry(900,m_titleBar->height()+710,80,30);
    editTableName=new QPushButton("编辑名称",mainWidget);
    editTableName->setGeometry(1000,m_titleBar->height()+710,80,30);
    save=new QPushButton("导出分组",mainWidget);
    save->setGeometry(1100,m_titleBar->height()+710,80,30);

    mainLayout=new QVBoxLayout();
    bottomLayout=new QHBoxLayout();
    rightLayout=new QVBoxLayout();
    operationsLayout=new QHBoxLayout();
    buttonsLayout=new QVBoxLayout();

    operationsLayout->addSpacing(700);
    operationsLayout->addWidget(addTable);
    operationsLayout->addWidget(addItem);
    operationsLayout->addWidget(deleteTable);
    operationsLayout->addWidget(editTableName);
    operationsLayout->addWidget(save);

    rightLayout->addWidget(stackedWidget);
    rightLayout->addLayout(operationsLayout);

    bottomLayout->addLayout(buttonsLayout);
    bottomLayout->addLayout(rightLayout);

    mainLayout->addWidget(m_titleBar);
    mainLayout->addLayout(bottomLayout);

    mainWidget->setLayout(mainLayout);

    connect(addTable,SIGNAL(clicked()),this,SLOT(addTableSlot()));
    connect(deleteTable,SIGNAL(clicked()),this,SLOT(deleteTableSlot()));
    connect(editTableName,SIGNAL(clicked()),this,SLOT(editTableNameSlot()));
    connect(addItem,SIGNAL(clicked()),this,SLOT(addItemSlot()));
    connect(stackedWidget,SIGNAL(currentChanged(int)),this,SLOT(onTabIndexChanged(int)));
    connect(this,SIGNAL(tableCountChanged()),this,SLOT(onTableCountChanged()));

    loadUserData();

}
void MainWindow::onTableCountChanged()
{
    if(tableCount==0)
        stackedWidget->hide(),addItem->hide(),deleteTable->hide(),editTableName->hide(),save->hide();
    else
        stackedWidget->show(),addItem->show(),deleteTable->show(),editTableName->show(),save->show();
}
void MainWindow::myHeaderList()
{
    QStringList commonHeader;
    commonHeader<<"应用名称"<<"昵称"<<"用户名"<<"密码"<<"手机"<<"邮箱"<<"官网"<<"备注";
    QStringList mailHeader;
    mailHeader<<"名称"<<"邮箱"<<"邮箱别名"<<"邮箱密码"<<"官网"<<"备注";
    QStringList jianguoyunHeader;
    jianguoyunHeader<<"名称"<<"邮箱"<<"网址"<<"授权码"<<"备注";
    QStringList otherHeader;
    otherHeader<<"名称"<<"密码"<<"备注";
    header<<commonHeader<<mailHeader<<jianguoyunHeader<<otherHeader;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::addItemSlot()
{
    additemdialog->ui->tabWidget->setCurrentIndex(tables[stackedWidget->currentIndex()]->type);
    additemdialog->setWindowTitle("在分组\""+tables[stackedWidget->currentIndex()]->name+"\"中添加密码");
    additemdialog->m_titleBar->setWindowTitle("在分组\""+tables[stackedWidget->currentIndex()]->name+"\"中添加条目");
    //清除“普通密码”内容
    additemdialog->ui->nickName->clear();
    additemdialog->ui->id->clear();
    additemdialog->ui->mail->clearEditText();
    additemdialog->ui->mobile->clearEditText();
    additemdialog->ui->name->clear();
    additemdialog->ui->password->clear();
    additemdialog->ui->remark->clear();
    additemdialog->ui->website->clear();
    additemdialog->ui->websiteJudge->setIcon(QIcon());
    for(int i=0;i<additemdialog->boxes.size();i++)
        additemdialog->boxes[i]->setChecked(false);
    //清除“邮箱密码”内容
    additemdialog->ui->mail_mail->clearEditText();
    additemdialog->ui->mail_name->clear();
    additemdialog->ui->mail_subName->clear();
    additemdialog->ui->mail_password->clear();
    additemdialog->ui->mail_remark->clear();
    additemdialog->ui->mail_website->clearEditText();
    additemdialog->ui->mail_subNameJudge->setIcon(QIcon());
    //清除“授权码”内容
    additemdialog->ui->jgy_mail->clearEditText();
    additemdialog->ui->jgy_name->clear();
    additemdialog->ui->jgy_password->clear();
    additemdialog->ui->jgy_remark->clear();
    additemdialog->ui->jgy_website->clearEditText();
    //清除“其他密码”内容
    additemdialog->ui->other_name->clear();
    additemdialog->ui->other_password->clear();
    additemdialog->ui->other_remark->clear();
    //打开Dialog
    additemdialog->setModal(true);
    additemdialog->setGeometry(this->geometry().x()+this->width()/2-additemdialog->width()/2+10,this->geometry().y()+this->height()/2-additemdialog->height()/2+20,additemdialog->width(),additemdialog->height());
    additemdialog->exec();
}
void MainWindow::addItemFunction(QString& tableName,int mode)
{//mode=1表示插入,mode=0表示加载
    if(newKey!=NULL&&newKey->flag)
    {
        int index=0;
        for(int j=0;j<tables.size();j++)
        {
            if(tableName==tables[j]->name)
                index=j;
        }
        QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
        data.setDatabaseName("user.db");
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            switch(newKey->type)
            {
            case 0:
                if(mode==1)
                {
                    query.prepare("insert into "+tableName+" (type,name,nickName,id,password,mobile,mail,website,remark,createTime,lastEditTime)"
                                                           "VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9,:10,:11)");
                    query.bindValue(":1",newKey->type);
                    query.bindValue(":2",newKey->name);
                    query.bindValue(":3",newKey->nickName);
                    query.bindValue(":4",newKey->id);
                    query.bindValue(":5",newKey->password);
                    query.bindValue(":6",newKey->mobile);
                    query.bindValue(":7",newKey->mail);
                    query.bindValue(":8",newKey->website);
                    query.bindValue(":9",newKey->remark);
                    query.bindValue(":10",newKey->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                    query.bindValue(":11",newKey->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
                    query.exec();
                }
                tableWidgets[index]->insertRow(tableWidgets[index]->rowCount());
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,0,new QTableWidgetItem(newKey->name));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,1,new QTableWidgetItem(newKey->nickName));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,2,new QTableWidgetItem(newKey->id));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,3,new QTableWidgetItem(newKey->password));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,4,new QTableWidgetItem(newKey->mobile));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,5,new QTableWidgetItem(newKey->mail));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,6,new QTableWidgetItem(newKey->website));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,7,new QTableWidgetItem(newKey->remark));
                break;
            case 1:
                if(mode==1)
                {
                    query.prepare("insert into "+tableName+" (type,name,mail,subName,password,website,remark,createTime,lastEditTime)"
                                                           "VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9)");
                    query.bindValue(":1",newKey->type);
                    query.bindValue(":2",newKey->name);
                    query.bindValue(":3",newKey->mail);
                    query.bindValue(":4",newKey->subName);
                    query.bindValue(":5",newKey->password);
                    query.bindValue(":6",newKey->website);
                    query.bindValue(":7",newKey->remark);
                    query.bindValue(":8",newKey->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                    query.bindValue(":9",newKey->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
                    query.exec();
                }
                tableWidgets[index]->insertRow(tableWidgets[index]->rowCount());
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,0,new QTableWidgetItem(newKey->name));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,1,new QTableWidgetItem(newKey->mail));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,2,new QTableWidgetItem(newKey->subName));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,3,new QTableWidgetItem(newKey->password));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,4,new QTableWidgetItem(newKey->website));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,5,new QTableWidgetItem(newKey->remark));
                break;
            case 2:
                if(mode==1)
                {
                    query.prepare("insert into "+tableName+" (type,name,mail,password,website,remark,createTime,lastEditTime)"
                                                           "VALUES (:1,:2,:3,:4,:5,:6,:7,:8)");
                    query.bindValue(":1",newKey->type);
                    query.bindValue(":2",newKey->name);
                    query.bindValue(":3",newKey->mail);
                    query.bindValue(":4",newKey->password);
                    query.bindValue(":5",newKey->website);
                    query.bindValue(":6",newKey->remark);
                    query.bindValue(":7",newKey->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                    query.bindValue(":8",newKey->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
                    query.exec();
                }
                tableWidgets[index]->insertRow(tableWidgets[index]->rowCount());
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,0,new QTableWidgetItem(newKey->name));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,1,new QTableWidgetItem(newKey->mail));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,2,new QTableWidgetItem(newKey->password));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,3,new QTableWidgetItem(newKey->website));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,4,new QTableWidgetItem(newKey->remark));
                break;
            case 3:
                if(mode==1)
                {
                    query.prepare("insert into "+tableName+" (type,name,password,remark,createTime,lastEditTime)"
                                                           "VALUES (:1,:2,:3,:4,:5,:6)");
                    query.bindValue(":1",newKey->type);
                    query.bindValue(":2",newKey->name);
                    query.bindValue(":3",newKey->password);
                    query.bindValue(":4",newKey->remark);
                    query.bindValue(":5",newKey->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                    query.bindValue(":6",newKey->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
                    query.exec();
                }
                tableWidgets[index]->insertRow(tableWidgets[index]->rowCount());
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,0,new QTableWidgetItem(newKey->name));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,1,new QTableWidgetItem(newKey->password));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,2,new QTableWidgetItem(newKey->remark));
                break;
            }
            updateTableWidgetView(index);
            if(mode==1)
            {
                if(personInfo!=NULL&&!personInfo->mails.contains(newKey->mail))
                    personInfo->mails<<newKey->mail,personInfo->subNames<<"";
                if(personInfo!=NULL&&newKey->type==1)
                    personInfo->subNames[personInfo->mails.indexOf(newKey->mail)]=newKey->subName;
                if(personInfo!=NULL&&!personInfo->mobiles.contains(newKey->mobile))
                    personInfo->mobiles<<newKey->mobile;
                if(personInfo!=NULL&&newKey->type==1&&!personInfo->mailWebsites.contains(newKey->website))
                    personInfo->mailWebsites<<newKey->website;
                if(personInfo!=NULL&&newKey->type==2&&!personInfo->jgyWebsites.contains(newKey->website))
                    personInfo->jgyWebsites<<newKey->website;
                updatePersonInfo();
            }
            data.close();
        }
    }
}
void MainWindow::updatePersonInfo()
{
    additemdialog->ui->nickName->clear();
    additemdialog->ui->mail->clear();
    additemdialog->ui->mobile->clear();
    additemdialog->ui->mail->addItems(personInfo->mails);
    additemdialog->ui->mail->addItems(personInfo->subNames);
    additemdialog->ui->mobile->addItems(personInfo->mobiles);
    for(int i=0;i<additemdialog->ui->mail->count();i++)
        if(additemdialog->ui->mail->itemText(i)=="")
            additemdialog->ui->mail->removeItem(i);
    for(int i=0;i<additemdialog->ui->mobile->count();i++)
        if(additemdialog->ui->mobile->itemText(i)=="")
            additemdialog->ui->mobile->removeItem(i);
    additemdialog->ui->mail_mail->clear();
    additemdialog->ui->mail_website->clear();
    additemdialog->ui->mail_mail->addItems(personInfo->mails);
    additemdialog->ui->mail_website->addItems(personInfo->mailWebsites);

    additemdialog->ui->jgy_mail->clear();
    additemdialog->ui->jgy_website->clear();
    additemdialog->ui->jgy_mail->addItems(personInfo->mails);
    additemdialog->ui->jgy_mail->addItems(personInfo->subNames);
    additemdialog->ui->jgy_website->addItems(personInfo->jgyWebsites);
    for(int i=0;i<additemdialog->ui->jgy_mail->count();i++)
        if(additemdialog->ui->jgy_mail->itemText(i)=="")
            additemdialog->ui->jgy_mail->removeItem(i);
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
    data.setDatabaseName("user.db");
    QSqlQuery query(data);
    if(!data.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
        return;
    }
    else
    {
        QString tableName="个人信息";//1-邮箱;2-手机号;3-mailWebsites;4-jgyWebsites
        if(data.tables().contains(tableName))
        {
            query.exec("drop table "+tableName);
        }
        query.exec("create table "+tableName+" (type int,content varchar(100),subContent varchar(100))");
        for(int i=0;i<personInfo->mails.size();i++)
        {
            query.prepare("insert into "+tableName+" (type,content,subContent)"
                                                   "VALUES (:1,:2,:3)");
            query.bindValue(":1",1);
            query.bindValue(":2",personInfo->mails[i]);
            query.bindValue(":3",personInfo->subNames[i]);
            query.exec();
        }
        for(int i=0;i<personInfo->mobiles.size();i++)
        {
            query.prepare("insert into "+tableName+" (type,content,subContent)"
                                                   "VALUES (:1,:2,:3)");
            query.bindValue(":1",2);
            query.bindValue(":2",personInfo->mobiles[i]);
            query.bindValue(":3","");
            query.exec();
        }
        for(int i=0;i<personInfo->mailWebsites.size();i++)
        {
            query.prepare("insert into "+tableName+" (type,content,subContent)"
                                                   "VALUES (:1,:2,:3)");
            query.bindValue(":1",3);
            query.bindValue(":2",personInfo->mailWebsites[i]);
            query.bindValue(":3","");
            query.exec();
        }
        for(int i=0;i<personInfo->jgyWebsites.size();i++)
        {
            query.prepare("insert into "+tableName+" (type,content,subContent)"
                                                   "VALUES (:1,:2,:3)");
            query.bindValue(":1",4);
            query.bindValue(":2",personInfo->jgyWebsites[i]);
            query.bindValue(":3","");
            query.exec();
        }
        data.close();
    }
}
void MainWindow::addTableSlot()
{
    bool flag;
    QString name=QInputDialog::getText(this,"新建分组","分组名称",QLineEdit::Normal,"",&flag,Qt::WindowCloseButtonHint);
    if(flag)
    {
        bool flag1;
        int type=QInputDialog::getText(this,"选择分组类型","0-普通密码;\n1-邮箱密码;\n2-坚果云授权码;\n3-其他密码",QLineEdit::Normal,"",&flag1,Qt::WindowCloseButtonHint).toInt();
        if(flag1)
            addTableFunction(name,type);
    }
}
void MainWindow::deleteTableSlot()
{
    bool flag;
    QString title="删除分组\""+tables[stackedWidget->currentIndex()]->name+"\"";
    QString message="是否"+title;
    flag=QMessageBox::question(this,title,message);
    if(flag)
    {
        QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
        data.setDatabaseName("user.db");
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            query.exec("drop table "+tables[stackedWidget->currentIndex()]->name);
            QString sql = QString("delete from tables where name = '%1' ").arg(tables[stackedWidget->currentIndex()]->name);
            int index=stackedWidget->currentIndex();
            stackedWidget->removeWidget(widgets[index]);
            buttons.at(index)->hide();
            buttons.removeAt(index);
            widgets.removeAt(index);
            tableWidgets.removeAt(index);
            tables.removeAt(index);
            query.exec(sql);
        }
        tableCount--;
    }
}
void MainWindow::editTableNameSlot()
{
    bool flag;
    QString name=tables[stackedWidget->currentIndex()]->name;
    QString newName=QInputDialog::getText(this,"编辑分组","分组名称",QLineEdit::Normal,name,&flag,Qt::WindowCloseButtonHint);
    if(flag)
    {
        buttons[stackedWidget->currentIndex()]->setText(newName);
        QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
        data.setDatabaseName("user.db");
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            query.exec("alter table "+name+" rename to "+newName);
            QString sql=QString("update tables set name='%1' where createTime='%2' ").arg(newName).arg(tables[stackedWidget->currentIndex()]->createTime.toString("yyyy-MM-dd hh:mm:ss"));
            query.exec(sql);
            data.close();
        }
        tables[stackedWidget->currentIndex()]->name=newName;
    }
}
void MainWindow::addTableFunction(QString name,int type)
{
    stackedWidget->show();
    //Init the tableWidget;
    QTableWidget* tempTableWidget=new QTableWidget();
    tableWidgets<<tempTableWidget;
    tableWidgets[tableCount]->setColumnCount(header[type].size());
    tableWidgets[tableCount]->setHorizontalHeaderLabels(header[type]);
    tableWidgets[tableCount]->setAlternatingRowColors(true);
    tableWidgets[tableCount]->verticalHeader()->setDefaultSectionSize(45);
    tableWidgets[tableCount]->horizontalHeader()->setStretchLastSection(true);
    tableWidgets[tableCount]->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    tableWidgets[tableCount]->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidgets[tableCount]->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidgets[tableCount]->verticalHeader()->hide();
    tableWidgets[tableCount]->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<tableWidgets[tableCount]->columnCount();i++)
        tableWidgets[tableCount]->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    //Init the button
    QPushButton* tempButton=new QPushButton(name,mainWidget);
    buttons<<tempButton;
    buttons[tableCount]->setObjectName(QString::number(tableCount));
    if(tableCount==0)
        buttons[tableCount]->setGeometry(20,m_titleBar->height()+20,80,30);
    else
        buttons[tableCount]->setGeometry(20,m_titleBar->height()+buttons[tableCount-1]->geometry().y()+50,80,30);
    buttons[tableCount]->setVisible(true);
    connect(buttons[tableCount],SIGNAL(clicked()),this,SLOT(changeTab()));
    buttonsLayout->addWidget(buttons[tableCount]);
    //Init the TABLE
    TABLE* tempTable=new TABLE;
    tempTable->count=0;
    tempTable->type=type;
    tempTable->name=name;
    tempTable->createTime=QDateTime::currentDateTime();
    tempTable->lastEditTime=QDateTime::currentDateTime();
    tables<<tempTable;
    //Init the newTab in the stackedWidget
    QWidget* tempWidget=new QWidget;
    widgets<<tempWidget;
    QHBoxLayout* tempLayout=new QHBoxLayout;
    tempLayout->addWidget(tableWidgets[tableCount]);
    widgets[tableCount]->setLayout(tempLayout);
    stackedWidget->addWidget(widgets[tableCount]);
    tableCount++;
    //add table in the database
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
    data.setDatabaseName("user.db");
    QSqlQuery query(data);
    if(!data.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
        return;
    }
    else
    {
        if(!data.tables().contains("tables"))
        {
            query.exec("create table tables (type int,name varchar(40),count int,createTime varchar(200),lastEditTime varchar(200))");
        }
        if(!data.tables().contains(tempTable->name))
        {
            switch(type)
            {
            case 0:
                query.exec("create table "+tempTable->name+" (type int,name varchar(20),nickName varchar(20),id varchar(100),password varchar(100),mobile varchar(50),mail varchar(200),website varchar(200),remark varchar(200),createTime varchar(200),lastEditTime varchar(200))");
                query.prepare("insert into tables (type,name,count,createTime,lastEditTime)"
                              "VALUES (:2,:3,:4,:5,:6)");
                query.bindValue(":2",tempTable->type);
                query.bindValue(":3",tempTable->name);
                query.bindValue(":4",tempTable->count);
                query.bindValue(":5",tempTable->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":6",tempTable->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.exec();
                break;
            case 1:
                query.exec("create table "+tempTable->name+" (type int,name varchar(20),mail varchar(20),subName varchar(100),password varchar(100),website varchar(200),remark varchar(200),createTime varchar(200),lastEditTime varchar(200))");
                query.prepare("insert into tables (type,name,count,createTime,lastEditTime)"
                              "VALUES (:2,:3,:4,:5,:6)");
                query.bindValue(":2",tempTable->type);
                query.bindValue(":3",tempTable->name);
                query.bindValue(":4",tempTable->count);
                query.bindValue(":5",tempTable->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":6",tempTable->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.exec();
                break;
            case 2:
                query.exec("create table "+tempTable->name+" (type int,name varchar(20),mail varchar(20),password varchar(100),website varchar(200),remark varchar(200),createTime varchar(200),lastEditTime varchar(200))");
                query.prepare("insert into tables (type,name,count,createTime,lastEditTime)"
                              "VALUES (:2,:3,:4,:5,:6)");
                query.bindValue(":2",tempTable->type);
                query.bindValue(":3",tempTable->name);
                query.bindValue(":4",tempTable->count);
                query.bindValue(":5",tempTable->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":6",tempTable->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.exec();
                break;
            case 3:
                query.exec("create table "+tempTable->name+" (type int,name varchar(20),password varchar(100),remark varchar(200),createTime varchar(200),lastEditTime varchar(200))");
                query.prepare("insert into tables (type,name,count,createTime,lastEditTime)"
                              "VALUES (:2,:3,:4,:5,:6)");
                query.bindValue(":2",tempTable->type);
                query.bindValue(":3",tempTable->name);
                query.bindValue(":4",tempTable->count);
                query.bindValue(":5",tempTable->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":6",tempTable->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.exec();
                break;
            }
        }
        data.close();
    }
    emit tableCountChanged();
}
void MainWindow::loadUserData()
{
    tableCount=0;
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
    data.setDatabaseName("user.db");
    QSqlQuery query(data);
    if(!data.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
        return;
    }
    else
    {
        QStringList tableNames=data.tables();
        tableNames.removeOne("tables");
        tableNames.removeOne("个人信息");
        //load user information;
        QString curTableName="个人信息";
        query.exec("select * from "+curTableName);
        for(int i = 0;query.next(); i++)
        {
            int type=query.value(0).toInt();
            switch(type)
            {
            case 1:
                personInfo->mails<<query.value(1).toString();
                personInfo->subNames<<query.value(2).toString();
                break;
            case 2:
                personInfo->mobiles<<query.value(1).toString();
                break;
            case 3:
                personInfo->mailWebsites<<query.value(1).toString();
                break;
            case 4:
                personInfo->jgyWebsites<<query.value(1).toString();
                break;
            default:
                break;
            }
        }
        //add tables
        curTableName="tables";
        query.exec("select * from "+curTableName);
        for(int i = 0;query.next(); i++)
            addTableFunction(query.value(1).toString(),query.value(0).toInt());
        //load tables;
        for(int i=0;i<tableNames.count();i++)
        {
            int index=0;
            for(int j=0;j<tables.size();j++)
            {
                if(tableNames[i]==tables[j]->name)
                    index=j;
            }
            curTableName=tableNames[i];
            query.exec("select * from "+curTableName);
            int type=tables[index]->type;
            switch(type)
            {
            case 0:
                for(int k = 0;query.next(); k++)
                {
                    newKey=new KEY;
                    newKey->flag=1;
                    newKey->type=0;
                    newKey->name=query.value(1).toString();
                    newKey->nickName=query.value(2).toString();
                    newKey->id=query.value(3).toString();
                    newKey->password=query.value(4).toString();
                    newKey->mobile=query.value(5).toString();
                    newKey->mail=query.value(6).toString();
                    newKey->website=query.value(7).toString();
                    newKey->remark=query.value(8).toString();
                    newKey->createTime=query.value(9).toDateTime();
                    newKey->lastEditTime=query.value(10).toDateTime();
                    addItemFunction(tableNames[i],0);
                }
                break;
            case 1:
                for(int k = 0;query.next(); k++)
                {
                    newKey=new KEY;
                    newKey->flag=1;
                    newKey->type=1;
                    newKey->name=query.value(1).toString();
                    newKey->mail=query.value(2).toString();
                    newKey->subName=query.value(3).toString();
                    newKey->password=query.value(4).toString();
                    newKey->website=query.value(5).toString();
                    newKey->remark=query.value(6).toString();
                    newKey->createTime=query.value(7).toDateTime();
                    newKey->lastEditTime=query.value(8).toDateTime();
                    addItemFunction(tableNames[i],0);
                }
                break;
            case 2:
                for(int k = 0;query.next(); k++)
                {
                    newKey=new KEY;
                    newKey->flag=1;
                    newKey->type=2;
                    newKey->name=query.value(1).toString();
                    newKey->mail=query.value(2).toString();
                    newKey->password=query.value(3).toString();
                    newKey->website=query.value(4).toString();
                    newKey->remark=query.value(5).toString();
                    newKey->createTime=query.value(6).toDateTime();
                    newKey->lastEditTime=query.value(7).toDateTime();
                    addItemFunction(tableNames[i],0);
                }
                break;
            case 3:
                for(int k = 0;query.next(); k++)
                {
                    newKey=new KEY;
                    newKey->flag=1;
                    newKey->type=3;
                    newKey->name=query.value(1).toString();
                    newKey->password=query.value(2).toString();
                    newKey->remark=query.value(3).toString();
                    newKey->createTime=query.value(4).toDateTime();
                    newKey->lastEditTime=query.value(5).toDateTime();
                    addItemFunction(tableNames[i],0);
                }
                break;
            default:
                break;
            }
        }
        updatePersonInfo();
        data.close();
    }
    onTableCountChanged();
}
void MainWindow::updateTableWidgetView(int index)
{
    for(int i=0;i<tableWidgets[index]->rowCount();i++)
        for(int j=0;j<tableWidgets[index]->columnCount();j++)
            tableWidgets[index]->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}
void MainWindow::changeTab()
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
    QAction *copyAll=new QAction("复制信息到剪切板");
    QAction *copyPassword=new QAction("复制密码到剪切板");
    connect(removeItem,SIGNAL(triggered()),this,SLOT(removeItemSlot()));
    connect(openWebsite,SIGNAL(triggered()),this,SLOT(openWebsiteSlot()));
    connect(copyAll,SIGNAL(triggered()),this,SLOT(copyAllSlot()));
    connect(copyPassword,SIGNAL(triggered()),this,SLOT(copyPasswordSlot()));
    tableMenu<<removeItem<<openWebsite<<copyAll<<copyPassword;
    tableWidgetMenu->addActions(tableMenu);
    tableWidgets[stackedWidget->currentIndex()]->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tableWidgets[stackedWidget->currentIndex()],SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(tableWidgetContextMenuRequested(QPoint)));
}
void MainWindow::onTabIndexChanged(int index)
{
    for(int i=0;i<tableCount;i++)
        buttons[i]->setStyleSheet("");
    buttons[index]->setStyleSheet("background-color:#00b7c3");
}
void MainWindow::updateQSS()
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
void MainWindow::tableWidgetContextMenuRequested(QPoint pos)
{
    cursorPos=new QPoint;
    *cursorPos=pos;
    tableWidgetMenu->exec(QCursor::pos());
}
void MainWindow::removeItemSlot()
{

}
void MainWindow::openWebsiteSlot()
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = tableWidgets[stackedWidget->currentIndex()]->indexAt(QPoint(x, y));
    int row = index.row();
    int column=index.column();
    if(row==-1)
        return;
    QDesktopServices::openUrl(QUrl(tableWidgets[stackedWidget->currentIndex()]->item(row,column)->text(), QUrl::TolerantMode));
}
void MainWindow::copyAllSlot()
{

}
void MainWindow::copyPasswordSlot()
{

}
