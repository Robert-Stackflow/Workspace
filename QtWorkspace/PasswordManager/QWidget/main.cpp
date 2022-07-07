#include "widget.h"
#include "logindialog.h"
#include "ui_logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("黑体");
    a.setFont(font);
    loginDialog login;
    login.show();
//    login.ui->yes->click();
    return a.exec();
}
