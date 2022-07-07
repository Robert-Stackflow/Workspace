#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include<QColorDialog>
Theme::Theme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Theme)
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
    connect(ui->colorplate_bg,SIGNAL(clicked()),this,SLOT(colorDialog()));
    connect(ui->colorplate_conflict,SIGNAL(clicked()),this,SLOT(colorDialog()));
    connect(ui->colorplate_fix,SIGNAL(clicked()),this,SLOT(colorDialog()));
    connect(ui->colorplate_space,SIGNAL(clicked()),this,SLOT(colorDialog()));
}

Theme::~Theme()
{
    delete ui;
}

QColor Theme::colorDialog()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    return color;
}
