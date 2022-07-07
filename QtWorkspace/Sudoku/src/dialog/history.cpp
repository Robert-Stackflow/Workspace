#include "include/mainwindow.h"
#include "ui_mainwindow.h"

history::history(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    this->setWindowTitle("历史记录");
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

history::~history()
{
    delete ui;
}
