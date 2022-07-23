#include "controller/draggabletablewidget.h"
#include <QDebug>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
draggableTableWidget::draggableTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    this->setDragDropMode(QAbstractItemView::InternalMove);
    this->setDropIndicatorShown(true);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
}
void draggableTableWidget::dropEvent(QDropEvent *event)
{
    int row_src,row_dst;
    row_src = this->currentRow();
    QTableWidgetItem *item = this->itemAt(event->pos());
    if(item !=nullptr){
        row_dst = item->row();
        row_src = (row_src > row_dst? row_src + 1:row_src);
        row_dst = (row_src < row_dst? row_dst + 1:row_dst);
        this->insertRow(row_dst);
    }
    else{
        row_dst = this->rowCount();
        this->insertRow(row_dst);
    }
    for(int i = 0;i < this->columnCount();i++){
        this->setItem(row_dst,i,this->takeItem(row_src,i));
    }
    this->removeRow(row_src);
}
