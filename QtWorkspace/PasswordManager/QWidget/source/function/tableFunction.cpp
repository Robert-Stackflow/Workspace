#include "dialog/widget.h"
#include "ui_widget.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
void Widget::loadUserData()
{
    groupCount=0;
    QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++sqlConnectionCount));
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
        tableNames.removeOne("groups");
        tableNames.removeOne("autofillInfo");
        //load user information
        QString curTableName="autofillInfo";
        query.exec("select * from "+curTableName);
        for(int i = 0;query.next(); i++)
        {
            int type=query.value(0).toInt();
            switch(type)
            {
            case 1:
                autofillInfo->mails<<query.value(1).toString();
                autofillInfo->mailAliases<<query.value(2).toString();
                break;
            case 2:
                autofillInfo->mobiles<<query.value(1).toString();
                break;
            case 3:
                autofillInfo->websites<<query.value(1).toString();
                break;
            default:
                break;
            }
        }
        //init groups
        curTableName="groups";
        query.exec("select * from "+curTableName);
        for(int i = 0;query.next(); i++)
        {
            newGroup=new GROUP;
            newGroup->type=query.value(0).toInt();
            newGroup->name=query.value(1).toString();
            newGroup->count=query.value(2).toInt();
            newGroup->createTime=query.value(3).toDateTime();
            newGroup->lastEditTime=query.value(4).toDateTime();
            newGroup->remark=query.value(5).toString();
            newGroupFunction(query.value(1).toString(),query.value(0).toInt());
        }
        //load each group
        for(int i=0;i<tableNames.count();i++)
        {
            int type=0;
            for(int j=0;j<groups.size();j++)
                if(tableNames[i]==groups[j]->name)
                    type=groups[j]->type;
            curTableName=tableNames[i];
            query.exec("select * from "+curTableName);
            switch(type)
            {
            case 0:
                for(int k = 0;query.next(); k++)
                {
                    newKey=new ITEM;
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
                    loadItemFunction(tableNames[i]);
                }
                break;
            default:
                break;
            }
        }
        updateAutofillInfo();
        data.close();
    }
    onGroupCountChanged();
}
void Widget::newGroupSlot()
{
    newGroup=nullptr;
    newgroupdialog->newGroup=nullptr;
    newgroupdialog->setWindowTitle("新建分组");
    newgroupdialog->setModal(true);
    newgroupdialog->setGeometry(this->geometry().x()+this->width()/2-newgroupdialog->width()/2+10,this->geometry().y()+this->height()/2-newgroupdialog->height()/2+20,newgroupdialog->width(),newgroupdialog->height());
    newgroupdialog->exec();
    newGroup=newgroupdialog->newGroup;
    newGroupFunction(newgroupdialog->newGroup->name,newgroupdialog->newGroup->type);
}
void Widget::newGroupFunction(QString name,int type)
{
    //Init the tableWidget
    QTableWidget* newGroupWidget=new QTableWidget();
    tableWidgets<<newGroupWidget;
    tableWidgets[groupCount]->setColumnCount(groupTypes->at(type)->count());
    qDebug()<<groupTypes->at(type)->getItemNames();
    tableWidgets[groupCount]->setHorizontalHeaderLabels(groupTypes->at(type)->getItemNames());
    tableWidgets[groupCount]->setAlternatingRowColors(true);
    tableWidgets[groupCount]->verticalHeader()->setDefaultSectionSize(45);
    tableWidgets[groupCount]->horizontalHeader()->setStretchLastSection(true);
    tableWidgets[groupCount]->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    tableWidgets[groupCount]->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidgets[groupCount]->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidgets[groupCount]->verticalHeader()->hide();
    tableWidgets[groupCount]->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<tableWidgets[groupCount]->columnCount();i++)
        tableWidgets[groupCount]->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    connect(tableWidgets[groupCount],SIGNAL(cellDoubleClicked(int,int)),this,SLOT(tableWidgetDoubleClickedSlot(int,int)));
    connect(tableWidgets[groupCount],SIGNAL(cellClicked(int,int)),this,SLOT(tableWidgetClickedSlot(int,int)));
    //Init the button
    QPushButton* tempButton=new QPushButton(name,this);
    buttons<<tempButton;
    buttons[groupCount]->setObjectName(QString::number(groupCount));
    if(groupCount==0)
        buttons[groupCount]->setGeometry(20,m_titleBar->height()+20,100,30);
    else
        buttons[groupCount]->setGeometry(20,m_titleBar->height()+buttons[groupCount-1]->geometry().y(),100,30);
    buttons[groupCount]->setVisible(true);
    connect(buttons[groupCount],SIGNAL(clicked()),this,SLOT(changeTab()));
    groups<<newGroup;
    //Add the new group to the stackedWidget
    QWidget* tempWidget=new QWidget;
    widgets<<tempWidget;
    QHBoxLayout* tempLayout=new QHBoxLayout;
    tempLayout->addWidget(tableWidgets[groupCount]);
    widgets[groupCount]->setLayout(tempLayout);
    stackedWidget->addWidget(widgets[groupCount]);
    groupCount++;
    //add the new group to the database
    QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++sqlConnectionCount));
    data.setDatabaseName("user.db");
    data.setPassword("123456");
    QSqlQuery query(data);
    if(!data.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
        return;
    }
    else
    {
        if(!data.tables().contains("groups"))
        {
            query.exec("create table groups (type int,name varchar(40),count int,createTime varchar(200),lastEditTime varchar(200),remark text)");
        }
        if(!data.tables().contains(newGroup->name))
        {
            switch(type)
            {
            case 0:
                query.exec("create table "+newGroup->name+" (type int,name varchar(20),nickName varchar(20),id varchar(100),password varchar(100),mobile varchar(50),mail varchar(200),website varchar(200),remark varchar(200),createTime varchar(200),lastEditTime varchar(200))");
                break;
            }
            query.prepare("insert into groups (type,name,count,createTime,lastEditTime,remark)"
                          "VALUES (:2,:3,:4,:5,:6,:7)");
            query.bindValue(":2",newGroup->type);
            query.bindValue(":3",newGroup->name);
            query.bindValue(":4",newGroup->count);
            query.bindValue(":5",newGroup->createTime.toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":6",newGroup->lastEditTime.toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":7",newGroup->remark);
            query.exec();
        }
        data.close();
    }
    emit groupCountChanged();
}
void Widget::deleteGroupSlot()
{
    int flag;
    QString title="删除分组 "+groups[stackedWidget->currentIndex()]->name+" ";
    QString message="是否"+title;
    flag=QMessageBox::question(this,title,message,QMessageBox::Yes|QMessageBox::No);
    if(flag==QMessageBox::Yes)
    {
        QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++sqlConnectionCount));
        data.setDatabaseName("user.db");
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            query.exec("drop table "+groups[stackedWidget->currentIndex()]->name);
            QString sql = QString("delete from groups where name = '%1' ").arg(groups[stackedWidget->currentIndex()]->name);
            int index=stackedWidget->currentIndex();
            stackedWidget->removeWidget(widgets[index]);
            buttons.at(index)->hide();
            buttons.removeAt(index);
            widgets.removeAt(index);
            tableWidgets.removeAt(index);
            groups.removeAt(index);
            query.exec(sql);
        }
        groupCount--;
    }
    buttons[0]->click();
    buttons[0]->setGeometry(20,m_titleBar->height()+20,100,30);
    buttons[0]->setObjectName(QString::number(0));
    for(int i=1;i<buttons.size();i++)
    {
        buttons[i]->setGeometry(20,m_titleBar->height()+buttons[i-1]->geometry().y()+20,100,30);
        buttons[i]->setObjectName(QString::number(i));
    }
    emit groupCountChanged();
}
void Widget::editGroupSlot()
{
    QString oldName="";
    newgroupdialog->ui->tabWidget->setCurrentIndex(1);
    newgroupdialog->setWindowTitle("编辑分组 "+oldName+" ");
    newgroupdialog->m_titleBar->setWindowTitle("编辑分组 "+oldName+" ");
    newgroupdialog->setModal(true);
    newgroupdialog->setGeometry(this->geometry().x()+this->width()/2-newgroupdialog->width()/2+10,this->geometry().y()+this->height()/2-newgroupdialog->height()/2+20,newgroupdialog->width(),newgroupdialog->height());
    newgroupdialog->exec();
}
void Widget::editGroupFunction(QString oldName)
{
    if(newGroup!=NULL&&newGroup->flag)
    {
        QString newName=newGroup->name;
        groups[stackedWidget->currentIndex()]->name=newGroup->name;
        groups[stackedWidget->currentIndex()]->remark=newGroup->remark;
        groups[stackedWidget->currentIndex()]->lastEditTime=newGroup->lastEditTime;
        buttons[stackedWidget->currentIndex()]->setText(newName);
        QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++sqlConnectionCount));
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
            QString sql=QString("update groups set name='%1',lastEditTime='%2',remark='%3' where createTime='%4' ").arg(newName).arg(groups[stackedWidget->currentIndex()]->lastEditTime.toString("yyyy-MM-dd hh:mm:ss")).arg(groups[stackedWidget->currentIndex()]->remark).arg(groups[stackedWidget->currentIndex()]->createTime.toString("yyyy-MM-dd hh:mm:ss"));
            query.exec(sql);
            data.close();
        }
    }
}
void Widget::updateAutofillInfo()
{
    //    newitemdialog->ui->nickName->clear();
    //    newitemdialog->ui->mail->clear();
    //    newitemdialog->ui->mobile->clear();
    //    newitemdialog->ui->mail->addItems(autofillInfo->mails);
    //    newitemdialog->ui->mail->addItems(autofillInfo->mailAliases);
    //    newitemdialog->ui->mobile->addItems(autofillInfo->mobiles);
    //    for(int i=0;i<newitemdialog->ui->mail->count();i++)
    //        if(newitemdialog->ui->mail->itemText(i)=="")
    //            newitemdialog->ui->mail->removeItem(i);
    //    for(int i=0;i<newitemdialog->ui->mobile->count();i++)
    //        if(newitemdialog->ui->mobile->itemText(i)=="")
    //            newitemdialog->ui->mobile->removeItem(i);
    QSqlDatabase data = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++sqlConnectionCount));
    data.setDatabaseName("user.db");
    data.setPassword("123456");
    data.setConnectOptions("QSQLITE_CREATE_ITEM");
    data.setConnectOptions("QSQLITE_REMOVE_ITEM");
    QSqlQuery query(data);
    if(!data.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
        return;
    }
    else
    {
        //1-邮箱
        //2-手机
        QString tableName="autofillInfo";
        if(data.tables().contains(tableName))
        {
            query.exec("drop table "+tableName);
        }
        query.exec("create table "+tableName+" (type int,content varchar(100),remark varchar(100))");
        for(int i=0;i<autofillInfo->mails.size();i++)
        {
            query.prepare("insert into "+tableName+" (type,content,remark)"
                                                   "VALUES (:1,:2,:3)");
            query.bindValue(":1",1);
            query.bindValue(":2",autofillInfo->mails[i]);
            query.bindValue(":3",autofillInfo->mailAliases[i]);
            query.exec();
        }
        for(int i=0;i<autofillInfo->mobiles.size();i++)
        {
            query.prepare("insert into "+tableName+" (type,content,remark)"
                                                   "VALUES (:1,:2,:3)");
            query.bindValue(":1",2);
            query.bindValue(":2",autofillInfo->mobiles[i]);
            query.bindValue(":3","");
            query.exec();
        }
        data.close();
    }
}
