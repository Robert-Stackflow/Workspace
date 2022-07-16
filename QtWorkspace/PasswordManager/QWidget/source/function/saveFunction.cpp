#include "dialog/widget.h"
#include "ui_widget.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
void Widget::saveMenuTriggered()
{
    QAction* send=(QAction*)sender();
    save->setDefaultAction(send);
}
void Widget::saveSlot()
{
    QAction* activeAction=((QToolButton*)sender())->defaultAction();
    QString caption;
    caption="将分组 "+tables[stackedWidget->currentIndex()]->name+" 另存为"+save->defaultAction()->text()+"文件";
    if(activeAction==saveAsPDF)
    {
        QString saveFilePath=QFileDialog::getSaveFileName(this,caption,"./",tr("PDF files(*.pdf)"));
        if(saveFilePath=="")
            return;
        QDesktopServices::openUrl(QUrl(saveFilePath));
    }
    else if(activeAction==saveAsExcel)
    {
        QString saveFilePath=QFileDialog::getSaveFileName(this,caption,"./",tr("Xlsx files(*.xlsx)"));
        if(saveFilePath=="")
            return;
        QXlsx::Document xlsxW;
        int row=1;
        for(int i=0;i<tables.size();i++)
        {
            xlsxW.addSheet(tables[i]->name);
            xlsxW.selectSheet(tables[i]->name);
            for(int j=0;j<header[tables[i]->type].size()-2;j++)
                xlsxW.write(QString('A'+j)+QString::number(row),header[tables[i]->type][j]);
            switch(tables[i]->type)
            {
            case 0:
                for(int row=0;row<tables[i]->keys.size();row++)
                {
                    xlsxW.write(QString('A')+QString::number(row+2),tables[i]->keys[row]->name);
                    xlsxW.write(QString('A'+1)+QString::number(row+2),tables[i]->keys[row]->nickName);
                    xlsxW.write(QString('A'+2)+QString::number(row+2),tables[i]->keys[row]->id);
                    xlsxW.write(QString('A'+3)+QString::number(row+2),tables[i]->keys[row]->password);
                    xlsxW.write(QString('A'+4)+QString::number(row+2),tables[i]->keys[row]->mobile);
                    xlsxW.write(QString('A'+5)+QString::number(row+2),tables[i]->keys[row]->mail);
                    xlsxW.write(QString('A'+6)+QString::number(row+2),tables[i]->keys[row]->website);
                    xlsxW.write(QString('A'+7)+QString::number(row+2),tables[i]->keys[row]->remark);
                }
                break;
            case 1:
                for(int row=0;row<tables[i]->keys.size();row++)
                {
                    xlsxW.write(QString('A')+QString::number(row+2),tables[i]->keys[row]->name);
                    xlsxW.write(QString('A'+1)+QString::number(row+2),tables[i]->keys[row]->mail);
                    xlsxW.write(QString('A'+2)+QString::number(row+2),tables[i]->keys[row]->subName);
                    xlsxW.write(QString('A'+3)+QString::number(row+2),tables[i]->keys[row]->password);
                    xlsxW.write(QString('A'+4)+QString::number(row+2),tables[i]->keys[row]->website);
                    xlsxW.write(QString('A'+5)+QString::number(row+2),tables[i]->keys[row]->remark);
                }
                break;
            case 2:
                for(int row=0;row<tables[i]->keys.size();row++)
                {
                    xlsxW.write(QString('A')+QString::number(row+2),tables[i]->keys[row]->name);
                    xlsxW.write(QString('A'+1)+QString::number(row+2),tables[i]->keys[row]->mail);
                    xlsxW.write(QString('A'+2)+QString::number(row+2),tables[i]->keys[row]->password);
                    xlsxW.write(QString('A'+3)+QString::number(row+2),tables[i]->keys[row]->website);
                    xlsxW.write(QString('A'+4)+QString::number(row+2),tables[i]->keys[row]->remark);
                }
                break;
            case 3:
                for(int row=0;row<tables[i]->keys.size();row++)
                {
                    xlsxW.write(QString('A')+QString::number(row+2),tables[i]->keys[row]->name);
                    xlsxW.write(QString('A'+1)+QString::number(row+2),tables[i]->keys[row]->password);
                    xlsxW.write(QString('A'+2)+QString::number(row+2),tables[i]->keys[row]->remark);
                }
                break;
            }
        }
        xlsxW.selectSheet(tables[0]->name);
        if (xlsxW.saveAs(saveFilePath))
        {
            qDebug()<<"[Info] success to write xlsx file";
        }
        QDesktopServices::openUrl(QUrl(saveFilePath));
    }
    else if(activeAction==saveAsCSV)
    {
        QString saveFilePath=QFileDialog::getSaveFileName(this,caption,"./",tr("CSV files(*.csv)"));
        if(saveFilePath=="")
            return;
        QFile file(saveFilePath);
        if(!file.open(QIODevice::WriteOnly))
            return;
        for(int j=0;j<header[tables[stackedWidget->currentIndex()]->type].size()-2;j++)
        {
            file.write(header[tables[stackedWidget->currentIndex()]->type][j].toLocal8Bit().data());
            if(j<header[tables[stackedWidget->currentIndex()]->type].size()-3)
                file.write(",");
            else
                file.write("\n");
        }
        switch(tables[stackedWidget->currentIndex()]->type)
        {
        case 0:
            for(int row=0;row<tables[stackedWidget->currentIndex()]->keys.size();row++)
            {
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->name.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->nickName.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->id.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->password.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->mobile.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->mail.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->website.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->remark.toLocal8Bit().data());
                file.write("\n");
            }
            break;
        case 1:
            for(int row=0;row<tables[stackedWidget->currentIndex()]->keys.size();row++)
            {
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->name.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->mail.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->subName.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->password.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->website.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->remark.toLocal8Bit().data());
                file.write("\n");
            }
            break;
        case 2:
            for(int row=0;row<tables[stackedWidget->currentIndex()]->keys.size();row++)
            {
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->name.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->mail.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->password.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->website.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->remark.toLocal8Bit().data());
                file.write("\n");
            }
            break;
        case 3:
            for(int row=0;row<tables[stackedWidget->currentIndex()]->keys.size();row++)
            {
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->name.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->password.toLocal8Bit().data());
                file.write(",");
                file.write(tables[stackedWidget->currentIndex()]->keys[row]->remark.toLocal8Bit().data());
                file.write("\n");
            }
            break;
        }
        QDesktopServices::openUrl(QUrl(saveFilePath));
        file.close();
    }
}
