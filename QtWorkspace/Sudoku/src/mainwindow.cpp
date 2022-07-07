#include "include/mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Initial();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Initial()
{
    setWindowTitle("Sudoku");
    //    this->setMouseTracking(true);
    //Generate My Objective
    ReadSettings();
    MyQSS();
    MyMenuBar();
    MyToolBar();
    MyTrayIcon();
    MyStatusBar();
    MyTimer();
    MyTTS();
    MyPlate();
    MyPlayer();
    WriteSettings();
    //Generate Subwindows
    theme=new Theme(this);
    option=new Option(this);
    help=new HelpDialog(this);
    about=new AboutDialog(this);
    collection=new Library(this);
    music=new musicdialog(this);
    LoadSettings();
    music->loadUserFile();
}
void MainWindow::MyTTS()
{
    tts=new QTextToSpeech(this);
    tts->say("Welcome to Sudoku!");
}
void MainWindow::MyPlayer()
{
    player=new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(QString::fromLocal8Bit("D:/test.wav")));
    player->setVolume(50);//音量
}
void MainWindow::MyQSS()
{
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString temp = this->styleSheet;
        temp+= QLatin1String(file.readAll());
        this->styleSheet=temp;
        this->setStyleSheet(styleSheet);
        file.close();
    }
}
QString MainWindow::FoundCertainButton(int type,int x,int y)
{
    //type=0 左
    //type=1 右
    //type=2 上
    //type=3 下
    int nx=x,ny=y;
    switch(type)
    {
    case 0:
        while((!(x==0&&y==0))&&plate[x][y]->isEnabled()==false)
        {
            if(y>0)
                y--;
            else if(y==0&&x!=0)
                x--,y=8;
        }
        break;
    case 1:
        qDebug()<<"right";
        while((!(x==8&&y==8))&&plate[x][y]->isEnabled()==false)
        {
            if(y<9)
                y++;
            else if(y==8&&x!=8)
                x++,y=0;
        }
        break;
    case 2:
        while(plate[x][y]->isEnabled()==false)
        {
            x=(x+1)%9;
        }
        break;
    case 3:
        while(plate[x][y]->isEnabled()==false)
        {
            x=(x-1+9)%9;
        }
        break;
    }
    qDebug()<<QString::asprintf("%d%d",nx,ny);
    return QString::asprintf("%d%d",nx,ny);
}
void MainWindow::keyPressEvent(QKeyEvent * event)
{
    QWidget *focus=QApplication::focusWidget();
    QPushButton *click=nullptr;
    int x=0,y=0,flag=0;
    switch (event->key())
    {
    case Qt::Key_Left:
        click=(QPushButton* )focus;
        if(click!=nullptr)
            qDebug()<<click->objectName()<<x<<y<<"right";
        else
            qDebug()<<"NULL";
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                if(click!=nullptr&&plate[i][j]->objectName()==click->objectName())
                    x=i,y=j,flag=1;
        if(flag)
        {
            QString result=FoundCertainButton(0,x,y);
            x=result.toInt()/10;
            y=result.toInt()%10;
            qDebug()<<x<<y<<"right";
            fill(x,y);
        }
        break;
    case Qt::Key_Right:
        click=(QPushButton* )focus;
        if(click!=nullptr)
            qDebug()<<click->objectName()<<x<<y<<"right";
        else
            qDebug()<<"NULL";
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                if(click!=nullptr&&plate[i][j]->objectName()==click->objectName())
                    x=i,y=j,flag=1;
        if(flag)
        {
            QString result=FoundCertainButton(1,x,y);
            x=result.toInt()/10;
            y=result.toInt()%10;
            qDebug()<<x<<y<<"right";
            fill(x,y);
        }
        break;
    case Qt::Key_Up:
        click=(QPushButton* )focus;
        if(click!=nullptr)
            qDebug()<<click->objectName()<<x<<y<<"right";
        else
            qDebug()<<"NULL";
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                if(click!=nullptr&&plate[i][j]->objectName()==click->objectName())
                    x=i,y=j,flag=1;
        if(flag)
        {
            QString result=FoundCertainButton(2,x,y);
            x=result.toInt()/10;
            y=result.toInt()%10;
            qDebug()<<x<<y<<"right";
            fill(x,y);
        }
        break;
    case Qt::Key_Down:
        click=(QPushButton* )focus;
        if(click!=nullptr)
            qDebug()<<click->objectName()<<x<<y<<"right";
        else
            qDebug()<<"NULL";
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                if(click!=nullptr&&plate[i][j]->objectName()==click->objectName())
                    x=i,y=j,flag=1;
        if(flag)
        {
            QString result=FoundCertainButton(3,x,y);
            x=result.toInt()/10;
            y=result.toInt()%10;
            qDebug()<<x<<y<<"right";
            fill(x,y);
        }
        break;
    case Qt::Key_Escape:
        if(sync->view.simple_mode)
        {
            menuBar->setVisible(true);
            Menus[4].acts[1]->setChecked(false);
        }
        else
            Menus[4].acts[0]->setChecked(false);
        break;
    case Qt::Key_F12:
        if(sync->view.simple_mode)
        {
            menuBar->setVisible(true);
            Menus[4].acts[1]->setChecked(false);
        }
        break;
    case Qt::Key_F11:
        if(menuBar->isHidden())
        {
            menuBar->setVisible(true);
            Menus[4].acts[0]->setChecked(!Menus[4].acts[0]->isChecked());
            menuBar->setVisible(false);
        }
        break;
    case Qt::Key_0:
    case Qt::Key_Backspace:
        ((QPushButton* )focus)->setText(QString(""));
        break;
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        QWidget *focus=QApplication::focusWidget();
        int x,y;
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                if(plate[i][j]==((QPushButton*)focus))
                {
                    x=i,y=j;
                    if(sudoku->cur.m[x][y]!=event->key()-48)
                        sudoku->history[sudoku->COUNT()-1].add(x,y,sudoku->cur.m[x][y],event->key()-48);
                    sudoku->history->print();
                    sudoku->cur.m[x][y]=event->key()-48;
                    ((QPushButton*)focus)->setText(QString::number(sudoku->cur.m[x][y]));
                    conflict(x,y,sudoku->cur.m[x][y]);
                    TestResult();
                }
        break;
    }

}
//void MainWindow::mouseMoveEvent(QMouseEvent *e)
//{
//    //        for(int i=0;i<9;i++)
//    //            for(int j=0;j<9;j++)
//    //                if(plate[i][j]->geometry().contains(this->mapFromGlobal(QCursor::pos())))
//    //                        fill(i,j);
//}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"enter";
    QPoint point=this->mapFromGlobal(QCursor::pos());
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(plate[i][j]->geometry().contains(point))
            {
                if(event->button()==Qt::LeftButton)
                    fill(i,j);
            }
        }
    }
}
