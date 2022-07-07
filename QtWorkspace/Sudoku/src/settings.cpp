#include"include/mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::WriteSettings()
{
    //    settings=new QSettings("D:/HUST-Courses/DS Course Design/Sudoku/config.ini",QSettings::IniFormat);
    {
        settings->beginGroup("system");
        settings->setValue("startupstatus",1);
        {
            settings->beginGroup("window");
            sync->system.window.size=size();
            sync->system.window.pos=pos();
            settings->setValue("size",sync->system.window.size);
            settings->setValue("pos", sync->system.window.pos);
            settings->endGroup();
        }
        {
            settings->beginGroup("toolbars");
            settings->setValue("game", sync->system.toolbars[0]);
            settings->setValue("edit", sync->system.toolbars[1]);
            settings->setValue("function", sync->system.toolbars[2]);
            settings->setValue("music", sync->system.toolbars[3]);
            settings->endGroup();
        }
        settings->endGroup();
    }
    {
        settings->beginGroup("game");
        settings->setValue("level",sync->game.level);
        settings->setValue("type",sync->game.type);
        settings->setValue("candidates",sync->game.candidates);
        settings->setValue("conflict_tips",sync->game.conflict_tips);
        settings->setValue("loadlast",sync->game.loadlast);
        settings->setValue("auto_timing",sync->game.auto_timing);
        settings->setValue("auto_stop_timing",sync->game.auto_stop_timing);
        settings->setValue("auto_stop_threshold",sync->game.auto_stop_threshold);
        settings->endGroup();
    }
    {
        settings->beginGroup("view");
        settings->setValue("font",sync->view.font);
        settings->setValue("full_mode",sync->view.full_mode);
        settings->setValue("simple_mode",sync->view.simple_mode);
        settings->setValue("statusbar",sync->view.statusbar);
        settings->setValue("language",sync->view.language);
        settings->setValue("trayicon",sync->view.trayicon);
        settings->endGroup();
    }
    {
        settings->beginGroup("advanced");
        settings->setValue("closed_prompt_box",sync->advanced.closed_prompt_box);
        settings->setValue("closed_to_trayicon",sync->advanced.closed_to_trayicon);
        settings->setValue("voice",sync->advanced.voice);
        settings->endGroup();
    }
    settings->sync();
}
void MainWindow::ReadSettings()
{
    sync=new SYNC;
    settings=new QSettings("D:/HUST-Courses/DS Course Design/Sudoku/config.ini",QSettings::IniFormat);
    settings->setIniCodec(QTextCodec::codecForName("UTF-8"));
    {
        settings->beginGroup("system");
        sync->system.startupstatus=settings->value("startupstatus",0).toInt();
        {
            settings->beginGroup("window");
            sync->system.window.size=settings->value("size", QSize(400, 400)).toSize();
            sync->system.window.pos=settings->value("pos").toPoint();
            resize(sync->system.window.size);
            move(sync->system.window.pos);
            settings->endGroup();
        }
        {
            settings->beginGroup("toolbars");
            sync->system.toolbars[0] = settings->value("game",true).toBool();
            sync->system.toolbars[1] = settings->value("edit",true).toBool();
            sync->system.toolbars[2]=settings->value("function",true).toBool();
            sync->system.toolbars[3]=settings->value("music",true).toBool();
            settings->endGroup();
        }
        settings->endGroup();
    }
    {
        settings->beginGroup("game");
        sync->game.level=settings->value("level",1).toInt();
        sync->game.type=settings->value("type",1).toInt();
        sync->game.candidates=settings->value("candidates",3).toInt();
        sync->game.conflict_tips=settings->value("conflict_tips",true).toBool();
        sync->game.loadlast=settings->value("loadlast",true).toBool();
        sync->game.auto_timing=settings->value("auto_timing",true).toBool();
        sync->game.auto_stop_timing=settings->value("auto_stop_timing",true).toBool();
        sync->game.auto_stop_threshold=settings->value("auto_stop_threshold",true).toInt();
        settings->endGroup();
    }
    {
        settings->beginGroup("view");
        sync->view.font=settings->value("font","宋体").toString();
        sync->view.full_mode=settings->value("full_mode",false).toBool();
        sync->view.simple_mode=settings->value("simple_mode",false).toBool();
        sync->view.statusbar=settings->value("statusbar",true).toBool();
        sync->view.language=settings->value("language",0).toInt();
        sync->view.trayicon=settings->value("trayicon",1).toInt();
        settings->endGroup();
    }
    {
        settings->beginGroup("advanced");
        sync->advanced.closed_prompt_box=settings->value("closed_prompt_box",true).toBool();
        sync->advanced.closed_to_trayicon=settings->value("closed_to_trayicon",true).toBool();
        sync->advanced.voice=settings->value("voice",true).toBool();
        settings->endGroup();
    }
}
void MainWindow::LoadSettings()
{
    if(option!=NULL)
    {
        option->ui->gamelevelbox->setCurrentIndex(sync->game.level);
        option->ui->gametypebox->setCurrentIndex(sync->game.type);
        option->ui->candidatecountbox->setValue(sync->game.candidates);
        option->ui->thresholdbox->setValue(sync->game.auto_stop_threshold);
        option->ui->CheckBox_tips->setChecked(sync->game.conflict_tips);
        option->ui->CheckBox_load->setChecked(sync->game.loadlast);
        option->ui->CheckBox_timing->setChecked(sync->game.auto_timing);
        option->ui->CheckBox_longtime->setChecked(sync->game.auto_stop_timing);
    }
}
