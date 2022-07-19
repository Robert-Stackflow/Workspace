#ifndef NEWGROUPDIALOG_H
#define NEWGROUPDIALOG_H

#include <QDialog>
#include "controller/titleBar.h"
namespace Ui {
class newGroupDialog;
}

class newGroupDialog : public QDialog
{
    Q_OBJECT

public:
    TitleBar *m_titleBar;
    explicit newGroupDialog(QWidget *parent = nullptr);
    ~newGroupDialog();
    void setWindowTitle(const QString& title);

private:
    Ui::newGroupDialog *ui;
private:
    QString styleSheet;
};

#endif // NEWGROUPDIALOG_H
