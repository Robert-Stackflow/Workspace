#include"include/mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::MyTrayIcon()
{
    trayicon=new TrayIcon;
    trayicon->systemTray = new QSystemTrayIcon(this);
    trayicon->systemTray->setIcon(QIcon(":/icons/icons/sudoku.ico"));
    trayicon->systemTray->setToolTip("Sudoku");
    trayicon->systemTray->show();

    trayicon->Traymenu = new QMenu(this);
    trayicon->Traywindow = new QAction(trayicon->Traymenu);
    trayicon->Traynew = new QAction(trayicon->Traymenu);
    trayicon->Traysave = new QAction(trayicon->Traymenu);
    trayicon->Trayexit =new QAction(trayicon->Traymenu);
    trayicon->Trayoption=new QAction(trayicon->Traymenu);

    trayicon->Traywindow->setText("隐藏界面");
    trayicon->Traynew->setText("新游戏");
    trayicon->Traysave->setText("保存进度");
    trayicon->Trayexit->setText("退出");
    trayicon->Trayoption->setText("选项");

    trayicon->Traymenu->addAction(trayicon->Traywindow);
    trayicon->Traymenu->addSeparator();
    trayicon->Traymenu->addAction(trayicon->Traynew);
    trayicon->Traymenu->addAction(trayicon->Traysave);
    trayicon->Traymenu->addSeparator();
    trayicon->Traymenu->addAction(trayicon->Trayoption);
    trayicon->Traymenu->addAction(trayicon->Trayexit);

    trayicon->systemTray->setContextMenu(trayicon->Traymenu);
    connect(trayicon->systemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this ,SLOT(activeTray(QSystemTrayIcon::ActivationReason)));
    connect(trayicon->Traywindow,SIGNAL(triggered()),
            this ,SLOT(TraywindowSlot()));
    //    connect(trayicon->Traynew,SIGNAL(triggered()),
    //            this ,SLOT(quit()));
    //    connect(trayicon->Traysave,SIGNAL(triggered()),
    //            this ,SLOT(quit()));
    connect(trayicon->Trayexit,SIGNAL(triggered()),
            this ,SLOT(quit()));
    connect(trayicon->Trayoption,SIGNAL(triggered()),
            this ,SLOT(option_triggered()));

    Menus[4].sub[3]->acts[sync->view.trayicon]->setChecked(true);
    if(sync->view.trayicon==0)
        trayicon->systemTray->setVisible(false);
    else if(sync->view.trayicon==1)
    {
        trayicon->systemTray->setIcon(QIcon(":/icons/icons/sudoku.ico"));
        trayicon->systemTray->setVisible(true);
    }
    else if(sync->view.trayicon==2)
    {
        trayicon->systemTray->setIcon(QIcon(":/icons/icons/sudoku-night.ico"));
        trayicon->systemTray->setVisible(true);
    }
}
void MainWindow::TraywindowSlot()
{
    if(trayicon->Traywindow->text()==QString("隐藏界面"))
    {
        this->hide();
        trayicon->Traywindow->setText("显示界面");
    }
    else
    {
        this->showNormal();
        this->raise();
        trayicon->Traywindow->setText("隐藏界面");
    }
}
void MainWindow::quit()
{
    WriteSettings();
    music->updateUserFile();
    qApp->quit();
}
void MainWindow::activeTray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Context:
        trayicon->Traymenu->show();
        break;
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        this->raise();
        break;
    case QSystemTrayIcon::Trigger:
        this->hide();
        break;
    default:
        break;
    }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    WriteSettings();
    trayicon->Traywindow->setChecked(false);
    this->hide();
    event->ignore();
}
void MainWindow::changeEvent(QEvent *event)
{
    if(this->windowState()==Qt::WindowMinimized)
    {
        this->close();
        event->ignore();
    }
}
void MainWindow::MyStatusBar()
{
    ui->statusBar->setSizeGripEnabled(false);
    ui->statusBar->showMessage(tr("就绪"));
    ui->statusBar->addAction(Menus[6].acts[0]);
    ui->statusBar->setVisible(true);
}
void MainWindow::statusbarvisible_triggered()
{
    if(Menus[4].acts[2]->isChecked())
        ui->statusBar->setHidden(false),sync->view.statusbar=1;
    else
        ui->statusBar->setVisible(false),sync->view.statusbar=0;
}
void MainWindow::trayiconhide_triggered()
{
    for(int i=0;i<3;i++)
        Menus[4].sub[3]->acts[i]->setChecked(false);
    Menus[4].sub[3]->acts[0]->setChecked(true);
    trayicon->systemTray->setVisible(false);
    sync->view.trayicon=0;
}
void MainWindow::trayiconlight_triggered()
{
    for(int i=0;i<3;i++)
        Menus[4].sub[3]->acts[i]->setChecked(false);
    Menus[4].sub[3]->acts[1]->setChecked(true);
    trayicon->systemTray->setIcon(QIcon(":/icons/icons/sudoku.ico"));
    trayicon->systemTray->setVisible(true);
    sync->view.trayicon=1;
}
void MainWindow::trayiconnight_triggered()
{
    for(int i=0;i<3;i++)
        Menus[4].sub[3]->acts[i]->setChecked(false);
    Menus[4].sub[3]->acts[2]->setChecked(true);
    trayicon->systemTray->setIcon(QIcon(":/icons/icons/sudoku-night.ico"));
    trayicon->systemTray->setVisible(true);
    sync->view.trayicon=2;
}
