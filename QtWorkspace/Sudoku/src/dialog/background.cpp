#include "include/mainwindow.h"
#include "ui_mainwindow.h"

BackGround::BackGround(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackGround)
{
    ui->setupUi(this);
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet+= QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
}

BackGround::~BackGround()
{
    delete ui;
}
