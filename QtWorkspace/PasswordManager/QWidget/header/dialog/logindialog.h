#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    Ui::loginDialog *ui;
    QPixmap PixmapToRound(const QPixmap &src, int radius);
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();
private:
    QString styleSheet;
private slots:
    void confirmClicked();
};

#endif // LOGINDIALOG_H
