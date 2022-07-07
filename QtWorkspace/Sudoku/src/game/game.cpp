#include "include/mainwindow.h"
#include "ui_mainwindow.h"
int times=0;
void MainWindow::MyTimer()
{
    Timer=new QTimer;
    TimerBoard=new QLCDNumber(this);
    TimerRecord=new QTime(0,0,0,0);
    TimerBoard->setDigitCount(8);
    TimerBoard->setSegmentStyle(QLCDNumber::Flat);
    TimerBoard->display(TimerRecord->toString("hh:mm:ss"));
    TimerBoard->setGeometry(500,100,200,200);
    TimerBoard->show();
    timerreset();
}
void MainWindow::MyPlate()
{
    for(int i=0;i<9;i++)
    {
        int x=80,y=120;
        if(i>0)
            x=coor[i-1][0].geometry().x()+41,y=coor[i-1][1].geometry().y()+41;
        if(i%3==0&&i!=0)
            x+=3,y+=3;
        coor[i][0].setGeometry(x,80,40,40);
        coor[i][1].setGeometry(40,y,40,40);
        coor[i][0].setText(QString::asprintf("%d",i+1));
        coor[i][1].setText(QString::asprintf("%c",'A'+i));
        coor[i][0].setParent(this);
        coor[i][1].setParent(this);
        coor[i][0].show();
        coor[i][1].show();
        coor[i][0].setAlignment(Qt::AlignCenter);
        coor[i][0].setAlignment(Qt::AlignCenter);
    }
    plate=new QPushButton**[9];
    for(int i=0;i<9;++i)
    {
        plate[i]=new QPushButton*[9];
        for(int j=0;j<9;++j)
        {
            plate[i][j]=new QPushButton(this);
            int x=80,y=120;
            if(j>0)
                x=plate[i][j-1]->geometry().x()+41;
            if(j%3==0&&j!=0)
                x+=3;
            if(i>0)
                y=plate[i-1][j]->geometry().y()+41;
            if(i%3==0&&i!=0)
                y+=3;
            plate[i][j]->show();
            plate[i][j]->setGeometry(x,y,40,40);
            plate[i][j]->setObjectName(QString::number(i*9+j));
            plate[i][j]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            plate[i][j]->installEventFilter(this);
            plate[i][j]->setAccessibleName(QString::number(i*9+j));
            connect(plate[i][j],SIGNAL(pressed()),this,SLOT(fill()));
            plate[i][j]->setFont(QFont("宋体", 12));
            plate[i][j]->setStyleSheet("background-color:#455364;border-radius:0px;border:1px groove black");//default stylesheet;
            plate[i][j]->setText(QString(""));
            plate[i][j]->setFlat(true);
            plate[i][j]->setAutoFillBackground(true);
            plate[i][j]->setDisabled(true);
            plate[i][j]->setFocusPolicy(Qt::StrongFocus);
            //            plate[i][j]->setMouseTracking(true);
        }
    }
}
void MainWindow::NewGame()
{
    sudoku=new SUDOKU(sync->game.type,sync->game.level);
    sudoku->PROB().print();
    sudoku->RES().print();
    LoadPuzzle();
    sudoku->AddHistory();
    timerreset();
    if(sync->game.auto_timing)
        Menus[2].acts[3]->setChecked(true);
}
void MainWindow::AddtoDB()
{
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
    data.setDatabaseName("default");
}
void MainWindow::Restart()
{
    LoadPuzzle();
    timerreset();
    if(sync->game.auto_timing)
        Menus[2].acts[3]->setChecked(true);
}
void MainWindow::LoadPuzzle()
{
    QPushButton *firstSpace=nullptr;
    int firstx,firsty;
    //重置谜题盘样式和内容
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            plate[i][j]->setText(QString(""));
            plate[i][j]->setStyleSheet("background-color:#455364;border-radius:0px;border:1px groove black");
            plate[i][j]->setEnabled(false);
        }
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(sudoku->PROB().m[i][j]!=0)
            {
                if(firstSpace==nullptr)
                    firstx=i,firsty=j,firstSpace=plate[i][j];
                plate[i][j]->setText(QString::asprintf("%d",sudoku->PROB().m[i][j]));
            }
            else
                plate[i][j]->setEnabled(true);
        }
    }
    if(firstSpace!=nullptr)
    {
        firstSpace->setFocus();
        qDebug()<<firstx<<firsty;
    }
}
void MainWindow::LoadResult()
{
    if(sudoku!=NULL)
    {
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                plate[i][j]->setText(QString(""));
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                plate[i][j]->setText(QString::asprintf("%d",sudoku->RES().m[i][j])),plate[i][j]->setEnabled(false);
        Menus[2].acts[3]->setChecked(false);
        timerstart(0);
    }
}
void MainWindow::TestResult()
{
    int flag=1;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(plate[i][j]->text()!=QString::asprintf("%d",sudoku->RES().m[i][j]))
                flag=0;
    if(flag)
    {
        qDebug("Success!");
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                plate[i][j]->setEnabled(false);
        Menus[2].acts[3]->setChecked(false);
        timerstart(0);
    }
}
void MainWindow::fill()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(!sudoku->clash.m[i][j])
                plate[i][j]->setStyleSheet("background-color:#455364;border-radius:0px;border:1px groove black");
        }
    }
    QObject* click=sender();
    int x=0,y=0;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(plate[i][j]->objectName()==click->objectName())
                x=i,y=j;
    qDebug("(%c,%d)",x+'A',y+1);
    plate[x][y]->setFocus();
    plate[x][y]->setStyleSheet("background-color:green");
}
void MainWindow::fill(int i,int j)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(!sudoku->clash.m[i][j])
                plate[i][j]->setStyleSheet("background-color:#455364;border-radius:0px;border:1px groove black");
        }
    }
    int x=i,y=j;
    qDebug("(%c,%d)",x+'A',y+1);
    plate[x][y]->setFocus();
    plate[x][y]->setStyleSheet("background-color:green");
}
void MainWindow::conflict(int x,int y,int num)
{
    bool flag=check(sudoku->cur.m,x,y,num);
    if(!flag&&sync->game.conflict_tips)
    {
        sudoku->clash.m[x][y]=1;
        plate[x][y]->setStyleSheet("color:red;border-radius:0px;border:1px groove black");
    }
    else
    {
        sudoku->clash.m[x][y]=0;
        plate[x][y]->setStyleSheet("background-color:#455364;border-radius:0px;border:1px groove black");
    }
}
void MainWindow::ClearConflict()
{
    if(sudoku!=NULL)
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                if(sudoku->clash.m[i][j])
                {
                    sudoku->clash.m[i][j]=0;
                    plate[i][j]->setText(QString(""));
                    plate[i][j]->setStyleSheet("background-color:#455364;border-radius:0px;border:1px groove black");
                }
}
void MainWindow::copy()
{
    QClipboard *clip = QApplication::clipboard();
    clip->setText(sudoku->PROB().print());
}
void MainWindow::paste()
{
    QClipboard *clip = QApplication::clipboard();
    QString qcontext=clip->text();
    qDebug()<<qcontext;
    if(qcontext=="")
        return;
    char *context;
    QByteArray ba = qcontext.toLatin1();
    context = ba.data();
    MAT temp;
    for(int i=0;i<qcontext.length();i++)
    {
        if(!(context[i]=='.'||(context[i]<='9'&&context[i]>='1')))
            return;
        else if(context[i]=='.')
            temp.m[i/9][i%9]=0;
        else
            temp.m[i/9][i%9]=context[i]-'0';
    }
    QMessageBox info(QMessageBox::NoIcon,"从剪切板粘贴谜题",QString::asprintf("读取到以下谜题:\n\n%s\n\n是否使用该谜题",context),QMessageBox::Yes|QMessageBox::No);
    info.setStyleSheet(styleSheet);
    int result=info.exec();
    if(result)
    {
        delete sudoku;
        sudoku=new SUDOKU(temp);
        LoadPuzzle();
    }
    else
        return;
}
void MainWindow::undo()
{
    if(sudoku!=NULL&&sudoku->history!=NULL)
    {
        qDebug()<<"enter";
        sudoku->history->print();
        elem e=sudoku->history[sudoku->COUNT()-1].undo();
        if(e.x==-1&&e.y==-1&&e.after==-1&&e.before==-1)
            return;
        sudoku->cur.m[e.x][e.y]=e.before;
        if(e.before!=0)
            plate[e.x][e.y]->setText(QString::number(e.before));
        else
            plate[e.x][e.y]->setText(QString(""));
        conflict(e.x,e.y,e.before);
    }
}
void MainWindow::redo()
{
    if(sudoku!=NULL&&sudoku->history!=NULL)
    {
        sudoku->history->print();
        elem e=sudoku->history[sudoku->COUNT()-1].redo();
        if(e.x==-1&&e.y==-1&&e.after==-1&&e.before==-1)
            return;
        sudoku->cur.m[e.x][e.y]=e.before;
        if(e.before!=0)
            plate[e.x][e.y]->setText(QString::number(e.before));
        else
            plate[e.x][e.y]->setText(QString(""));
        conflict(e.x,e.y,e.before);
    }
}
void MainWindow::timerstart(bool)
{
    if(Menus[2].acts[3]->isChecked())
    {
        Menus[2].acts[3]->setIcon(QIcon(":/icons/icons/time-stop.png"));
        connect(Timer,SIGNAL(timeout()),this,SLOT(timeupdate()));
    }
    else
    {
        Menus[2].acts[3]->setIcon(QIcon(":/icons/icons/time-start.png"));
        disconnect(Timer,SIGNAL(timeout()),this,SLOT(timeupdate()));
    }
}

