#include "include/mainwindow.h"
#include "ui_mainwindow.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog),times(0)
{
    ui->setupUi(this);
    this->setWindowTitle("关于");
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet+= QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
    timer=new QTimer;
    ui->icon->setVisible(true);
    ui->version->setVisible(true);
    ui->base->setVisible(true);
    ui->copyright->setVisible(true);
    ui->time->setVisible(true);
    ui->egg->setVisible(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(love()));
    connect(ui->close,SIGNAL(clicked()),this,SLOT(close_clicked()));
    connect(ui->icon,SIGNAL(toggled(bool)),this,SLOT(icon_toggled(bool)));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::close_clicked()
{
    this->close();
}


void AboutDialog::icon_toggled(bool)
{
    times++;
    if(times==9)
    {
        timer->start(6500);
        ui->icon->setVisible(false);
        ui->version->setVisible(false);
        ui->base->setVisible(false);
        ui->copyright->setVisible(false);
        ui->time->setVisible(false);
        ui->egg->setVisible(true);
        MainWindow *p= (MainWindow *)parentWidget();
        p->tts->say("To My Lover : Thanks for You And Your Sincere Love . I Love You Forever !");
    }
}
void AboutDialog::love()
{
    ui->icon->setVisible(true);
    ui->version->setVisible(true);
    ui->base->setVisible(true);
    ui->copyright->setVisible(true);
    ui->time->setVisible(true);
    ui->egg->setVisible(false);
    times=0;
}
