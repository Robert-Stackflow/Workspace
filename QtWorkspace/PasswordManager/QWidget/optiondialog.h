#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include "titleBar.h"

namespace Ui {
class optionDialog;
}

class optionDialog : public QDialog
{
    Q_OBJECT

public:
    TitleBar *m_titleBar;
    explicit optionDialog(QWidget *parent = nullptr);
    ~optionDialog();

private:
    Ui::optionDialog *ui;
    QString styleSheet;
};

#endif // OPTIONDIALOG_H
