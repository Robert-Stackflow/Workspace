#include "include/library/library.h"
#include <QVBoxLayout>
#include <QEventLoop>
#include <QListWidgetItem>
#include <QList>
#include <QCheckBox>
#include <QSet>
FilterWidget::FilterWidget(QStringList Items, QStringList showItems, int col, QWidget *parent/*=0*/):
    QWidget(parent),
    m_col(col)
{
    m_ListWidget = new QListWidget(this);
    m_ListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->setMargin(0);
    lay->setSpacing(0);
    setLayout(lay);
    int maxwidth=-1;
    for(int i=0;i<Items.size();i++)
    {
        QString var=Items[i];
        QCheckBox* checkBox = new QCheckBox(this);
        checkBox->setText(var);
        if(showItems.contains(var))
        {
            m_showList.append(var);
            checkBox->setChecked(true);
        }
        connect(checkBox, &QCheckBox::stateChanged, this, &FilterWidget::slot_stateChanged);
        QListWidgetItem *item = new QListWidgetItem();
        m_ListWidget->addItem(item);
        m_ListWidget->setItemWidget(item,checkBox);
        maxwidth=maxwidth>checkBox->width()?maxwidth:checkBox->width();
    }
    if(Items.size()<=5)
        this->setFixedHeight(Items.size()*30);
    else
        this->setFixedHeight(150);
    lay->addWidget(m_ListWidget);
    this->setFixedWidth(maxwidth+20);
}

FilterWidget::~FilterWidget()
{
}

QStringList FilterWidget::getShowList()
{
    return m_showList;
}

int FilterWidget::getColumn()
{
    return m_col;
}

void FilterWidget::exec(const QPoint & pos)
{
    setAttribute(Qt::WA_ShowModal, true);
    move(pos);
    show();
    QEventLoop loop;
    loop.exec();
}

void FilterWidget::slot_stateChanged()
{
    m_showList.clear();
    for (int i = 0; i < m_ListWidget->count(); i++)
    {
        QListWidgetItem *item = m_ListWidget->item(i);
        QCheckBox *checkBox = static_cast<QCheckBox *>(m_ListWidget->itemWidget(item));
        if (checkBox->isChecked())
            m_showList.append(checkBox->text());
    }
    emit updateFilter();
}
