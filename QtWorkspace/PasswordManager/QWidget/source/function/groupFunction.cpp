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
void Widget::loadUserData()
{
    SharedData& sharedData = SharedData::instace();
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter& dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    //连接数据库
    sharedData.database.setDatabaseName(dataPathGetter.getCurrentAccountDataBasePath());
    QSqlQuery query(sharedData.database);
    if(!sharedData.database.open()){
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
        return;
    }else{
        //获取数据库表名列表
        QStringList tableNames=sharedData.database.tables();
        if(!tableNames.contains(dataBaseTableNameGetter.getGroupsTableName())){
            query.exec("create table sharedData.groupList (groupType int,groupName varchar(40),KeyItemCount int,createTime varchar(200),lastEditTime varchar(200),describe text)");
        }
        if(!tableNames.contains(dataBaseTableNameGetter.getGroupTypesTableName())){
            query.exec("create table sharedData.groupTypeList (groupTypeName int,fieldCount int,createTime varchar(200),lastEditTime varchar(200),describe text)");
        }
        if(!tableNames.contains(dataBaseTableNameGetter.getAutofillInfoTableName())){
            query.exec("create table sharedData.autofillInfo (type int,content varchar(100),remark varchar(100))");
        }
        //加载分组类型
        QString curTableName=dataBaseTableNameGetter.getGroupTypesTableName();
        query.exec("select * from "+curTableName);
        //新建各个分组类型
        for(int i = 0;query.next(); i++){
            GroupType* newGroupType=new GroupType(query.value(0).toString(),query.value(2).toDateTime(),query.value(3).toDateTime(),query.value(4).toString());
            sharedData.groupTypeList<<newGroupType;
        }
        //加载各个分组类型的字段条目
        for(int i=0;i<sharedData.groupTypeList.count();i++){
            curTableName=dataBaseTableNameGetter.getGroupTypeTableName(sharedData.groupTypeList[i]->getGroupTypeName());
            query.exec("select * from "+curTableName);
            QList<AbstractCustomField*> fieldList;
            for(int i = 0;query.next(); i++){
                QString fieldName=query.value(0).toString();
                QString fieldTypeName=query.value(2).toString();
                QString fieldPlaceholderText=query.value(3).toString();
                AbstractCustomField::controllerTypeChoices controllerType=sharedData.fieldTypeList.getControllerType(fieldTypeName);
                AbstractCustomField::dataTypeChoices dataType=sharedData.fieldTypeList.getDataType(fieldTypeName);
                AbstractCustomField::isRequiredChoices isRequired=AbstractCustomField::isRequiredChoices(query.value(1).toInt());
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
        newgrouptypedialog->loadGroupTypes();
        //加载分组
        //新建各个分组
        curTableName=dataBaseTableNameGetter.getGroupsTableName();
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
        //加载个人信息
        curTableName=dataBaseTableNameGetter.getAutofillInfoTableName();
        query.exec("select * from "+curTableName);
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
    //初始化button
    QPushButton* tempButton=new QPushButton(groupName,this);
    buttons<<tempButton;
    buttons[groupCount]->setVisible(true);
    buttons[groupCount]->setObjectName(QString::number(groupCount));
    //设置button位置
    if(groupCount==0)
        buttons[groupCount]->setGeometry(20,m_titleBar->height()+20,100,30);
    else
        buttons[groupCount]->setGeometry(20,m_titleBar->height()+buttons[groupCount-1]->geometry().y(),100,30);
    //绑定button槽函数
    connect(buttons[groupCount],SIGNAL(clicked()),this,SLOT(changeTab()));
    //初始化stackedWidget
    QWidget* tempWidget=new QWidget;
    widgets<<tempWidget;
    QHBoxLayout* tempLayout=new QHBoxLayout;
    tempLayout->addWidget(tableWidgets[groupCount]);
    widgets[groupCount]->setLayout(tempLayout);
    stackedWidget->addWidget(widgets[groupCount]);
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
    int index=stackedWidget->currentIndex();
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
            stackedWidget->removeWidget(widgets[index]);
            buttons.at(index)->hide();
            buttons.removeAt(index);
            widgets.removeAt(index);
            tableWidgets.removeAt(index);
            //删除group
            sharedData.groupList.removeAt(index);
            query.exec(sql);
        }
    }
    //删除成功后跳转到第一个分组,并更新buttons位置与相关信息
    buttons[0]->click();
    buttons[0]->setGeometry(20,m_titleBar->height()+20,100,30);
    buttons[0]->setObjectName(QString::number(0));
    for(int i=1;i<buttons.count();i++)
    {
        buttons[i]->setGeometry(20,m_titleBar->height()+buttons[i-1]->geometry().y()+20,100,30);
        buttons[i]->setObjectName(QString::number(i));
    }
    //发射分组数目改变的信号
    emit groupCountChanged();
}
void Widget::editGroupSlot()
{
    SharedData& sharedData = SharedData::instace();
    Group* currentGroup=sharedData.groupList[stackedWidget->currentIndex()];
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
    int index=stackedWidget->currentIndex();
    Group* currentGroup=sharedData.groupList[stackedWidget->currentIndex()];
    if(newGroup!=NULL&&newGroup->getFlag())
    {
        //更新group信息
        currentGroup->setGroupName(newGroup->getGroupName());
        currentGroup->setDescribe(newGroup->getDescribe());
        currentGroup->setLastEditTime();
        buttons[index]->setText(newGroup->getGroupName());
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
