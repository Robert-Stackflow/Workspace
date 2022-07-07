#include "include/sudoku.h"
bool STACK::empty()
{
    return top == bottom;
}
bool STACK::full()
{
    return (top+1)%capacity==bottom;
}
STACK::STACK()
{
    bottom = 0;
    top = 0;
    capacity = 100;
    data =new elem[capacity];
}
void STACK::push(int x,int y,int before,int after)
{
    elem e;
    e.x=x;
    e.y=y;
    e.before=before;
    e.after=after;
    if(full())
        bottom=(bottom+1)%capacity;
    data[top] = e;
    top=(top+1)%capacity;
}
void STACK::push(elem e)
{
    if(full())
        bottom=(bottom+1)%capacity;
    data[top++] = e;
    qDebug("%d",top);
    top%=capacity;
    qDebug("%d %c %d %d %d",capacity,e.x+'A',e.y+1,bottom,top);
}
elem STACK::pop()
{
    if(!empty())
    {
        elem r = data[top-1];
        top--;
        return r;
    }
    else
    {
        elem e;
        e.x=e.y=e.before=e.after=-1;
        return e;
    }
}

HISTORY::HISTORY():date(QDate::currentDate()),time(QTime::currentTime())
{
    undolist=new STACK;
    redolist=new STACK;
}
void HISTORY::add(elem e)
{
    undolist->push(e);
}
void HISTORY::add(int x,int y,int before,int after)
{
    elem e;
    e.x=x;
    e.y=y;
    e.before=before;
    e.after=after;
    undolist->push(e);
    qDebug("add:(%c,%d): %d --> %d",x+'A',y+1,before,after);
}
elem HISTORY::undo()
{
    elem e=undolist->pop();
    if(e.x!=-1)
        redolist->push(e.x,e.y,e.after,e.before);
    return e;
}
elem HISTORY::redo()
{
    elem e=redolist->pop();
    if(e.x!=-1)
        undolist->push(e.x,e.y,e.after,e.before);
    return e;
}
void HISTORY::operator=(HISTORY& h)
{
    undolist=h.undolist;
    redolist=h.redolist;
    *(const_cast<QDate*>(&date))=h.date;
    *(const_cast<QTime*>(&time))=h.time;
}
void HISTORY::print()
{
    qDebug("----------------Undolist----------------");
    for(int i=undolist->top-1;i>=undolist->bottom;i--)
        qDebug("(%c,%d): %d --> %d",undolist->data[i].x+'A',undolist->data[i].y+1,undolist->data[i].before,undolist->data[i].after);
    qDebug("----------------Redolist----------------");
    for(int i=redolist->top-1;i>=redolist->bottom;i--)
        qDebug("(%c,%d): %d --> %d",redolist->data[i].x+'A',redolist->data[i].y+1,redolist->data[i].before,redolist->data[i].after);
}
SUDOKU::SUDOKU(int type,int level):type(type),level(level),count(0)//根据类型和难度等级随机生成谜题存入数独格局中
{
    switch(level)
    {
    case 0:
        sol.generate_range(11,20,1);
        break;
    case 1:
        sol.generate_range(21,30,1);
        break;
    case 2:
        sol.generate_range(31,40,1);
        break;
    case 3:
        sol.generate_range(41,50,1);
        break;
    case 4:
        sol.generate_range(51,81,1);
        break;
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            prob.m[i][j]=sol.a.m[i][j],cur.m[i][j]=prob.m[i][j],clash.m[i][j]=0;
    sol.solve(prob,1);
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            res.m[i][j]=sol.a.m[i][j];
}
SUDOKU::SUDOKU(MAT prag):type(-1),level(0),count(0)//根据类型和难度等级随机生成谜题存入数独格局中
{
    int holes=0;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(prag.m[i][j]==0)
                holes++;
            prob.m[i][j]=prag.m[i][j],cur.m[i][j]=prob.m[i][j],clash.m[i][j]=0;
        }
    sol.solve(prag,1);
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            res.m[i][j]=sol.a.m[i][j];
    if(holes>=11&&holes<20) *(const_cast<int*>(&level))=1;
    if(holes>=21&&holes<30) *(const_cast<int*>(&level))=2;
    if(holes>=31&&holes<40) *(const_cast<int*>(&level))=3;
    if(holes>=41&&holes<50) *(const_cast<int*>(&level))=4;
    if(holes>=51&&holes<81) *(const_cast<int*>(&level))=5;
}
MAT SUDOKU::PROB()
{
    return prob;
}
MAT SUDOKU::RES()
{
    return res;
}
int SUDOKU::LEVEL()//返回level等级
{
    return level;
}
int SUDOKU::LIB()//返回谜题库编号
{
    return 1;
}
int SUDOKU::COUNT()
{
    return count;
}
void SUDOKU::AddHistory()
{
    if(!history&&count==0)
    {
        history=new HISTORY;
        *(const_cast<int*>(&count))=count+1;
    }
    else
    {
        HISTORY *new_history=new HISTORY[count+1];
        if(!new_history) return;
        else
        {
            if(history)
                for(int i=0;i<count;i++)
                    new_history[i]=history[i];
            history=new_history;
        }
        *(const_cast<int*>(&count))=count+1;
    }
}
