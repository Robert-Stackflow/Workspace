#include "widget.h"
#include "ui_widget.h"
void Widget::addTableSlot()
{
    additemdialog->isNewGroup=true;
    additemdialog->setWindowTitle("添加分组");
    additemdialog->m_titleBar->setWindowTitle("添加分组");
    additemdialog->ui->groupType->setEnabled(true);
    additemdialog->ui->tabWidget->setCurrentIndex(4);
    additemdialog->ui->groupName->clear();
    additemdialog->ui->group_remark->clear();
    additemdialog->ui->groupNameWarning->clear();
    additemdialog->ui->groupNameJudge->setIcon(QIcon());
    additemdialog->setModal(true);
    additemdialog->setGeometry(this->geometry().x()+this->width()/2-additemdialog->width()/2+10,this->geometry().y()+this->height()/2-additemdialog->height()/2+20,additemdialog->width(),additemdialog->height());
    additemdialog->exec();
}
void Widget::addTableFunction(QString name,int type)
{
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
    connect(tableWidgets[tableCount],SIGNAL(cellDoubleClicked(int,int)),this,SLOT(tableWidgetDoubleClickedSlot(int,int)));
    connect(tableWidgets[tableCount],SIGNAL(cellClicked(int,int)),this,SLOT(tableWidgetClickedSlot(int,int)));
    //Init the button
    QPushButton* tempButton=new QPushButton(name,this);
    buttons<<tempButton;
    buttons[tableCount]->setObjectName(QString::number(tableCount));
    if(tableCount==0)
        buttons[tableCount]->setGeometry(20,m_titleBar->height()+20,100,30);
    else
        buttons[tableCount]->setGeometry(20,m_titleBar->height()+buttons[tableCount-1]->geometry().y(),100,30);
    buttons[tableCount]->setVisible(true);
    connect(buttons[tableCount],SIGNAL(clicked()),this,SLOT(changeTab()));
    //Init the TABLE
    TABLE* tempTable=new TABLE;
    tempTable->count=newGroup->count;
    tempTable->type=newGroup->type;
    tempTable->name=newGroup->name;
    tempTable->createTime=newGroup->createTime;
    tempTable->lastEditTime=newGroup->lastEditTime;
    tempTable->remark=newGroup->remark;
    tables<<tempTable;
    //Init the newTab in the stackedWidget
    QWidget* tempWidget=new QWidget;
    widgets<<tempWidget;
    QHBoxLayout* tempLayout=new QHBoxLayout;
    tempLayout->addWidget(tableWidgets[tableCount]);
    widgets[tableCount]->setLayout(tempLayout);
    stackedWidget->addWidget(widgets[tableCount]);
    tableCount++;
    switch(type)
    {
    case 0:
        tableWidgets[tableCount-1]->setColumnHidden(8,true);
        tableWidgets[tableCount-1]->setColumnHidden(9,true);
        break;
    case 1:
        tableWidgets[tableCount-1]->setColumnHidden(6,true);
        tableWidgets[tableCount-1]->setColumnHidden(7,true);
        break;
    case 2:
        tableWidgets[tableCount-1]->setColumnHidden(5,true);
        tableWidgets[tableCount-1]->setColumnHidden(6,true);
        break;
    case 3:
        tableWidgets[tableCount-1]->setColumnHidden(3,true);
        tableWidgets[tableCount-1]->setColumnHidden(4,true);
        break;
    }
    //add table in the database
    QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++times));
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
            query.exec("create table tables (type int,name varchar(40),count int,createTime varchar(200),lastEditTime varchar(200),remark text)");
        }
        if(!data.tables().contains(tempTable->name))
        {
            switch(type)
            {
            case 0:
                query.exec("create table "+tempTable->name+" (type int,name varchar(20),nickName varchar(20),id varchar(100),password varchar(100),mobile varchar(50),mail varchar(200),website varchar(200),remark varchar(200),createTime varchar(200),lastEditTime varchar(200))");
                break;
            case 1:
                query.exec("create table "+tempTable->name+" (type int,name varchar(20),mail varchar(20),subName varchar(100),password varchar(100),website varchar(200),remark varchar(200),createTime varchar(200),lastEditTime varchar(200))");
                break;
            case 2:
                query.exec("create table "+tempTable->name+" (type int,name varchar(20),mail varchar(20),password varchar(100),website varchar(200),remark varchar(200),createTime varchar(200),lastEditTime varchar(200))");
                break;
            case 3:
                query.exec("create table "+tempTable->name+" (type int,name varchar(20),password varchar(100),remark varchar(200),createTime varchar(200),lastEditTime varchar(200))");
                break;
            }
            query.prepare("insert into tables (type,name,count,createTime,lastEditTime,remark)"
                          "VALUES (:2,:3,:4,:5,:6,:7)");
            query.bindValue(":2",tempTable->type);
            query.bindValue(":3",tempTable->name);
            query.bindValue(":4",tempTable->count);
            query.bindValue(":5",tempTable->createTime.toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":6",tempTable->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":7",tempTable->remark);
            query.exec();
        }
        data.close();
    }
    emit tableCountChanged();
}
void Widget::deleteTableSlot()
{
    int flag;
    QString title="删除分组\""+tables[stackedWidget->currentIndex()]->name+"\"";
    QString message="是否"+title;
    flag=QMessageBox::question(this,title,message,QMessageBox::Yes|QMessageBox::No);
    if(flag==QMessageBox::Yes)
    {
        QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++times));
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
    buttons[0]->click();
    buttons[0]->setGeometry(20,m_titleBar->height()+20,100,30);
    buttons[0]->setObjectName(QString::number(0));
    for(int i=1;i<buttons.size();i++)
    {
        buttons[i]->setGeometry(20,m_titleBar->height()+buttons[i-1]->geometry().y()+20,100,30);
        buttons[i]->setObjectName(QString::number(i));
    }
    emit tableCountChanged();
}
void Widget::editTableNameSlot()
{
    QString oldName=tables[stackedWidget->currentIndex()]->name;
    additemdialog->isNewGroup=false;
    additemdialog->ui->tabWidget->setCurrentIndex(4);
    additemdialog->setWindowTitle("编辑分组\""+oldName+"\"");
    additemdialog->m_titleBar->setWindowTitle("编辑分组\""+oldName+"\"");
    additemdialog->ui->groupName->setText(oldName);
    additemdialog->ui->groupType->setCurrentIndex(tables[stackedWidget->currentIndex()]->type);
    additemdialog->ui->groupType->setEnabled(false);
    additemdialog->ui->groupNameJudge->setIcon(QIcon());
    additemdialog->ui->group_remark->setText(tables[stackedWidget->currentIndex()]->remark);
    additemdialog->setModal(true);
    additemdialog->setGeometry(this->geometry().x()+this->width()/2-additemdialog->width()/2+10,this->geometry().y()+this->height()/2-additemdialog->height()/2+20,additemdialog->width(),additemdialog->height());
    additemdialog->exec();
}
void Widget::editTableNameFunction(QString oldName)
{
    if(newGroup!=NULL&&newGroup->flag)
    {
        QString newName=newGroup->name;
        tables[stackedWidget->currentIndex()]->name=newGroup->name;
        tables[stackedWidget->currentIndex()]->remark=newGroup->remark;
        tables[stackedWidget->currentIndex()]->lastEditTime=newGroup->lastEditTime;
        buttons[stackedWidget->currentIndex()]->setText(newName);
        QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++times));
        data.setDatabaseName("user.db");
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            query.exec("alter table "+oldName+" rename to "+newName);
            QString sql=QString("update tables set name='%1',lastEditTime='%2',remark='%3' where createTime='%4' ").arg(newName).arg(tables[stackedWidget->currentIndex()]->lastEditTime.toString("yyyy-MM-dd hh:mm:ss")).arg(tables[stackedWidget->currentIndex()]->remark).arg(tables[stackedWidget->currentIndex()]->createTime.toString("yyyy-MM-dd hh:mm:ss"));
            query.exec(sql);
            data.close();
        }
    }
}
void Widget::updatePersonInfo()
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
    QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++times));
    data.setDatabaseName("user.db");
    //    data.setPassword("123456");
    //    data.setConnectOptions("QSQLITE_CREATE_KEY");
    //    data.setConnectOptions("QSQLITE_REMOVE_KEY");
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
void Widget::loadUserData()
{
    tableCount=0;
    qDebug() << QSqlDatabase::drivers()<<QSqlDatabase::isDriverAvailable("SQLITECIPHER");
    QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++times));
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
        //load user information
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
        {
            newGroup=new Table;
            newGroup->type=query.value(0).toInt();
            newGroup->name=query.value(1).toString();
            newGroup->count=query.value(2).toInt();
            newGroup->createTime=query.value(3).toDateTime();
            newGroup->lastEditTime=query.value(4).toDateTime();
            newGroup->remark=query.value(5).toString();
            addTableFunction(query.value(1).toString(),query.value(0).toInt());
        }
        //load tables;
        for(int i=0;i<tableNames.count();i++)
        {
            int type=0;
            for(int j=0;j<tables.size();j++)
                if(tableNames[i]==tables[j]->name)
                    type=tables[j]->type;
            curTableName=tableNames[i];
            query.exec("select * from "+curTableName);
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
