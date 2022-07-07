#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private slots:
    void close_clicked();

    void icon_toggled(bool checked);

    void love();

private:
    Ui::AboutDialog *ui;
    int times;
    QTimer *timer;
};

#endif // ABOUTDIALOG_H
