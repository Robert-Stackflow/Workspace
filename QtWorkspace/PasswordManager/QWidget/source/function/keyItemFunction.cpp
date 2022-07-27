#include "widget.h"
#include "ui_widget.h"
#include "util/databasetablenamegetter.h"
#include "util/datapathgetter.h"
#include "util/shareddata.h"
#include "QsLog.h"
#pragma warning (disable:4100)
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
void Widget::loadKeyItemFunction(QString& groupName)
{
    SharedData& sharedData = SharedData::instace();
    if(newKeyItem!=NULL&&newKeyItem->getFlag()){
        int index=0;
        int groupType=newKeyItem->getGroupType();
        int groupTypeFieldCount=sharedData.groupTypeList[groupType]->count();
        for(int j=0;j<sharedData.groupList.count();j++){
            if(groupName==sharedData.groupList[j]->getGroupName())
                index=j;
        }
        sharedData.groupList[index]->append(newKeyItem);
        if(!sharedData.database.open()){
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
            return;
        }else{
            tableWidgets[index]->insertRow(tableWidgets[index]->rowCount());
            tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,groupTypeFieldCount+1,new QTableWidgetItem(newKeyItem->getCreateTime().toString("yyyy-MM-dd hh:mm:ss")));
            tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,groupTypeFieldCount+2,new QTableWidgetItem(newKeyItem->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")));
            updateTableWidgetView(index);
            sharedData.database.close();
        }
    }
}
void Widget::newKeyItemSlot()
{
    SharedData& sharedData = SharedData::instace();
    if(sharedData.groupList.count()==0)
    {

    }
    QString groupName=sharedData.groupList[stackedWidget->currentIndex()]->getGroupName();
    newitemdialog->setWindowTitle("在分组 "+groupName+" 中添加密码");
    newitemdialog->m_titleBar->setWindowTitle("在分组 "+groupName+" 中添加密码");
    //转到newitemdialog
    newitemdialog->loadGroupType(sharedData.groupList[stackedWidget->currentIndex()]->getGroupType());
    newitemdialog->setModal(true);
    newitemdialog->setGeometry(this->geometry().x()+this->width()/2-newitemdialog->width()/2+10,this->geometry().y()+this->height()/2-newitemdialog->height()/2+20,newitemdialog->width(),newitemdialog->height());
    newitemdialog->exec();
    newKeyItemFunction(groupName);
}
void Widget::newKeyItemFunction(QString& groupName)
{
    SharedData& sharedData = SharedData::instace();
    if(newKeyItem!=NULL&&newKeyItem->getFlag()){
        int index=0;
        for(int j=0;j<sharedData.groupList.count();j++){
            if(groupName==sharedData.groupList[j]->getGroupName())
                index=j;
        }
        Group* currentGroup=sharedData.groupList[index];
        currentGroup->append(newKeyItem);
        currentGroup->setLastEditTime();
        sharedData.database.setPassword("123456");
        QSqlQuery query(sharedData.database);
        if(!sharedData.database.open()){
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
            return;
        }else{
            QString sql=QString("update sharedData.groupList set count='%1',lastEditTime='%2' where name='%3' ")
                    .arg(currentGroup->count())
                    .arg(currentGroup->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(currentGroup->getGroupName());
            query.exec(sql);
            query.prepare("insert into "+groupName+" (type,createTime,lastEditTime)"
                                                   "VALUES (:1,:2,:3)");
            query.bindValue(":1",newKeyItem->getGroupType());
            query.bindValue(":2",newKeyItem->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":3",newKeyItem->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"));
            query.exec();
            tableWidgets[index]->insertRow(tableWidgets[index]->rowCount());
            tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,1,new QTableWidgetItem(newKeyItem->getCreateTime().toString("yyyy-MM-dd hh:mm:ss")));
            tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,2,new QTableWidgetItem(newKeyItem->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")));
            updateTableWidgetView(index);
            //            if(autofillInfo!=NULL&&!autofillInfo->mails.contains(newKeyItem->mail))
            //                autofillInfo->mails<<newKeyItem->mail,autofillInfo->mailAliases<<"";
            //            if(autofillInfo!=NULL&&newKeyItem->type==1)
            //                autofillInfo->mailAliases[autofillInfo->mails.indexOf(newKeyItem->mail)]=newKeyItem->subName;
            //            if(autofillInfo!=NULL&&!autofillInfo->mobiles.contains(newKeyItem->mobile))
            //                autofillInfo->mobiles<<newKeyItem->mobile;
            //            if(autofillInfo!=NULL&&newKeyItem->type==1&&!autofillInfo->websites.contains(newKeyItem->website))
            //                autofillInfo->websites<<newKeyItem->website;
            //            updateAutofillInfo();
            sharedData.database.close();
        }
    }
}
void Widget::removeKeyItemSlot()
{
    SharedData& sharedData = SharedData::instace();
    QList<QTableWidgetItem*> selectItems = tableWidgets[stackedWidget->currentIndex()]->selectedItems();
    QList<int> selectRows;
    for(int i=0;i<selectItems.size();i++)
    {
        if(!selectRows.contains(selectItems[i]->row()))
            selectRows<<selectItems[i]->row();
    }
    std::sort(selectRows.begin(),selectRows.end());
    QString message="是否删除已选条目:\n";
    for(int i=selectRows.size()-1;i>=0;i--)
    {
        int row=selectRows[i];
        message+=sharedData.groupList[stackedWidget->currentIndex()]->at(row)->toString();
        message+="\n";
    }
    int choice=QMessageBox::question(this,"删除条目",message);
    if(choice==QMessageBox::Yes)
    {
        for(int i=selectRows.size()-1;i>=0;i--)
        {
            int row=selectRows[i];
            QSqlQuery query(sharedData.database);
            if(!sharedData.database.open())
            {
                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
                return;
            }
            else
            {
                int index=stackedWidget->currentIndex();
                Group* currentGroup=sharedData.groupList.at(index);
                QString sql = QString("delete from '%1' where createTime = '%2' ").arg(currentGroup->getGroupName()).arg(currentGroup->at(row)->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.exec(sql);
                currentGroup->removeAt(row);
                currentGroup->setLastEditTime();
                sql=QString("update sharedData.groupList set count='%1',lastEditTime='%2' where name='%3' ").arg(currentGroup->count()).arg(currentGroup->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")).arg(currentGroup->getGroupName());
                query.exec(sql);
                tableWidgets[index]->removeRow(row);
            }
        }
    }
}
