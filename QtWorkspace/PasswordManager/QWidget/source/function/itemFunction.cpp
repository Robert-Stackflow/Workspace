#include "dialog/widget.h"
#include "ui_widget.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
QString KEY::toString(){
    QString result;
    return result;
}
void Widget::addItemSlot()
{
//    newitemdialog->ui->tabWidget->setCurrentIndex(tables[stackedWidget->currentIndex()]->type);
//    newitemdialog->setWindowTitle("在分组 "+tables[stackedWidget->currentIndex()]->name+" 中添加密码");
//    newitemdialog->m_titleBar->setWindowTitle("在分组 "+tables[stackedWidget->currentIndex()]->name+" 中添加密码");
    //打开Dialog
    newitemdialog->setModal(true);
    newitemdialog->setGeometry(this->geometry().x()+this->width()/2-newitemdialog->width()/2+10,this->geometry().y()+this->height()/2-newitemdialog->height()/2+20,newitemdialog->width(),newitemdialog->height());
    newitemdialog->exec();
}
void Widget::addItemFunction(QString& tableName,int mode)
{//mode=1表示插入,mode=0表示加载
    if(newKey!=NULL&&newKey->flag)
    {
        int index=0;
        for(int j=0;j<tables.size();j++)
        {
            if(tableName==tables[j]->name)
                index=j;
        }
        tables[index]->keys<<newKey;
        tables[index]->lastEditTime=newKey->lastEditTime;
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
            if(mode==1)
            {
                QString sql=QString("update tables set count='%1',lastEditTime='%2' where name='%3' ").arg(tables[index]->keys.size()).arg(tables[index]->lastEditTime.toString("yyyy-MM-dd hh:mm:ss")).arg(tables[index]->name);
                query.exec(sql);
            }
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
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,8,new QTableWidgetItem(newKey->createTime.toString("yyyy-MM-dd hh:mm:ss")));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,9,new QTableWidgetItem(newKey->lastEditTime.toString("yyyy-MM-dd hh:mm:ss")));
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
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,6,new QTableWidgetItem(newKey->createTime.toString("yyyy-MM-dd hh:mm:ss")));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,7,new QTableWidgetItem(newKey->lastEditTime.toString("yyyy-MM-dd hh:mm:ss")));
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
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,5,new QTableWidgetItem(newKey->createTime.toString("yyyy-MM-dd hh:mm:ss")));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,6,new QTableWidgetItem(newKey->lastEditTime.toString("yyyy-MM-dd hh:mm:ss")));
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
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,3,new QTableWidgetItem(newKey->createTime.toString("yyyy-MM-dd hh:mm:ss")));
                tableWidgets[index]->setItem(tableWidgets[index]->rowCount()-1,4,new QTableWidgetItem(newKey->lastEditTime.toString("yyyy-MM-dd hh:mm:ss")));
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
void Widget::tableWidgetContextMenuRequested(QPoint pos)
{
    cursorPos=new QPoint;
    *cursorPos=pos;
    tableWidgetMenu->exec(QCursor::pos());
}
void Widget::removeItemSlot()
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
        message+=tables[stackedWidget->currentIndex()]->keys[row]->name;
        message+="\n";
    }
    int choice=QMessageBox::question(this,"删除条目",message);
    if(choice==QMessageBox::Yes)
    {
        for(int i=selectRows.size()-1;i>=0;i--)
        {
            int row=selectRows[i];
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
                int index=stackedWidget->currentIndex();
                QString sql = QString("delete from '%1' where createTime = '%2' ").arg(tables[index]->name).arg(tables[index]->keys[row]->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.exec(sql);
                tables[index]->keys.removeAt(row);
                tables[index]->lastEditTime=QDateTime::currentDateTime();
                sql=QString("update tables set count='%1',lastEditTime='%2' where name='%3' ").arg(tables[index]->keys.size()).arg(tables[index]->lastEditTime.toString("yyyy-MM-dd hh:mm:ss")).arg(tables[index]->name);
                query.exec(sql);
                tableWidgets[index]->removeRow(row);
            }
        }
    }
}
void Widget::openWebsiteSlot()
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = tableWidgets[stackedWidget->currentIndex()]->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    QDesktopServices::openUrl(QUrl(tables[stackedWidget->currentIndex()]->keys[row]->website, QUrl::TolerantMode));
}
void Widget::copyAllSlot()
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = tableWidgets[stackedWidget->currentIndex()]->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    QClipboard *clip = QApplication::clipboard();
    clip->setText(tables[stackedWidget->currentIndex()]->keys[row]->toString());
}
void Widget::searchSlot(const QString& text)
{
    int rowCount=tableWidgets[stackedWidget->currentIndex()]->rowCount();
    if (text=="")
    {
        for (int i = 0; i < rowCount; i++)
            tableWidgets[stackedWidget->currentIndex()]->setRowHidden(i, false);
    }
    else
    {
        QList <QTableWidgetItem *> item = tableWidgets[stackedWidget->currentIndex()]->findItems(text,Qt::MatchCaseSensitive|Qt::MatchContains);
        for (int i = 0; i < rowCount; i++)
            tableWidgets[stackedWidget->currentIndex()]->setRowHidden(i, true);
        if (!item.isEmpty()) {
            for (int i = 0; i < item.count(); i++) {
                tableWidgets[stackedWidget->currentIndex()]->setRowHidden(item.at(i)->row(),false);
            }
        }
    }
}
void Widget::tableWidgetDoubleClickedSlot(int row,int column)
{
    QClipboard *clip = QApplication::clipboard();
    clip->setText(tableWidgets[stackedWidget->currentIndex()]->item(row,column)->text());
}
void Widget::tableWidgetClickedSlot(int row,int column)
{
    int type=tables[stackedWidget->currentIndex()]->type;
    int certainColumn=0;
    switch(type)
    {
    case 0:
    case 1:
    case 2:
        certainColumn=3;
        break;
    case 3:
        certainColumn=1;
        break;
    }
    if(column==certainColumn)
    {
        if(tableWidgets[stackedWidget->currentIndex()]->item(row,column)->text()=="******")
            tableWidgets[stackedWidget->currentIndex()]->item(row,column)->setText(tables[stackedWidget->currentIndex()]->keys[row]->password);
        else
            tableWidgets[stackedWidget->currentIndex()]->item(row,column)->setText("******");
    }
}
void Widget::moveMenuSlot()
{
    QAction* send=(QAction*)sender();
    QList<QTableWidgetItem*> selectItems = tableWidgets[stackedWidget->currentIndex()]->selectedItems();
    QList<int> selectRows;
    for(int i=0;i<selectItems.size();i++)
    {
        if(!selectRows.contains(selectItems[i]->row()))
            selectRows<<selectItems[i]->row();
    }
    std::sort(selectRows.begin(),selectRows.end());
    QString message=QString("是否将已选条目从 '%1' 移动到 '%2' :\n").arg(tables[stackedWidget->currentIndex()]->name).arg(send->text());
    for(int i=selectRows.size()-1;i>=0;i--)
    {
        int row=selectRows[i];
        message+=tables[stackedWidget->currentIndex()]->keys[row]->name;
        message+="\n";
    }
    int choice=QMessageBox::question(this,"移动条目",message);
    if(choice==QMessageBox::Yes)
    {
        for(int i=selectRows.size()-1;i>=0;i--)
        {
            int row=selectRows[i];
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
                //添加到新表中
                QString newName=send->text();
                int index=stackedWidget->currentIndex();
                newKey=tables[index]->keys[row];
                addItemFunction(newName,1);
                //从原表中删除
                QString sql = QString("delete from '%1' where createTime = '%2' ").arg(tables[index]->name).arg(tables[index]->keys[row]->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.exec(sql);
                tables[index]->keys.removeAt(row);
                tables[index]->lastEditTime=QDateTime::currentDateTime();
                sql=QString("update tables set count='%1',lastEditTime='%2' where name='%3' ").arg(tables[index]->keys.size()).arg(tables[index]->lastEditTime.toString("yyyy-MM-dd hh:mm:ss")).arg(tables[index]->name);
                query.exec(sql);
                tableWidgets[index]->removeRow(row);
            }
        }
    }
}
void Widget::copyMenuSlot()
{
    QAction* send=(QAction*)sender();
    QList<QTableWidgetItem*> selectItems = tableWidgets[stackedWidget->currentIndex()]->selectedItems();
    QList<int> selectRows;
    for(int i=0;i<selectItems.size();i++)
    {
        if(!selectRows.contains(selectItems[i]->row()))
            selectRows<<selectItems[i]->row();
    }
    std::sort(selectRows.begin(),selectRows.end());
    QString message=QString("是否将已选条目从 '%1' 移动到 '%2' :\n").arg(tables[stackedWidget->currentIndex()]->name).arg(send->text());
    for(int i=selectRows.size()-1;i>=0;i--)
    {
        int row=selectRows[i];
        message+=tables[stackedWidget->currentIndex()]->keys[row]->name;
        message+="\n";
    }
    int choice=QMessageBox::question(this,"移动条目",message);
    if(choice==QMessageBox::Yes)
    {
        for(int i=selectRows.size()-1;i>=0;i--)
        {
            int row=selectRows[i];
            //添加到新表中
            QString newName=send->text();
            int index=stackedWidget->currentIndex();
            newKey=new KEY;
            newKey->createTime=tables[index]->keys[row]->createTime;
            newKey->lastEditTime=tables[index]->keys[row]->lastEditTime;
            newKey->type=tables[index]->keys[row]->type;
            newKey->flag=1;
            newKey->id=tables[index]->keys[row]->id;
            newKey->mail=tables[index]->keys[row]->mail;
            newKey->mobile=tables[index]->keys[row]->mobile;
            newKey->name=tables[index]->keys[row]->name;
            newKey->nickName=tables[index]->keys[row]->nickName;
            newKey->password=tables[index]->keys[row]->password;
            newKey->remark=tables[index]->keys[row]->remark;
            newKey->subName=tables[index]->keys[row]->subName;
            newKey->website=tables[index]->keys[row]->website;
            addItemFunction(newName,1);
        }
    }
}
