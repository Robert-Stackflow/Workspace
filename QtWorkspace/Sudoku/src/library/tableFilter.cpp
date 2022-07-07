#include "include/mainwindow.h"
#include "ui_mainwindow.h"
void Library::filterChanged()
{
    if (filterWidget != nullptr)
    {
        QStringList showList = filterWidget->getShowList();
        int row=filterWidget->getColumn();
        filter(row,showList);
        delete filterWidget;
        filterWidget = nullptr;
    }
}
void Library::onHeaderClicked(int col)
{
    //QSet类去重
    QSet<QString> items;
    QSet<QString> showItems;
    int rows = activeWidget->rowCount();
    for (int i = 0; i < rows; i++)
    {
        if(activeWidget!=NULL&&activeWidget->isRowHidden(i)==false)
        {
            QString strItem = activeWidget->item(i,col)->text();
            items.insert(strItem);
            if (map.value(col).contains(strItem))
                showItems.insert(strItem);
        }
    }
    //转换为QList
    QStringList strShowItems=showItems.values();
    QStringList strItems=items.values();
    closeFilterWidget();
    filterWidget = new FilterWidget(strItems,strShowItems,col,activeWidget);
    connect(filterWidget,&FilterWidget::updateFilter,this,&Library::filterChanged);
    filterWidget->exec(activeWidget->mapFromGlobal(cursor().pos()));
}
void Library::initMap()
{
    for (int col = 0; col < activeWidget->columnCount(); col++)
    {
        QStringList strList;
        for (int row = 0; row < activeWidget->rowCount(); row++)
        {
            QString	strItem = activeWidget->item(row, col)->text();
            strList.append(strItem);
        }
        map[col] = strList;
    }
}
bool Library::eventFilter(QObject *target, QEvent *event)
{
    QMouseEvent *e = static_cast<QMouseEvent *>(event);
    if (e == nullptr)
    {
        return QWidget::eventFilter(target, event);
    }
    if (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease)
    {
        closeFilterWidget();
    }
    return QWidget::eventFilter(target, event);
}
void Library::filter(int col, QStringList showList)
{
    map[col] = showList;
    for (int i = 0; i < activeWidget->rowCount(); i++)
    {
        if (!map.value(col).contains(activeWidget->item(i,col)->text()))
            activeWidget->setRowHidden(i, true);
        else
            activeWidget->setRowHidden(i, false);
    }
}
void Library::closeFilterWidget()
{
    if (filterWidget != nullptr)
    {
        QStringList showList = filterWidget->getShowList();
        int row=filterWidget->getColumn();
        filter(row,showList);
        delete filterWidget;
        filterWidget = nullptr;
    }
}
