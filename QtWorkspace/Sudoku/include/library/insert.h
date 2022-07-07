#ifndef INSERT_H
#define INSERT_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlTableModel>
#include <QTableWidget>
#include <QHeaderView>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QPoint>
#include <QDate>
#include <QProcess>
#include <QInputDialog>

namespace Ui {
class Insert;
}

class Insert : public QDialog
{
    Q_OBJECT

public:
    void recSignal();
    explicit Insert(QWidget *parent = nullptr);
    ~Insert();

private slots:
    void getNewLibName();

    void yes_clicked();

    void no_clicked();

    void updateView(int);

    void tableId_textEdited(const QString &arg1);

    void puzzleId_textEdited(const QString &arg1);

    void puzzlecontent_textEdited(const QString &arg1);

private:
    Ui::Insert *ui;
    friend class Library;
    int type;//0代表数据库，1代表数据表，2代表数据记录
};

#endif // INSERT_H
