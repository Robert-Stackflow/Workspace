#include"include/mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::MyMenuBar()
{
    menuBar=new QMenuBar(this);
    MyGameMenuBar();
    MyEditMenuBar();
    MyOperateMenuBar();
    MyToolMenuBar();
    MyViewMenuBar();
    MyMusicMenuBar();
    MyHelpMenuBar();
    this->setMenuBar(menuBar);
}
void MainWindow::MyGameMenuBar()
{
    Menus[0].main=new QMenu("游戏(&G)");
    Menus[0].main->setStyleSheet(styleSheet);
    Menus[0].sub=new MenuAction*[4];
    Menus[0].acts=new QAction*[6];
    {//The Game Menu subMenu
        Menus[0].sub[0]=new MenuAction;
        Menus[0].sub[0]->main=new QMenu("新游戏产生方式");
        Menus[0].sub[0]->main->setStyleSheet(styleSheet);
        Menus[0].sub[0]->sub=nullptr;
        Menus[0].sub[0]->acts=new QAction*[6];
        Menus[0].sub[0]->acts[0]= new QAction("所有谜题库");
        Menus[0].sub[0]->acts[1]= new QAction("内置谜题");
        Menus[0].sub[0]->acts[2]= new QAction("我的创建");
        Menus[0].sub[0]->acts[3]= new QAction("我的收藏");
        Menus[0].sub[0]->acts[4]= new QAction("外谜题库");
        Menus[0].sub[0]->acts[5]= new QAction("随机生成");
        for(int i=0;i<6;i++)
        {
            Menus[0].sub[0]->acts[i]->setCheckable(true);
            Menus[0].sub[0]->acts[i]->setChecked(false);
            Menus[0].sub[0]->main->addAction(Menus[0].sub[0]->acts[i]);
            connect(Menus[0].sub[0]->acts[i],SIGNAL(triggered(bool)),this,SLOT(type_changed(bool)));
        }
        Menus[0].sub[1]=new MenuAction;
        Menus[0].sub[1]->main=new QMenu("新游戏难度等级");
        Menus[0].sub[1]->main->setStyleSheet(styleSheet);
        Menus[0].sub[1]->sub=nullptr;
        Menus[0].sub[1]->acts=new QAction*[5];
        Menus[0].sub[1]->main->setIcon(QIcon(":/icons/icons/level.png"));
        Menus[0].sub[1]->acts[0]= new QAction("容易");
        Menus[0].sub[1]->acts[1]= new QAction("普通");
        Menus[0].sub[1]->acts[2]= new QAction("困难");
        Menus[0].sub[1]->acts[3]= new QAction("专业");
        Menus[0].sub[1]->acts[4]= new QAction("骨灰");
        for(int i=0;i<5;i++)
        {
            Menus[0].sub[1]->acts[i]->setCheckable(true);
            Menus[0].sub[1]->acts[i]->setChecked(false);
            Menus[0].sub[1]->main->addAction(Menus[0].sub[1]->acts[i]);
            connect(Menus[0].sub[1]->acts[i],SIGNAL(triggered(bool)),this,SLOT(level_changed(bool)));
        }
        Menus[0].sub[1]->acts[sync->game.level]->setChecked(true);

        Menus[0].sub[2]=new MenuAction;
        Menus[0].sub[2]->main=new QMenu("最近尝试的谜题");
        Menus[0].sub[2]->main->setStyleSheet(styleSheet);
        Menus[0].sub[2]->sub=nullptr;
        Menus[0].sub[2]->acts=new QAction*[5];
        Menus[0].sub[2]->acts[0]= new QAction("清空最近尝试的谜题");
        Menus[0].sub[2]->main->addAction(Menus[0].sub[2]->acts[0]);

        Menus[0].sub[3]=new MenuAction;
        Menus[0].sub[3]->main=new QMenu("最近完成的谜题");
        Menus[0].sub[3]->main->setStyleSheet(styleSheet);
        Menus[0].sub[3]->sub=nullptr;
        Menus[0].sub[3]->acts=new QAction*[5];
        Menus[0].sub[3]->acts[0]= new QAction("清空最近完成的谜题");
        Menus[0].sub[3]->main->addAction(Menus[0].sub[3]->acts[0]);
    }
    Menus[0].acts[0] = new QAction("新游戏");
    Menus[0].acts[0]->setStatusTip(tr("以自定义方式开始新游戏"));
    Menus[0].acts[0]->setIcon(QIcon(":/icons/icons/newGame.png"));
    Menus[0].acts[0]->setShortcut(tr("ctrl+N"));
    connect(Menus[0].acts[0],SIGNAL(triggered()),this,SLOT(NewGame()));

    Menus[0].acts[1] = new QAction("打开...(.sud)");
    Menus[0].acts[1]->setStatusTip(tr("打开标准数独文件"));
    Menus[0].acts[1]->setIcon(QIcon(":/icons/icons/file-open.png"));
    Menus[0].acts[1]->setShortcut(tr("ctrl+O"));

    Menus[0].acts[2] = new QAction("另存为...(.sud)");
    Menus[0].acts[2]->setStatusTip(tr("另存为标准数独文件"));
    Menus[0].acts[2]->setIcon(QIcon(":/icons/icons/file-save.png"));
    Menus[0].acts[2]->setShortcut(tr("ctrl+S"));

    Menus[0].acts[3] = new QAction("保存进度");
    Menus[0].acts[3]->setStatusTip(tr("保存当前游戏进度"));

    Menus[0].acts[4] = new QAction("退出游戏");
    Menus[0].acts[4]->setStatusTip(tr("保存当前游戏进度并退出游戏"));
    connect(Menus[0].acts[4],SIGNAL(triggered()),this,SLOT(quit()));

    Menus[0].acts[5] = new QAction("历史记录");
    Menus[0].acts[5]->setStatusTip(tr("查看所有历史记录"));
    Menus[0].acts[5]->setIcon(QIcon(":/icons/icons/history.png"));
    Menus[0].acts[5]->setShortcut(tr("ctrl+H"));

    Menus[0].main->addAction(Menus[0].acts[0]);
    Menus[0].main->addMenu(Menus[0].sub[0]->main);
    Menus[0].main->addMenu(Menus[0].sub[1]->main);
    Menus[0].main->addSeparator();
    Menus[0].main->addAction(Menus[0].acts[1]);
    Menus[0].main->addAction(Menus[0].acts[2]);
    Menus[0].main->addSeparator();
    Menus[0].main->addMenu(Menus[0].sub[2]->main);
    Menus[0].main->addMenu(Menus[0].sub[3]->main);
    Menus[0].main->addSeparator();
    Menus[0].main->addAction(Menus[0].acts[5]);
    Menus[0].main->addSeparator();
    Menus[0].main->addAction(Menus[0].acts[3]);
    Menus[0].main->addAction(Menus[0].acts[4]);
    menuBar->addMenu(Menus[0].main);
}
void MainWindow::MyEditMenuBar()
{
    Menus[1].main=new QMenu("编辑(&E)");
    Menus[1].main->setShortcutEnabled(true);
    Menus[1].main->setStyleSheet(styleSheet);
    Menus[1].sub=nullptr;
    Menus[1].acts=new QAction*[7];

    Menus[1].acts[0] = new QAction("撤销");
    Menus[1].acts[0]->setStatusTip(tr("撤销最近一步操作"));
    Menus[1].acts[0]->setIcon(QIcon(":/icons/icons/undo.png"));
    connect(Menus[1].acts[0],SIGNAL(triggered()),this,SLOT(undo()));
    Menus[1].acts[0]->setShortcut(tr("ctrl+Z"));

    Menus[1].acts[1] = new QAction("重做");
    Menus[1].acts[1]->setStatusTip(tr("重做最近一步操作"));
    Menus[1].acts[1]->setIcon(QIcon(":/icons/icons/redo.png"));
    connect(Menus[1].acts[1],SIGNAL(triggered()),this,SLOT(redo()));
    Menus[1].acts[1]->setShortcut(tr("ctrl+Y"));

    Menus[1].acts[2] = new QAction("撤销全部");
    Menus[1].acts[2]->setShortcut(tr("shift+Z"));

    Menus[1].acts[3] = new QAction("重做全部");
    Menus[1].acts[3]->setShortcut(tr("shift+Y"));

    Menus[1].acts[4] = new QAction("清除全部错误");
    Menus[1].acts[4]->setStatusTip(tr("清除当前游戏中的全部冲突"));
    Menus[1].acts[4]->setIcon(QIcon(":/icons/icons/clear.png"));
    connect(Menus[1].acts[4],SIGNAL(triggered()),this,SLOT(ClearConflict()));

    Menus[1].acts[5] = new QAction("复制谜题");
    Menus[1].acts[5]->setStatusTip(tr("以选择的复制方式复制谜题到剪切板"));
    Menus[1].acts[5]->setIcon(QIcon(":/icons/icons/copy.png"));
    connect(Menus[1].acts[5],SIGNAL(triggered()),this,SLOT(copy()));
    Menus[1].acts[5]->setShortcut(tr("ctrl+C"));

    Menus[1].acts[6] = new QAction("粘贴谜题");
    Menus[1].acts[6]->setStatusTip(tr("从剪切板读取并解析谜题"));
    Menus[1].acts[6]->setIcon(QIcon(":/icons/icons/paste.png"));
    connect(Menus[1].acts[6],SIGNAL(triggered()),this,SLOT(paste()));
    Menus[1].acts[6]->setShortcut(tr("ctrl+V"));

    Menus[1].main->addAction(Menus[1].acts[0]);
    Menus[1].main->addAction(Menus[1].acts[1]);
    Menus[1].main->addSeparator();
    Menus[1].main->addAction(Menus[1].acts[2]);
    Menus[1].main->addAction(Menus[1].acts[3]);
    Menus[1].main->addAction(Menus[1].acts[4]);
    Menus[1].main->addSeparator();
    Menus[1].main->addAction(Menus[1].acts[5]);
    Menus[1].main->addAction(Menus[1].acts[6]);
    menuBar->addMenu(Menus[1].main);
}
void MainWindow::MyOperateMenuBar()
{
    Menus[2].main=new QMenu("操作(&O)");
    Menus[2].main->setStyleSheet(styleSheet);
    Menus[2].sub=nullptr;
    Menus[2].acts=new QAction*[5];

    Menus[2].acts[0] = new QAction("提示");
    Menus[2].acts[0]->setStatusTip(tr("提示随机位置处的数字"));
    Menus[2].acts[0]->setIcon(QIcon(":/icons/icons/tip.png"));
    Menus[2].acts[0]->setShortcut(tr("ctrl+T"));

    Menus[2].acts[1] = new QAction("重新开始");
    Menus[2].acts[1]->setStatusTip(tr("清空历史操作，重新开始游戏"));
    Menus[2].acts[1]->setIcon(QIcon(":/icons/icons/regame.png"));
    connect(Menus[2].acts[1],SIGNAL(triggered()),this,SLOT(Restart()));
    Menus[2].acts[1]->setShortcut(tr("ctrl+R"));

    Menus[2].acts[2] = new QAction("显示结果");
    Menus[2].acts[2]->setIcon(QIcon(":/icons/icons/result.png"));
    connect(Menus[2].acts[2],SIGNAL(triggered()),this,SLOT(LoadResult()));

    Menus[2].acts[3] = new QAction("开始计时");
    Menus[2].acts[3]->setIcon(QIcon(":/icons/icons/time-start.png"));
    Menus[2].acts[3]->setCheckable(true);
    Menus[2].acts[3]->setChecked(false);
    connect(Menus[2].acts[3],SIGNAL(toggled(bool)),this,SLOT(timerstart(bool)));

    Menus[2].acts[4] = new QAction("结束计时");
    Menus[2].acts[4]->setIcon(QIcon(":/icons/icons/time-reset.png"));
    connect(Menus[2].acts[4],SIGNAL(triggered()),this,SLOT(timerreset()));

    Menus[2].main->addAction(Menus[2].acts[0]);
    Menus[2].main->addAction(Menus[2].acts[1]);
    Menus[2].main->addAction(Menus[2].acts[2]);
    Menus[2].main->addSeparator();
    Menus[2].main->addAction(Menus[2].acts[3]);
    Menus[2].main->addAction(Menus[2].acts[4]);
    menuBar->addMenu(Menus[2].main);
}
void MainWindow::MyToolMenuBar()
{
    Menus[3].main=new QMenu("工具(&T)");
    Menus[3].main->setStyleSheet(styleSheet);
    Menus[3].sub=new MenuAction*[2];
    Menus[3].acts=new QAction*[8];
    {//The Tool Menu subMenu
        Menus[3].sub[0]=new MenuAction;
        Menus[3].sub[0]->main=new QMenu("选择备份内容");
        Menus[3].sub[0]->main->setStyleSheet(styleSheet);
        Menus[3].sub[0]->sub=nullptr;
        Menus[3].sub[0]->acts=new QAction*[6];
        Menus[3].sub[0]->acts[0]= new QAction("所有设置");
        Menus[3].sub[0]->acts[1]= new QAction("我的收藏");
        Menus[3].sub[0]->acts[2]= new QAction("历史记录");
        Menus[3].sub[0]->acts[3]= new QAction("我的谜题");
        Menus[3].sub[0]->acts[4]= new QAction("我的主题");
        Menus[3].sub[0]->acts[5]= new QAction("我的背景");
        for(int i=0;i<6;i++)
            Menus[3].sub[0]->acts[i]->setCheckable(true);
        for(int i=0;i<6;i++)
            Menus[3].sub[0]->acts[i]->setChecked(true);
        for(int i=0;i<6;i++)
            Menus[3].sub[0]->main->addAction(Menus[3].sub[0]->acts[i]);

        Menus[3].sub[1]=new MenuAction;
        Menus[3].sub[1]->main=new QMenu("恢复备份");
        Menus[3].sub[1]->main->setStyleSheet(styleSheet);
        Menus[3].sub[1]->sub=nullptr;
        Menus[3].sub[1]->acts=new QAction*[5];
        Menus[3].sub[1]->acts[0]= new QAction("浏览文件…");
        Menus[3].sub[1]->main->addAction(Menus[3].sub[1]->acts[0]);
    }
    Menus[3].acts[0] = new QAction("查找谜题");
    Menus[3].acts[0]->setIcon(QIcon(":/icons/icons/search.png"));
    Menus[3].acts[0]->setShortcut(tr("ctrl+F"));

    Menus[3].acts[1] = new QAction("创建谜题");
    Menus[3].acts[1]->setIcon(QIcon(":/icons/icons/create.png"));
    Menus[3].acts[1]->setShortcut(tr("ctrl+shift+N"));

    Menus[3].acts[2] = new QAction("我的谜题");
    Menus[3].acts[2]->setIcon(QIcon(":/icons/icons/myproblem.png"));
    connect(Menus[3].acts[2],SIGNAL(triggered()),this,SLOT(collection_triggered()));

    Menus[3].acts[3] = new QAction("收藏谜题");
    Menus[3].acts[3]->setShortcut(tr("ctrl+D"));
    Menus[3].acts[3]->setIcon(QIcon(":/icons/icons/collection.png"));

    Menus[3].acts[4] = new QAction("我的收藏");
    Menus[3].acts[4]->setIcon(QIcon(":/icons/icons/all.png"));

    Menus[3].acts[5] = new QAction("语音提示");
    Menus[3].acts[5]->setIcon(QIcon(":/icons/icons/voice.png"));
    Menus[3].acts[5]->setCheckable(true);

    Menus[3].acts[6] = new QAction("备份数据");

    Menus[3].acts[7] = new QAction("选项");
    Menus[3].acts[7]->setIcon(QIcon(":/icons/icons/option.png"));
    Menus[3].acts[7]->setShortcut(tr("ctrl+P"));
    connect(Menus[3].acts[7],SIGNAL(triggered()),this,SLOT(option_triggered()));

    Menus[3].main->addAction(Menus[3].acts[0]);
    Menus[3].main->addAction(Menus[3].acts[1]);
    Menus[3].main->addAction(Menus[3].acts[2]);
    Menus[3].main->addSeparator();
    Menus[3].main->addAction(Menus[3].acts[3]);
    Menus[3].main->addAction(Menus[3].acts[4]);
    Menus[3].main->addSeparator();
    Menus[3].main->addAction(Menus[3].acts[5]);
    Menus[3].main->addSeparator();
    Menus[3].main->addAction(Menus[3].acts[6]);
    Menus[3].main->addMenu(Menus[3].sub[0]->main);
    Menus[3].main->addMenu(Menus[3].sub[1]->main);
    Menus[3].main->addSeparator();
    Menus[3].main->addAction(Menus[3].acts[7]);
    menuBar->addMenu(Menus[3].main);
}
void MainWindow::MyViewMenuBar()
{
    Menus[4].main=new QMenu("视图(&V)");
    Menus[4].main->setStyleSheet(styleSheet);
    Menus[4].sub=new MenuAction*[5];
    Menus[4].acts=new QAction*[4];
    {//The View Menu subMenu
        Menus[4].sub[0]=new MenuAction;
        Menus[4].sub[0]->main=new QMenu("预置主题");
        Menus[4].sub[0]->main->setStyleSheet(styleSheet);
        Menus[4].sub[0]->main->setIcon(QIcon(":/icons/icons/background.png"));
        Menus[4].sub[0]->sub=nullptr;
        Menus[4].sub[0]->acts=new QAction*[8];
        Menus[4].sub[0]->acts[0]= new QAction("极简白");
        Menus[4].sub[0]->acts[1]= new QAction("酷炫黑");
        Menus[4].sub[0]->acts[2]= new QAction("经典蓝");
        Menus[4].sub[0]->acts[3]= new QAction("少女粉");
        for(int i=0;i<4;i++)
            Menus[4].sub[0]->acts[i]->setCheckable(true);
        for(int i=0;i<4;i++)
            Menus[4].sub[0]->main->addAction(Menus[4].sub[0]->acts[i]);

        Menus[4].sub[1]=new MenuAction;
        Menus[4].sub[1]->main=new QMenu("我的主题");
        Menus[4].sub[1]->main->setStyleSheet(styleSheet);
        Menus[4].sub[1]->main->setIcon(QIcon(":/icons/icons/background.png"));
        Menus[4].sub[1]->sub=nullptr;
        Menus[4].sub[1]->acts=new QAction*[4];
        Menus[4].sub[1]->acts[0]= new QAction("极简白");
        Menus[4].sub[1]->acts[1]= new QAction("酷炫黑");
        Menus[4].sub[1]->acts[2]= new QAction("经典蓝");
        Menus[4].sub[1]->acts[3]= new QAction("少女粉");
        for(int i=0;i<4;i++)
            Menus[4].sub[1]->acts[i]->setCheckable(true);
        for(int i=0;i<4;i++)
            Menus[4].sub[1]->main->addAction(Menus[4].sub[1]->acts[i]);

        Menus[4].sub[2]=new MenuAction;
        Menus[4].sub[2]->main=new QMenu("工具栏");
        Menus[4].sub[2]->main->setStyleSheet(styleSheet);
        Menus[4].sub[2]->sub=nullptr;
        Menus[4].sub[2]->acts=new QAction*[6];
        Menus[4].sub[2]->acts[0]= new QAction("游戏栏");
        Menus[4].sub[2]->acts[1]= new QAction("操作栏");
        Menus[4].sub[2]->acts[2]= new QAction("功能栏");
        Menus[4].sub[2]->acts[3]= new QAction("音乐栏");
        Menus[4].sub[2]->acts[4]= new QAction("全部显示");
        Menus[4].sub[2]->acts[5]= new QAction("全部隐藏");
        for(int i=0;i<4;i++)
        {
            Menus[4].sub[2]->acts[i]->setCheckable(true);
            Menus[4].sub[2]->acts[i]->setChecked(!sync->system.toolbars[i]);
        }
        connect(Menus[4].sub[2]->acts[0],SIGNAL(toggled(bool)),this,SLOT(toolbar_1_toggled()));
        connect(Menus[4].sub[2]->acts[1],SIGNAL(toggled(bool)),this,SLOT(toolbar_2_toggled()));
        connect(Menus[4].sub[2]->acts[2],SIGNAL(toggled(bool)),this,SLOT(toolbar_3_toggled()));
        connect(Menus[4].sub[2]->acts[3],SIGNAL(toggled(bool)),this,SLOT(toolbar_4_toggled()));
        connect(Menus[4].sub[2]->acts[4],SIGNAL(triggered()),this,SLOT(toolbardisplay_triggered()));
        connect(Menus[4].sub[2]->acts[5],SIGNAL(triggered()),this,SLOT(toolbarhide_triggered()));
        Menus[4].sub[2]->main->addAction(Menus[4].sub[2]->acts[4]);
        Menus[4].sub[2]->main->addAction(Menus[4].sub[2]->acts[5]);
        Menus[4].sub[2]->main->addSeparator();
        for(int i=0;i<4;i++)
            Menus[4].sub[2]->main->addAction(Menus[4].sub[2]->acts[i]);

        Menus[4].sub[3]=new MenuAction;
        Menus[4].sub[3]->main=new QMenu("托盘图标");
        Menus[4].sub[3]->main->setStyleSheet(styleSheet);
        Menus[4].sub[3]->acts=new QAction*[3];
        Menus[4].sub[3]->acts[0]= new QAction("不显示");
        Menus[4].sub[3]->acts[1]= new QAction("浅色图标");
        Menus[4].sub[3]->acts[2]= new QAction("深色图标");
        for(int i=0;i<3;i++)
        {
            Menus[4].sub[3]->main->addAction(Menus[4].sub[3]->acts[i]);
            Menus[4].sub[3]->acts[i]->setCheckable(true);
        }
        connect(Menus[4].sub[3]->acts[0],SIGNAL(triggered()),this,SLOT(trayiconhide_triggered()));
        connect(Menus[4].sub[3]->acts[1],SIGNAL(triggered()),this,SLOT(trayiconlight_triggered()));
        connect(Menus[4].sub[3]->acts[2],SIGNAL(triggered()),this,SLOT(trayiconnight_triggered()));
        Menus[4].sub[4]=new MenuAction;
        Menus[4].sub[4]->main=new QMenu("语言");
        Menus[4].sub[4]->main->setStyleSheet(styleSheet);
        Menus[4].sub[4]->sub=nullptr;
        Menus[4].sub[4]->acts=new QAction*[3];
        Menus[4].sub[4]->acts[0]= new QAction("简体中文");
        Menus[4].sub[4]->acts[1]= new QAction("繁体中文");
        Menus[4].sub[4]->acts[2]= new QAction("English");
        for(int i=0;i<3;i++)
            Menus[4].sub[4]->acts[i]->setCheckable(true);
        for(int i=0;i<3;i++)
            Menus[4].sub[4]->main->addAction(Menus[4].sub[4]->acts[i]);
        Menus[4].sub[4]->acts[0]->setChecked(true);
    }
    Menus[4].acts[0] = new QAction("全屏模式");
    Menus[4].acts[0]->setShortcut(tr("F11"));
    Menus[4].acts[0]->setCheckable(true);
    Menus[4].acts[0]->setChecked(!sync->view.full_mode);
    connect(Menus[4].acts[0],SIGNAL(toggled(bool)),this,SLOT(full_triggered(bool)));
    Menus[4].acts[0]->setChecked(sync->view.full_mode);

    Menus[4].acts[1]= new QAction("简洁模式");
    Menus[4].acts[1]->setShortcut(tr("F12"));
    Menus[4].acts[1]->setCheckable(true);
    Menus[4].acts[1]->setChecked(!sync->view.simple_mode);
    connect(Menus[4].acts[1],SIGNAL(toggled(bool)),this,SLOT(simple_triggered(bool)));

    Menus[4].acts[2] = new QAction("配色方案");
    Menus[4].acts[2]->setIcon(QIcon(":/icons/icons/color.png"));
    connect(Menus[4].acts[2],SIGNAL(triggered()),this,SLOT(color_triggered()));

    Menus[4].acts[3] = new QAction("状态栏");
    Menus[4].acts[3]->setCheckable(true);
    Menus[4].acts[3]->setChecked(!sync->view.statusbar);
    ui->statusBar->setVisible(sync->view.statusbar);
    //    qDebug()<<sync->view.statusbar<<Menus[4].acts[2]->isChecked()<<ui->statusBar->isHidden();
    connect(Menus[4].acts[3],SIGNAL(toggled(bool)),this,SLOT(statusbarvisible_triggered()));
    Menus[4].acts[3]->setChecked(sync->view.statusbar);
    //    qDebug()<<sync->view.statusbar<<Menus[4].acts[2]->isChecked()<<ui->statusBar->isHidden();

    Menus[4].main->addAction(Menus[4].acts[0]);
    Menus[4].main->addAction(Menus[4].acts[1]);
    Menus[4].main->addAction(Menus[4].acts[2]);
    Menus[4].main->addMenu(Menus[4].sub[0]->main);
    Menus[4].main->addMenu(Menus[4].sub[1]->main);
    Menus[4].main->addSeparator();
    Menus[4].main->addAction(Menus[4].acts[3]);
    Menus[4].main->addMenu(Menus[4].sub[2]->main);
    Menus[4].main->addMenu(Menus[4].sub[3]->main);
    Menus[4].main->addSeparator();
    Menus[4].main->addMenu(Menus[4].sub[4]->main);
    menuBar->addMenu(Menus[4].main);
}
void MainWindow::MyMusicMenuBar()
{
    Menus[5].main=new QMenu("音乐(&M)");
    Menus[5].main->setStyleSheet(styleSheet);
    Menus[5].sub=new MenuAction*[2];
    Menus[5].acts=new QAction*[5];
    {//The Music Menu subMenu
        Menus[5].sub[0]=new MenuAction;
        Menus[5].sub[0]->main=new QMenu("播放模式");
        Menus[5].sub[0]->main->setStyleSheet(styleSheet);
        Menus[5].sub[0]->sub=nullptr;
        Menus[5].sub[0]->acts=new QAction*[2];
        Menus[5].sub[0]->acts[0]= new QAction("单曲循环");
        Menus[5].sub[0]->acts[1]= new QAction("列表循环");
        for(int i=0;i<2;i++)
            Menus[5].sub[0]->acts[i]->setCheckable(true);
        for(int i=0;i<2;i++)
            Menus[5].sub[0]->main->addAction(Menus[5].sub[0]->acts[i]);

        Menus[5].sub[1]=new MenuAction;
        Menus[5].sub[1]->main=new QMenu("播放条");
        Menus[5].sub[1]->main->setStyleSheet(styleSheet);
        Menus[5].sub[1]->sub=nullptr;
        Menus[5].sub[1]->acts=new QAction*[3];
        Menus[5].sub[1]->acts[0]= new QAction("不显示");
        Menus[5].sub[1]->acts[1]= new QAction("数独上方");
        Menus[5].sub[1]->acts[2]= new QAction("数独下方");
        for(int i=0;i<3;i++)
            Menus[5].sub[1]->acts[i]->setCheckable(true);
        for(int i=0;i<3;i++)
            Menus[5].sub[1]->main->addAction(Menus[5].sub[1]->acts[i]);
    }
    Menus[5].acts[0] = new QAction("开始播放");
    Menus[5].acts[0]->setCheckable(true);
    Menus[5].acts[0]->setChecked(false);
    Menus[5].acts[0]->setIcon(QIcon(":/icons/icons/music-play.png"));
    connect(Menus[5].acts[0],SIGNAL(toggled(bool)),this,SLOT(play_triggered(bool)));

    Menus[5].acts[1] = new QAction("静音");
    Menus[5].acts[1]->setCheckable(true);
    Menus[5].acts[1]->setChecked(false);
    Menus[5].acts[1]->setIcon(QIcon(":/icons/icons/sound-filling.png"));
    connect(Menus[5].acts[1],SIGNAL(toggled(bool)),this,SLOT(volume_triggered(bool)));

    Menus[5].acts[2] = new QAction("上一首");
    Menus[5].acts[2]->setIcon(QIcon(":/icons/icons/music-pre.png"));

    Menus[5].acts[3] = new QAction("下一首");
    Menus[5].acts[3]->setIcon(QIcon(":/icons/icons/music-next.png"));

    Menus[5].acts[4] = new QAction("所有音乐");
    connect(Menus[5].acts[4],SIGNAL(triggered()),this,SLOT(music_triggered()));
    Menus[5].main->addAction(Menus[5].acts[0]);
    Menus[5].main->addAction(Menus[5].acts[1]);
    Menus[5].main->addAction(Menus[5].acts[2]);
    Menus[5].main->addAction(Menus[5].acts[3]);
    Menus[5].main->addAction(Menus[5].acts[4]);
    Menus[5].main->addSeparator();
    Menus[5].main->addMenu(Menus[5].sub[0]->main);
    Menus[5].main->addMenu(Menus[5].sub[1]->main);
    menuBar->addMenu(Menus[5].main);
}
void MainWindow::MyHelpMenuBar()
{
    Menus[6].main=new QMenu("帮助(&H)");
    Menus[6].main->setStyleSheet(styleSheet);
    Menus[6].sub=nullptr;
    Menus[6].acts=new QAction*[5];

    Menus[6].acts[0] = new QAction("使用帮助");
    Menus[6].acts[0]->setShortcut(tr("F1"));
    Menus[6].acts[0]->setIcon(QIcon(":/icons/icons/help.png"));

    Menus[6].acts[1] = new QAction("数独技巧");
    Menus[6].acts[1]->setIcon(QIcon(":/icons/icons/tips.png"));

    Menus[6].acts[2] = new QAction("反馈与建议");
    Menus[6].acts[2]->setIcon(QIcon(":/icons/icons/feedback.png"));

    Menus[6].acts[3] = new QAction("检查更新");
    Menus[6].acts[3]->setIcon(QIcon(":/icons/icons/update.png"));

    Menus[6].acts[4] = new QAction("关于");
    Menus[6].acts[4]->setIcon(QIcon(":/icons/icons/copyright.png"));

    connect(Menus[6].acts[0],SIGNAL(triggered()),this,SLOT(help_triggered()));
    connect(Menus[6].acts[1],SIGNAL(triggered()),this,SLOT(tips_triggered()));
    connect(Menus[6].acts[2],SIGNAL(triggered()),this,SLOT(feedback_triggered()));
    connect(Menus[6].acts[3],SIGNAL(triggered()),this,SLOT(update_triggered()));
    connect(Menus[6].acts[4],SIGNAL(triggered()),this,SLOT(contact_triggered()));

    Menus[6].main->addAction(Menus[6].acts[0]);
    Menus[6].main->addAction(Menus[6].acts[1]);
    Menus[6].main->addSeparator();
    Menus[6].main->addAction(Menus[6].acts[2]);
    Menus[6].main->addAction(Menus[6].acts[3]);
    Menus[6].main->addAction(Menus[6].acts[4]);
    menuBar->addMenu(Menus[6].main);
}
