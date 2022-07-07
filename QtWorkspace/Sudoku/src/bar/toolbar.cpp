#include"include/mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::MyToolBar()
{
    //Game ToolBar
    ToolBars[0]=ui->GameToolBar;
    ui->GameToolBar->addSeparator();
    ui->GameToolBar->setToolTip("游戏栏");
    ui->GameToolBar->setWindowTitle("游戏栏");
    ui->GameToolBar->setIconSize(QSize(25,25));
    ui->GameToolBar->addAction(Menus[0].acts[0]);
    ui->GameToolBar->addAction(Menus[1].acts[0]);
    ui->GameToolBar->addAction(Menus[1].acts[1]);
    ui->GameToolBar->addAction(Menus[1].acts[4]);
    ui->GameToolBar->addAction(Menus[1].acts[5]);
    ui->GameToolBar->addAction(Menus[1].acts[6]);
    ui->GameToolBar->addSeparator();
    //Operate ToolBar
    ToolBars[1]=ui->OperateToolBar;
    ui->OperateToolBar->setToolTip("操作栏");
    ui->OperateToolBar->setWindowTitle("操作栏");
    ui->OperateToolBar->setIconSize(QSize(25,25));
    ui->OperateToolBar->addAction(Menus[2].acts[0]);
    ui->OperateToolBar->addAction(Menus[2].acts[1]);
    ui->OperateToolBar->addAction(Menus[2].acts[2]);
    ui->OperateToolBar->addAction(Menus[2].acts[3]);
    ui->OperateToolBar->addAction(Menus[2].acts[4]);
    ui->OperateToolBar->addSeparator();
    //Function ToolBar
    ToolBars[2]=ui->FunctionToolBar;
    ui->FunctionToolBar->setToolTip("功能栏");
    ui->FunctionToolBar->setWindowTitle("功能栏");
    ui->FunctionToolBar->setIconSize(QSize(25,25));
    ui->FunctionToolBar->addAction(Menus[3].acts[3]);
    ui->FunctionToolBar->addAction(Menus[6].acts[0]);
    ui->FunctionToolBar->addAction(Menus[6].acts[1]);
    ui->FunctionToolBar->addAction(Menus[3].acts[5]);
    ui->FunctionToolBar->addSeparator();
    //Music ToolBar
    ToolBars[3]=ui->MusicToolBar;
    ui->MusicToolBar->setToolTip("音乐栏");
    ui->MusicToolBar->setWindowTitle("音乐栏");
    ui->MusicToolBar->setIconSize(QSize(25,25));
    ui->MusicToolBar->addAction(Menus[5].acts[0]);
    ui->MusicToolBar->addAction(Menus[5].acts[1]);
    ui->MusicToolBar->addAction(Menus[5].acts[2]);
    ui->MusicToolBar->addAction(Menus[5].acts[3]);
    for(int i=0;i<4;i++)
    {
        ToolBars[i]->setMovable(false);
        Menus[4].sub[2]->acts[i]->setChecked(sync->system.toolbars[i]);
    }
    Menus[4].acts[1]->setChecked(sync->view.simple_mode);
    this->setContextMenuPolicy(Qt::NoContextMenu);
}
void MainWindow::toolbardisplay_triggered()
{
    for(int i=0;i<4;i++)
        ToolBars[i]->setHidden(false),Menus[4].sub[2]->acts[i]->setChecked(true);
}
void MainWindow::toolbarhide_triggered()
{
    for(int i=0;i<4;i++)
        ToolBars[i]->setHidden(true),Menus[4].sub[2]->acts[i]->setChecked(false);
}
void MainWindow::toolbar_1_toggled()
{
    if(Menus[4].sub[2]->acts[0]->isChecked())
        ToolBars[0]->setVisible(true),sync->system.toolbars[0]=true;
    else
        ToolBars[0]->setVisible(false),sync->system.toolbars[0]=false;
}
void MainWindow::toolbar_2_toggled()
{
    if(Menus[4].sub[2]->acts[1]->isChecked())
        ToolBars[1]->setVisible(true),sync->system.toolbars[1]=true;
    else
        ToolBars[1]->setVisible(false),sync->system.toolbars[1]=false;
}
void MainWindow::toolbar_3_toggled()
{
    if(Menus[4].sub[2]->acts[2]->isChecked())
        ToolBars[2]->setVisible(true),sync->system.toolbars[2]=true;
    else
        ToolBars[2]->setVisible(false),sync->system.toolbars[2]=false;
}
void MainWindow::toolbar_4_toggled()
{
    if(Menus[4].sub[2]->acts[3]->isChecked())
        ToolBars[3]->setVisible(true),sync->system.toolbars[3]=true;
    else
        ToolBars[3]->setVisible(false),sync->system.toolbars[3]=false;
}
