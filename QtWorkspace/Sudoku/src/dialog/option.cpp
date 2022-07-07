#include "include/mainwindow.h"
#include "ui_mainwindow.h"
Option::Option(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Option)
{
    ui->setupUi(this);
    MainWindow *p= (MainWindow *)parentWidget();
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet+= QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
    QStringList level;
    for(int i=0;i<5;i++)
        level<<p->Menus[0].sub[1]->acts[i]->text();
    ui->gamelevelbox->addItems(level);
    QStringList type;
    for(int i=0;i<6;i++)
        type<<p->Menus[0].sub[0]->acts[i]->text();
    ui->gametypebox->addItems(type);
    ui->candidatecountbox->setRange(0,9);
    ui->thresholdbox->setMinimum(10);
    connect(ui->gamelevelbox,SIGNAL(currentIndexChanged(int)),this,SLOT(level_changed(int)));
    connect(ui->gametypebox,SIGNAL(currentIndexChanged(int)),this,SLOT(type_changed(int)));
    connect(ui->candidatecountbox,SIGNAL(valueChanged(int)),this,SLOT(candidate_changed(int)));
    connect(ui->thresholdbox,SIGNAL(valueChanged(int)),this,SLOT(threshold_changed(int)));
    connect(ui->CheckBox_load,SIGNAL(toggled(bool)),this,SLOT(load_changed()));
    connect(ui->CheckBox_timing,SIGNAL(toggled(bool)),this,SLOT(timing_changed()));
    connect(ui->CheckBox_longtime,SIGNAL(toggled(bool)),this,SLOT(longtime_changed()));
    connect(ui->CheckBox_tips,SIGNAL(toggled(bool)),this,SLOT(tips_changed()));
    connect(ui->yes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(cancel_clicked()));
}

Option::~Option()
{
    delete ui;
}

void Option::level_changed(int index)
{
    MainWindow *p= (MainWindow *)parentWidget();
    p->sync->game.level=index;
    for(int i=0;i<5;i++)
        p->Menus[0].sub[1]->acts[i]->setChecked(false);
    p->Menus[0].sub[1]->acts[p->sync->game.level]->setChecked(true);
}

void Option::type_changed(int index)
{
    MainWindow *p= (MainWindow *)parentWidget();
    p->sync->game.type=index;
    for(int i=0;i<6;i++)
        p->Menus[0].sub[0]->acts[i]->setChecked(false);
    p->Menus[0].sub[0]->acts[p->sync->game.type]->setChecked(true);
}
void Option::candidate_changed(int num)
{
    MainWindow *p= (MainWindow *)parentWidget();
    p->sync->game.candidates=num;
}
void Option::threshold_changed(int num)
{
    MainWindow *p= (MainWindow *)parentWidget();
    p->sync->game.auto_stop_threshold=num;
}
void Option::load_changed()
{
    MainWindow *p= (MainWindow *)parentWidget();
    p->sync->game.auto_stop_threshold=ui->CheckBox_load->isChecked();
}
void Option::longtime_changed()
{
    MainWindow *p= (MainWindow *)parentWidget();
    p->sync->game.auto_stop_timing=ui->CheckBox_longtime->isChecked();
}
void Option::timing_changed()
{
    MainWindow *p= (MainWindow *)parentWidget();
    p->sync->game.auto_timing=ui->CheckBox_timing->isChecked();
}
void Option::tips_changed()
{
    MainWindow *p= (MainWindow *)parentWidget();
    p->sync->game.conflict_tips=ui->CheckBox_tips->isChecked();
    if(p->sync->game.conflict_tips)
    {
        p->Menus[1].acts[4]->setEnabled(true);
        p->ToolBars[0]->insertAction(p->Menus[1].acts[5],p->Menus[1].acts[4]);
    }
    else
    {
        p->Menus[1].acts[4]->setEnabled(false);
        p->ToolBars[0]->removeAction(p->Menus[1].acts[4]);
    }
}

void Option::yes_clicked()
{
    this->close();
}

void Option::cancel_clicked()
{
    this->close();
}
