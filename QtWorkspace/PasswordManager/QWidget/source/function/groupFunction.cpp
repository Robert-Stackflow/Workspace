#include "customField/customTextEdit.h"
#include "widget.h"
#include "ui_widget.h"
#include "util/databasetablenamegetter.h"
#include "util/datapathgetter.h"
#include "util/shareddata.h"
#include "QsLog.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
void Widget::loadGroups()
{
    SharedData& sharedData = SharedData::instace();
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter& dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    //连接数据库
    QString currentUsername=sharedData.accountList.getActiveAccount()->getUsername();
    QString databaseName=dataPathGetter.getCurrentAccountDataBasePath();
    sharedData.database.setDatabaseName(databaseName);
    QSqlQuery query(sharedData.database);
    if(!sharedData.database.open()){
        QsLogging::Logger::getFileLogger(currentUsername,"DATABASE");
        QLOG_WARN()<<"Database Connection Error:"<<databaseName<<"!";
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
        return;
    }else{
        QsLogging::Logger::getFileLogger("PUBLIC","DATABASE");
        QLOG_DEBUG()<<"Database Connection:"<<databaseName;
        //获取数据库表名列表
        QStringList tableNames=sharedData.database.tables();
        if(!tableNames.contains(dataBaseTableNameGetter.getGroupsTableName())){
            QsLogging::Logger::getFileLogger(currentUsername,"SQL");
            //开启事务
            QString transactionBeginSql="begin";
            query.exec(transactionBeginSql);
            QLOG_DEBUG()<<"Begin Transaction:"<<transactionBeginSql;
            //创建groups表
            QString createSql="create table "+dataBaseTableNameGetter.getGroupsTableName()
                    +" (groupType int,groupName varchar(40),KeyItemCount int,createTime varchar(200),"
                     "lastEditTime varchar(200),describe text)";
            bool createSqlFlag=query.exec(createSql);
            QLOG_DEBUG()<<"Create Table(s):"<<createSql;
            //创建默认分组
            Group* newGroup=new Group(0,"默认分组",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"账户初始化时创建的默认分组");
            sharedData.groupList<<newGroup;
            //插入到groups表中
            QString insertSql="insert into "+dataBaseTableNameGetter.getGroupsTableName()
                    +" (groupType,groupName,KeyItemCount,createTime,lastEditTime,describe) "
                     "VALUES(:1,:2,:3,:4,:5,:6)";
            query.prepare(insertSql);
            query.bindValue(":1",newGroup->getGroupType());
            query.bindValue(":2",newGroup->getGroupName());
            query.bindValue(":3",newGroup->count());
            query.bindValue(":4",newGroup->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":5",newGroup->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":6",newGroup->getDescribe());
            bool insertSqlFlag=query.exec();
            QLOG_DEBUG()<<"Insert Record(s):"<<insertSql;
            //创建默认分组表
            QString createDefaultGroupSql="create table "+dataBaseTableNameGetter.getGroupTableName(newGroup->getGroupName())
                    +" (groupType int,createTime varchar(200),lastEditTime varchar(200))";
            bool createDefaultGroupFlag=query.exec(createDefaultGroupSql);
            QLOG_DEBUG()<<"Create Table(s):"<<createDefaultGroupSql;
            if(createSqlFlag&&insertSqlFlag&&createDefaultGroupFlag){
                QString transactionCommitSql="commit";
                query.exec(transactionCommitSql);
                QLOG_DEBUG()<<"Commit Transaction:"<<transactionCommitSql;
            }else{
                QString transactionRollbackSql="rollback";
                query.exec(transactionRollbackSql);
                QLOG_DEBUG()<<"Rollback Transaction:"<<transactionRollbackSql;
            }
        }
        if(!tableNames.contains(dataBaseTableNameGetter.getAutofillInfoTableName())){
            QString createSql="create table sharedData.autofillInfo (type int,content varchar(100),remark varchar(100))";
            query.exec(createSql);
            QsLogging::Logger::getFileLogger(currentUsername,"SQL");
            QLOG_DEBUG()<<"Create Table(s):"<<createSql;
        }
        //加载分组
        //新建各个分组
        QString curTableName=dataBaseTableNameGetter.getGroupsTableName();
        query.exec("select * from "+curTableName);
        for(int i = 0;query.next(); i++){
            newGroup=new Group(query.value(0).toInt(),query.value(1).toString(),query.value(3).toDateTime(),query.value(4).toDateTime(),query.value(5).toString());
            newGroupFunction(1);
        }
        //加载每个分组的密码条目
        for(int i=0;i<sharedData.groupList.count();i++){
            curTableName=dataBaseTableNameGetter.getGroupTableName(sharedData.groupList[i]->getGroupName());
            query.exec("select * from "+curTableName);
            //加载密码条目
            for(int k=0;query.next();k++){
                newKeyItem=new KeyItem(sharedData.groupList[i]->getGroupType(),query.value(1).toDateTime(),query.value(2).toDateTime(),sharedData.groupTypeList[sharedData.groupList[i]->getGroupType()]->getFieldNames());
                loadKeyItemFunction(curTableName);
            }
        }
        sharedData.database.close();
    }
    //发射分组数目改变的信号
    emit groupCountChanged();
}
void Widget::loadGroupTypes()
{
    SharedData& sharedData = SharedData::instace();
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter& dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    //连接数据库
    QString currentUsername=sharedData.accountList.getActiveAccount()->getUsername();
    QString databaseName=dataPathGetter.getCurrentAccountDataBasePath();
    sharedData.database.setDatabaseName(databaseName);
    QSqlQuery query(sharedData.database);
    if(!sharedData.database.open()){
        QsLogging::Logger::getFileLogger(currentUsername,"DATABASE");
        QLOG_WARN()<<"Database Connection Error:"<<databaseName<<"!";
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
        return;
    }else{
        QsLogging::Logger::getFileLogger("PUBLIC","DATABASE");
        QLOG_DEBUG()<<"Database Connection:"<<databaseName;
        //获取数据库表名列表
        QStringList tableNames=sharedData.database.tables();
        if(!tableNames.contains(dataBaseTableNameGetter.getGroupTypesTableName())){
            //如果不包含groupTypes表，则创建之并插入默认分组类型
            QsLogging::Logger::getFileLogger(currentUsername,"SQL");
            //开启事务
            QString transactionBeginSql="begin";
            query.exec(transactionBeginSql);
            QLOG_DEBUG()<<"Begin Transaction:"<<transactionBeginSql;
            //创建groupTypes表
            QString createGroupTypesTableSql="create table "+dataBaseTableNameGetter.getGroupTypesTableName()
                    +" (groupTypeName varchar(200),fieldCount int,"
                     "createTime varchar(200),lastEditTime varchar(200),describe text)";
            bool createGroupTypesTableFlag=query.exec(createGroupTypesTableSql);
            QLOG_DEBUG()<<"Create Table(s):"<<createGroupTypesTableSql;
            //创建默认分组类型
            QList<AbstractCustomField*> customFieldList;
            AbstractCustomField* field_1=new customLineEdit("名称",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
            field_1->setFieldTypeName("单行文本");
            AbstractCustomField* field_2=new customLineEdit("用户名",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
            field_2->setFieldTypeName("单行文本");
            AbstractCustomField* field_3=new customLineEdit("密码",AbstractCustomField::REQUIRED,AbstractCustomField::PASSWORD,this);
            field_3->setFieldTypeName("密码");
            AbstractCustomField* field_4=new customComboBox("邮箱",AbstractCustomField::OPTIONAL,AbstractCustomField::MAIL,this);
            field_4->setFieldTypeName("自动填充-邮箱");
            AbstractCustomField* field_5=new customComboBox("手机号码",AbstractCustomField::OPTIONAL,AbstractCustomField::MOBILE,this);
            field_5->setFieldTypeName("自动填充-电话");
            AbstractCustomField* field_6=new customComboBox("网址",AbstractCustomField::OPTIONAL,AbstractCustomField::WEBSITE,this);
            field_6->setFieldTypeName("自动填充-网址");
            AbstractCustomField* field_7=new customTextEdit("备注",AbstractCustomField::OPTIONAL,AbstractCustomField::NORMAL,this);
            field_7->setFieldTypeName("多行文本");
            customFieldList<<field_1<<field_2<<field_3<<field_4<<field_5<<field_6<<field_7;
            GroupType* loadGroupType=new GroupType("默认类型","账户初始化时创建的默认分组类型",customFieldList);
            sharedData.groupTypeList<<loadGroupType;
            //插入到groupTypes表中
            QString insertIntoGroupTypesTableSql="insert into "+dataBaseTableNameGetter.getGroupTypesTableName()
                    +" (groupTypeName,fieldCount,createTime,lastEditTime,describe) "
                     "VALUES(:1,:2,:3,:4,:5)";
            query.prepare(insertIntoGroupTypesTableSql);
            query.bindValue(":1",loadGroupType->getGroupTypeName());
            query.bindValue(":2",loadGroupType->count());
            query.bindValue(":3",loadGroupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":4",loadGroupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":5",loadGroupType->getDescribe());
            bool insertIntoGroupTypesTableFlag=query.exec();
            QLOG_DEBUG()<<"Insert Record(s):"<<insertIntoGroupTypesTableSql;
            //创建默认分组类型表
            QString createDefaultGroupTypeTableSql="create table "+dataBaseTableNameGetter.getGroupTypeTableName(loadGroupType->getGroupTypeName())
                    +" (fieldName varchar(200),isRequired int,fieldTypeName varchar(200),placeholderText text)";
            bool createDefaultGroupTypeTableFlag=query.exec(createDefaultGroupTypeTableSql);
            QLOG_DEBUG()<<"Create Table(s):"<<createDefaultGroupTypeTableSql;
            //插入类型字段
            bool insertFieldFlag=true;
            for(int i=0;i<loadGroupType->count();i++){
                QString insertFieldSql="insert into "+dataBaseTableNameGetter.getGroupTypeTableName(loadGroupType->getGroupTypeName())
                        +" (fieldName,isRequired,fieldTypeName,placeholderText)VALUES(:1,:2,:3,:4)";
                query.prepare(insertFieldSql);
                query.bindValue(":1",loadGroupType->at(i)->getFieldName());
                query.bindValue(":2",int(loadGroupType->at(i)->getIsRequired()));
                query.bindValue(":3",loadGroupType->at(i)->getFieldTypeName());
                query.bindValue(":4",loadGroupType->at(i)->getPlaceholderText());
                bool temp=query.exec();
                qDebug()<<query.lastError();
                insertFieldFlag=insertFieldFlag&&temp;
                QLOG_DEBUG()<<"Insert Record(s):"<<insertFieldSql;
            }
            if(createGroupTypesTableFlag&&insertIntoGroupTypesTableFlag&&createDefaultGroupTypeTableFlag&&insertFieldFlag){
                QString transactionCommitSql="commit";
                query.exec(transactionCommitSql);
                QLOG_DEBUG()<<"Commit Transaction:"<<transactionCommitSql;
            }else{
                QString transactionRollbackSql="rollback";
                query.exec(transactionRollbackSql);
                QLOG_DEBUG()<<"Rollback Transaction:"<<transactionRollbackSql;
            }
        }else{
            //加载分组类型
            QString curTableName=dataBaseTableNameGetter.getGroupTypesTableName();
            QString selectSql="select * from "+curTableName;
            query.exec(selectSql);
            QsLogging::Logger::getFileLogger(currentUsername,"SQL");
            QLOG_DEBUG()<<"Select Column(s):"<<selectSql;
            //新建各个分组类型
            for(int i = 0;query.next(); i++){
                GroupType* newGroupType=new GroupType(query.value(0).toString(),query.value(2).toDateTime(),query.value(3).toDateTime(),query.value(4).toString());
                sharedData.groupTypeList<<newGroupType;
                QsLogging::Logger::getFileLogger(currentUsername,"SQL");
                QLOG_DEBUG()<<"Load GroupType:"<<newGroupType->getGroupTypeName();
            }
            //加载各个分组类型的字段条目
            for(int i=0;i<sharedData.groupTypeList.count();i++){
                curTableName=dataBaseTableNameGetter.getGroupTypeTableName(sharedData.groupTypeList[i]->getGroupTypeName());
                QString selectSql="select * from "+curTableName;
                query.exec(selectSql);
                QsLogging::Logger::getFileLogger(currentUsername,"SQL");
                QLOG_DEBUG()<<"Select Column(s):"<<selectSql;
                QList<AbstractCustomField*> fieldList;
                for(int i = 0;query.next(); i++){
                    QString fieldName=query.value(0).toString();
                    QString fieldTypeName=query.value(2).toString();
                    QString fieldPlaceholderText=query.value(3).toString();
                    AbstractCustomField::isRequiredChoices isRequired=AbstractCustomField::isRequiredChoices(query.value(1).toInt());
                    AbstractCustomField::controllerTypeChoices controllerType=sharedData.fieldTypeList.getControllerType(fieldTypeName);
                    AbstractCustomField::dataTypeChoices dataType=sharedData.fieldTypeList.getDataType(fieldTypeName);
                    QLOG_DEBUG()<<"Load Field:"<<fieldName;
                    AbstractCustomField* tempField=nullptr;
                    //新建abstractCustomField
                    if(controllerType==AbstractCustomField::LINEEDIT)
                        tempField=new customLineEdit(fieldName,isRequired,dataType);
                    else if(controllerType==AbstractCustomField::COMBOBOX)
                        tempField=new customComboBox(fieldName,isRequired,dataType);
                    else if(controllerType==AbstractCustomField::TEXTEDIT)
                        tempField=new customTextEdit(fieldName,isRequired,dataType);
                    if(tempField!=nullptr&&fieldPlaceholderText!=""){
                        tempField->setPlaceholderText(fieldPlaceholderText);
                    }
                    fieldList<<tempField;
                }
                sharedData.groupTypeList[i]->setCustomFieldList(fieldList);
            }
        }
        newgrouptypedialog->loadGroupTypes();
        sharedData.database.close();
    }
}
void Widget::loadAutofillInfo()
{
    SharedData& sharedData = SharedData::instace();
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter& dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    //连接数据库
    QString currentUsername=sharedData.accountList.getActiveAccount()->getUsername();
    QString databaseName=dataPathGetter.getCurrentAccountDataBasePath();
    sharedData.database.setDatabaseName(databaseName);
    QSqlQuery query(sharedData.database);
    if(!sharedData.database.open()){
        QsLogging::Logger::getFileLogger(currentUsername,"DATABASE");
        QLOG_WARN()<<"Database Connection Error:"<<databaseName<<"!";
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
        return;
    }else{
        QsLogging::Logger::getFileLogger("PUBLIC","DATABASE");
        QLOG_DEBUG()<<"Database Connection:"<<databaseName;
        //获取数据库表名列表
        QStringList tableNames=sharedData.database.tables();
        if(!tableNames.contains(dataBaseTableNameGetter.getAutofillInfoTableName())){
            QString createSql="create table sharedData.autofillInfo (type int,content varchar(100),remark varchar(100))";
            query.exec(createSql);
            QsLogging::Logger::getFileLogger(currentUsername,"SQL");
            QLOG_DEBUG()<<"Create Table(s):"<<createSql;
        }
        //加载个人信息
        QString curTableName=dataBaseTableNameGetter.getAutofillInfoTableName();
        QString selectSql="select * from "+curTableName;
        query.exec(selectSql);
        QsLogging::Logger::getFileLogger(currentUsername,"SQL");
        QLOG_DEBUG()<<"Select Column(s):"<<selectSql;
        for(int i = 0;query.next(); i++){
            //个人信息类型:1-邮箱,2-电话,3-网址
            int type=query.value(0).toInt();
            switch(type)
            {
            case 1:
                sharedData.autofillInfo.addMail(query.value(1).toString(),query.value(2).toString());
                break;
            case 2:
                sharedData.autofillInfo.addMobile(query.value(1).toString());
                break;
            case 3:
                sharedData.autofillInfo.addWebsite(query.value(1).toString());
                break;
            }
        }
        updateAutofillInfo();
        sharedData.database.close();
    }
    //发射分组数目改变的信号
    emit groupCountChanged();
}
void Widget::loadUserData()
{
    loadGroupTypes();
    loadGroups();
    loadAutofillInfo();
}
void Widget::newGroupSlot()
{
    //新建分组时置newGroup为nullptr
    newGroup=nullptr;
    newgroupdialog->newGroup=nullptr;
    //设置标题并转到newgroupdialog窗口
    newgroupdialog->setWindowTitle("新建分组");
    newgroupdialog->setModal(true);
    newgroupdialog->setGeometry(this->geometry().x()+this->width()/2-newgroupdialog->width()/2+10,this->geometry().y()+this->height()/2-newgroupdialog->height()/2+20,newgroupdialog->width(),newgroupdialog->height());
    newgroupdialog->exec();
    //关闭newgroupdialog窗口后，赋值Group，并调用newGroupFunction新建分组
    newGroup=newgroupdialog->newGroup;
    newGroupFunction(0);
}
void Widget::newGroupFunction(int mode)
{
    SharedData& sharedData = SharedData::instace();
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter& dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    if(newGroup==nullptr)
        return;
    int groupCount=sharedData.groupList.count();
    int groupType=newGroup->getGroupType();
    QString groupName=newGroup->getGroupName();
    GroupType* currentGroupType=sharedData.groupTypeList[groupType];
    //初始化tableWidget
    QTableWidget* newGroupWidget=new QTableWidget();
    tableWidgets<<newGroupWidget;
    tableWidgets[groupCount]->setColumnCount(currentGroupType->count());//设置列数
    tableWidgets[groupCount]->setHorizontalHeaderLabels(currentGroupType->getFieldNames());//设置表头
    tableWidgets[groupCount]->setAlternatingRowColors(true);//设置行色交替
    tableWidgets[groupCount]->verticalHeader()->hide();//隐藏垂直表头
    tableWidgets[groupCount]->verticalHeader()->setDefaultSectionSize(45);//设置表格高度
    tableWidgets[groupCount]->horizontalHeader()->setStretchLastSection(true);
    tableWidgets[groupCount]->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidgets[groupCount]->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置水平表头
    tableWidgets[groupCount]->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    tableWidgets[groupCount]->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选择整行
    for(int i=0;i<tableWidgets[groupCount]->columnCount();i++)
        tableWidgets[groupCount]->horizontalHeader()->setSectionResizeMode(i,QHeaderView::ResizeToContents);
    //绑定tableWidget槽函数
    connect(tableWidgets[groupCount],SIGNAL(cellClicked(int,int)),this,SLOT(tableWidgetClickedSlot(int,int)));
    //初始化tabWidget
    QWidget* tempWidget=new QWidget;
    widgets<<tempWidget;
    QHBoxLayout* tempLayout=new QHBoxLayout;
    tempLayout->addWidget(tableWidgets[groupCount]);
    widgets[groupCount]->setLayout(tempLayout);
    tabWidget->addTab(widgets[groupCount],groupName);
    //添加到sharedData.groupList中
    sharedData.groupList<<newGroup;
    if(mode==0){
        //添加到数据库中
        sharedData.database.setDatabaseName(dataPathGetter.getCurrentAccountDataBasePath());
        QSqlQuery query(sharedData.database);
        if(!sharedData.database.open()){
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
            return;
        }else{
            QString newGroupTableName=dataBaseTableNameGetter.getGroupTableName(newGroup->getGroupName());
            if(!sharedData.database.tables().contains(newGroupTableName)){
                //如果分组不存在，创建记录分组信息的表
                query.exec("create table "+newGroupTableName+" (groupType int,createTime varchar(200),lastEditTime varchar(200))");
                //向sharedData.groupList表插入数据
                query.prepare("insert into sharedData.groupList (groupType,groupName,KeyItemCount,createTime,lastEditTime,describe)"
                              "VALUES (:1,:2,:3,:4,:5,:6)");
                query.bindValue(":1",newGroup->getGroupType());
                query.bindValue(":2",newGroup->getGroupName());
                query.bindValue(":3",newGroup->count());
                query.bindValue(":4",newGroup->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":5",newGroup->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":6",newGroup->getDescribe());
                query.exec();
            }
            sharedData.database.close();
        }
    }
    //发射分组数目改变的信号
    emit groupCountChanged();
}
void Widget::deleteGroupSlot()
{
    SharedData& sharedData = SharedData::instace();
    int index=tabWidget->currentIndex();
    QString deleteGroupName=sharedData.groupList[index]->getGroupName();
    QString title="删除分组 "+deleteGroupName+" ";
    QString message="是否确认"+title;
    //询问是否确认删除
    int choice=QMessageBox::question(this,title,message,QMessageBox::Yes|QMessageBox::No);
    if(choice==QMessageBox::Yes){
        //连接数据库
        sharedData.database.setPassword("123456");
        QSqlQuery query(sharedData.database);
        if(!sharedData.database.open()){
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
            return;
        }
        else{
            //删除数据表
            query.exec("drop table "+deleteGroupName);
            QString sql = QString("delete from sharedData.groupList where groupName = '%1' ").arg(deleteGroupName);
            //删除stackedWidget、buttons、widgets、tableWidgets中的相关控件
            tabWidget->removeTab(index);
            widgets.removeAt(index);
            tableWidgets.removeAt(index);
            //删除group
            sharedData.groupList.removeAt(index);
            query.exec(sql);
        }
    }
    //发射分组数目改变的信号
    emit groupCountChanged();
}
void Widget::editGroupSlot()
{
    SharedData& sharedData = SharedData::instace();
    Group* currentGroup=sharedData.groupList[tabWidget->currentIndex()];
    int groupType=currentGroup->getGroupType();
    QString oldGroupName=currentGroup->getGroupName();
    newgroupdialog->ui->tabWidget->setCurrentIndex(1);
    newgroupdialog->setWindowTitle("编辑分组 "+oldGroupName+" ");
    newgroupdialog->m_titleBar->setWindowTitle("编辑分组 "+oldGroupName+" ");
    newgroupdialog->newGroupName->setText(oldGroupName);
    newgroupdialog->newGroupType->setCurrentIndex(groupType);
    newgroupdialog->newGroupType->setEnable(false);
    newgroupdialog->setModal(true);
    newgroupdialog->setGeometry(this->geometry().x()+this->width()/2-newgroupdialog->width()/2+10,this->geometry().y()+this->height()/2-newgroupdialog->height()/2+20,newgroupdialog->width(),newgroupdialog->height());
    newgroupdialog->exec();
    editGroupFunction(oldGroupName);
}
void Widget::editGroupFunction(QString oldGroupName)
{
    SharedData& sharedData = SharedData::instace();
    int index=tabWidget->currentIndex();
    Group* currentGroup=sharedData.groupList[tabWidget->currentIndex()];
    if(newGroup!=NULL&&newGroup->getFlag())
    {
        //更新group信息
        currentGroup->setGroupName(newGroup->getGroupName());
        currentGroup->setDescribe(newGroup->getDescribe());
        currentGroup->setLastEditTime();
        //更新数据库
        QSqlQuery query(sharedData.database);
        if(!sharedData.database.open()){
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
            return;
        }else{
            query.exec("alter table "+oldGroupName+" rename to "+currentGroup->getGroupName());
            QString sql=QString("update sharedData.groupList set groupName='%1',lastEditTime='%2',describe='%3' where createTime='%4' ")
                    .arg(newGroup->getGroupName())
                    .arg(sharedData.groupList[index]->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(sharedData.groupList[index]->getDescribe())
                    .arg(sharedData.groupList[index]->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query.exec(sql);
            sharedData.database.close();
        }
    }
}
void Widget::updateAutofillInfo()
{
    SharedData& sharedData = SharedData::instace();
    //    newitemdialog->ui->nickName->clear();
    //    newitemdialog->ui->mail->clear();
    //    newitemdialog->ui->mobile->clear();
    //    newitemdialog->ui->mail->addItems(sharedData.autofillInfo->mails);
    //    newitemdialog->ui->mail->addItems(sharedData.autofillInfo->mailAliases);
    //    newitemdialog->ui->mobile->addItems(sharedData.autofillInfo->mobiles);
    //    for(int i=0;i<newitemdialog->ui->mail->count();i++)
    //        if(newitemdialog->ui->mail->itemText(i)=="")
    //            newitemdialog->ui->mail->removeItem(i);
    //    for(int i=0;i<newitemdialog->ui->mobile->count();i++)
    //        if(newitemdialog->ui->mobile->itemText(i)=="")
    //            newitemdialog->ui->mobile->removeItem(i);
    //    QSqlDatabase sharedData.database = QSqlDatabase::addDatabase("SQLITECIPHER",QString::asprintf("%d",++sqlConnectionCount));
    //    sharedData.database.setDatabaseName("user.db");
    //    sharedData.database.setPassword("123456");
    //    sharedData.database.setConnectOptions("QSQLITE_CREATE_ITEM");
    //    sharedData.database.setConnectOptions("QSQLITE_REMOVE_ITEM");
    QSqlQuery query(sharedData.database);
    if(!sharedData.database.open()){
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
        return;
    }else{
        //1-邮箱,2-手机,3-网址
        QString curTableName="sharedData.autofillInfo";
        //删除旧表
        if(sharedData.database.tables().contains(curTableName)){
            query.exec("drop table "+curTableName);
        }
        query.exec("create table "+curTableName+" (type int,content varchar(100),remark varchar(100))");
        //添加mail
        for(int i=0;i<sharedData.autofillInfo.getMails().count();i++){
            query.prepare("insert into "+curTableName+" (type,content,remark)"
                                                      "VALUES (:1,:2,:3)");
            query.bindValue(":1",0);
            query.bindValue(":2",sharedData.autofillInfo.getMails()[i]);
            query.bindValue(":3",sharedData.autofillInfo.getMailAliases()[i]);
            query.exec();
        }
        //添加mobile
        for(int i=0;i<sharedData.autofillInfo.getMobiles().size();i++){
            query.prepare("insert into "+curTableName+" (type,content,remark)"
                                                      "VALUES (:1,:2,:3)");
            query.bindValue(":1",1);
            query.bindValue(":2",sharedData.autofillInfo.getMobiles()[i]);
            query.bindValue(":3","");
            query.exec();
        }
        //添加website
        for(int i=0;i<sharedData.autofillInfo.getWebsites().size();i++){
            query.prepare("insert into "+curTableName+" (type,content,remark)"
                                                      "VALUES (:1,:2,:3)");
            query.bindValue(":1",2);
            query.bindValue(":2",sharedData.autofillInfo.getWebsites()[i]);
            query.bindValue(":3","");
            query.exec();
        }
        sharedData.database.close();
    }
}
