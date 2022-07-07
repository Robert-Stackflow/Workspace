#ifndef FILTER_H
#define FILTER_H
#include <QWidget>
#include <QListWidget>
class FilterWidget :
        public QWidget
{
    Q_OBJECT
public:
    FilterWidget(QStringList Items, QStringList showItems, int col, QWidget *parent = 0);
    ~FilterWidget();

    QStringList getShowList();

    int getColumn();

    void exec(const QPoint &pos);
signals:
    void updateFilter();
private slots:
    void slot_stateChanged();

private:

    QListWidget* m_ListWidget = nullptr;

    QStringList m_showList;

    int m_col;
};
#endif // FILTER_H