void MainWindow::timeupdate()
{
    *TimerRecord=TimerRecord->addSecs(1);
    TimerBoard->display(TimerRecord->toString("hh:mm:ss"));
}

void MainWindow::timerreset()
{
    TimerRecord->setHMS(0,0,0,0);
    TimerBoard->display(TimerRecord->toString("hh:mm:ss"));
    Timer->start(1000);
    Menus[2].acts[3]->setChecked(false);
    Menus[2].acts[3]->setIcon(QIcon(":/icons/icons/time-start.png"));
    disconnect(Timer,SIGNAL(timeout()),this,SLOT(timeupdate()));
}
bool check(int (*Parameter)[9],int x,int y,int num)
{
    if(num==0)
        return true;
    // Determine whether the number filled in at the current position violates Sudoku rules
    int i, j;
    // Judge the line
    for (i = x, j = 0; j < 9; j++)
        if (Parameter[i][j] == num && j != y)
            return false;
    // Judge the list
    for (i = 0, j = y; i < 9; i++)
        if (Parameter[i][j] == num && i != x)
            return false;
    // Judge the little Jiugongge
    for (i = (x / 3) * 3; i < (x / 3) * 3 + 3; i++)
        for (j = (y / 3) * 3; j < (y / 3) * 3 + 3; j++)
            if (Parameter[i][j] == num && i != x && j != y)
                return false;
    return true;
}

int nextx(int x, int y)
{
    // Auxiliary function of DFSSlover to generate abscissa
    if (y == 8)
        return x + 1;
    return x;
}

int nexty(int x, int y)
{
    // Auxiliary function of DFSSlover to generate ordinate
    if (y == 8)
        return 0;
    return y + 1;
    int temp=x;
    x=temp;
}

bool DFSSolver(int (*Sudoku)[9],int (*Parameter)[9], int x, int y)
{
    // Depth first search solver
    if (x > 8)
    {
        // Conditions for exiting the solver
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                Sudoku[i][j] = Parameter[i][j];
        return 1;
    }
    if (Sudoku[x][y] != 0) // If it has been filled in, continue to solve
        return DFSSolver(Sudoku,Parameter, nextx(x, y), nexty(x, y));
    int copyd[9][9], flag = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            copyd[i][j] = Parameter[i][j];
    for (int i = 1; i < 10; i++)
    {
        if (check(Parameter, x, y, i))
        {
            // If it does not violate the rules, fill in and continue to solve
            copyd[x][y] = i;
            if (DFSSolver(Sudoku,copyd, nextx(x, y), nexty(x, y)))
            {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}
