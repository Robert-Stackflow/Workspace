#ifndef GROUPTYPEMANAGERDIALOG_H
#define GROUPTYPEMANAGERDIALOG_H

#include <QDialog>

namespace Ui {
class groupTypeManagerDialog;
}

class groupTypeManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit groupTypeManagerDialog(QWidget *parent = nullptr);
    ~groupTypeManagerDialog();

private:
    Ui::groupTypeManagerDialog *ui;
};

#endif // GROUPTYPEMANAGERDIALOG_H
