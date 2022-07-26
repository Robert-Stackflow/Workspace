#include "widget.h"
#include "ui_widget.h"
#include "util/data.h"
#pragma warning (disable:4100)
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
void Widget::loadKeyItemFunction(QString& groupName)
{
    if(newKeyItem!=NULL&&newKeyItem->getFlag()){
        int index=0;
        int groupType=newKeyItem->getGroupType();
        int groupTypeFieldCount=Data::sharedData.groupTypeList[groupType]->count();
        for(int j=0;j<Data::sharedData.groupList.count();j++){
            if(groupName==Data::sharedData.groupList[j]->getGroupName())
                index=j;
        }
        Data::sharedData.groupList[index]->append(newKeyItem);
        if(!Data::sharedData.database.open()){
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), Data::sharedData.database.lastError().text());
            return;
        }else{
            tableWidgets[index]->insertRow(tableWidgets[index]->rowCount());
            tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,groupTypeFieldCount+1,new QTableWidgetItem(newKeyItem->getCreateTime().toString("yyyy-MM-dd hh:mm:ss")));
            tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,groupTypeFieldCount+2,new QTableWidgetItem(newKeyItem->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")));
            updateTableWidgetView(index);
            Data::sharedData.database.close();
        }
    }
}
void Widget::newKeyItemSlot()
{
    if(Data::sharedData.groupList.count()==0)
    {

    }
    QString groupName=Data::sharedData.groupList[stackedWidget->currentIndex()]->getGroupName();
    newitemdialog->setWindowTitle("在分组 "+groupName+" 中添加密码");
    newitemdialog->m_titleBar->setWindowTitle("在分组 "+groupName+" 中添加密码");
    //转到newitemdialog
    newitemdialog->loadGroupType(Data::sharedData.groupList[stackedWidget->currentIndex()]->getGroupType());
    newitemdialog->setModal(true);
    newitemdialog->setGeometry(this->geometry().x()+this->width()/2-newitemdialog->width()/2+10,this->geometry().y()+this->height()/2-newitemdialog->height()/2+20,newitemdialog->width(),newitemdialog->height());
    newitemdialog->exec();
    newKeyItemFunction(groupName);
}
void Widget::newKeyItemFunction(QString& groupName)
{
    if(newKeyItem!=NULL&&newKeyItem->getFlag()){
        int index=0;
        for(int j=0;j<Data::sharedData.groupList.count();j++){
            if(groupName==Data::sharedData.groupList[j]->getGroupName())
                index=j;
        }
        Group* currentGroup=Data::sharedData.groupList[index];
        currentGroup->append(newKeyItem);
        currentGroup->setLastEditTime();
        Data::sharedData.database.setPassword("123456");
        QSqlQuery query(Data::sharedData.database);
        if(!Data::sharedData.database.open()){
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), Data::sharedData.database.lastError().text());
            return;
        }else{
            QString sql=QString("update Data::sharedData.groupList set count='%1',lastEditTime='%2' where name='%3' ")
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
            Data::sharedData.database.close();
        }
    }
}
void Widget::removeKeyItemSlot()
{
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
        message+=Data::sharedData.groupList[stackedWidget->currentIndex()]->at(row)->toString();
        message+="\n";
    }
    int choice=QMessageBox::question(this,"删除条目",message);
    if(choice==QMessageBox::Yes)
    {
        for(int i=selectRows.size()-1;i>=0;i--)
        {
            int row=selectRows[i];
            QSqlQuery query(Data::sharedData.database);
            if(!Data::sharedData.database.open())
            {
                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), Data::sharedData.database.lastError().text());
                return;
            }
            else
            {
                int index=stackedWidget->currentIndex();
                Group* currentGroup=Data::sharedData.groupList.at(index);
                QString sql = QString("delete from '%1' where createTime = '%2' ").arg(currentGroup->getGroupName()).arg(currentGroup->at(row)->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.exec(sql);
                currentGroup->removeAt(row);
                currentGroup->setLastEditTime();
                sql=QString("update Data::sharedData.groupList set count='%1',lastEditTime='%2' where name='%3' ").arg(currentGroup->count()).arg(currentGroup->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")).arg(currentGroup->getGroupName());
                query.exec(sql);
                tableWidgets[index]->removeRow(row);
            }
        }
    }
}
