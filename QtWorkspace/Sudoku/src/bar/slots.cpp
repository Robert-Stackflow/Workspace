#include"include/mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::level_changed(bool checked)
{
    QAction *send=qobject_cast<QAction*>(sender());
    int index=0;
    for(int i=0;i<5;i++)
        if(Menus[0].sub[1]->acts[i]==send)
            index=i;
    if(!checked)
        send->setChecked(true);
    else
    {
        Menus[0].sub[1]->acts[sync->game.level]->setChecked(false);
        sync->game.level=index;
        option->ui->gamelevelbox->setCurrentIndex(index);
    }
}
void MainWindow::type_changed(bool checked)
{
    QAction *send=qobject_cast<QAction*>(sender());
    int index=0;
    for(int i=0;i<6;i++)
        if(Menus[0].sub[0]->acts[i]==send)
            index=i;
    if(!checked)
        send->setChecked(true);
    else
    {
        Menus[0].sub[1]->acts[sync->game.type]->setChecked(false);
        sync->game.type=index;
        option->ui->gametypebox->setCurrentIndex(index);
    }
}
void MainWindow::result_triggered()
{
    sudoku->RES().print();
    LoadResult();
}
void MainWindow::play_triggered(bool)
{
    if(Menus[5].acts[0]->isChecked())
    {
        Menus[5].acts[0]->setIcon(QIcon(":/icons/icons/music-suspended.png"));
        Menus[5].acts[0]->setText("暂停播放");
        player->play();
    }
    else if(!Menus[5].acts[0]->isChecked())
    {
        Menus[5].acts[0]->setIcon(QIcon(":/icons/icons/music-play.png"));
        Menus[5].acts[0]->setText("开始播放");
        player->pause();
    }
}
void MainWindow::volume_triggered(bool)
{
    if(Menus[5].acts[1]->isChecked())
    {
        Menus[5].acts[1]->setIcon(QIcon(":/icons/icons/sound-Mute.png"));
        Menus[5].acts[1]->setText("取消静音");
        player->setVolume(0);
    }
    else if(!Menus[5].acts[1]->isChecked())
    {
        Menus[5].acts[1]->setIcon(QIcon(":/icons/icons/sound-filling.png"));
        Menus[5].acts[1]->setText("静音");
        player->setVolume(50);
    }
}
void MainWindow::music_triggered()
{
    music->show();
}
void MainWindow::full_triggered(bool checked)
{
    if(checked)
        this->showFullScreen(),sync->view.full_mode=1;
    else
        this->showNormal(),sync->view.full_mode=0;
}
void MainWindow::simple_triggered(bool checked)
{
    if(checked)
    {
        menuBar->setVisible(false);
        for(int i=0;i<4;i++)
            ToolBars[i]->setVisible(false);
        sync->view.simple_mode=1;
    }
    else
    {
        if(menuBar->isHidden())
            menuBar->setVisible(true);
        for(int i=0;i<4;i++)
            if(Menus[4].sub[2]->acts[i]->isChecked())
                ToolBars[i]->setVisible(true);
        sync->view.simple_mode=0;
    }
}
void MainWindow::color_triggered()
{
    theme->setModal(true);
    theme->ui->tabWidget->setCurrentIndex(0);
    theme->show();
    theme->exec();
}

void MainWindow::update_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Robert-Stackflow/HUST-Courses/releases", QUrl::TolerantMode));
}

void MainWindow::tips_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Robert-Stackflow/HUST-Courses/releases", QUrl::TolerantMode));
}

void MainWindow::help_triggered()
{
    help->setModal(true);
    help->show();
    help->exec();
}

void MainWindow::feedback_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Robert-Stackflow/HUST-Courses/issues", QUrl::TolerantMode));
}

void MainWindow::contact_triggered()
{
    about->setModal(true);
    about->show();
    about->exec();
}

void MainWindow::option_triggered()
{
    option->show();
}

void MainWindow::collection_triggered()
{
    collection->show();
    collection->move((QApplication::desktop()->width()-collection->width())/2,(QApplication::desktop()->height() - collection->height())/2);
}
