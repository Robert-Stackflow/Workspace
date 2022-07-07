#ifndef SUDOKU_H
#define SUDOKU_H
#include <QDate>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlDriver>
#include "solver.h"
using namespace std;
typedef struct node{
    int x;
    int y;
    int before;
    int after;
}elem;
struct STACK{
    int top;
    int bottom;
    int capacity;
    elem *data;
public:
    STACK();
    bool full();
    bool empty();
    void push(elem e);
    void push(int x,int y,int before,int after);
    elem pop();
};
struct HISTORY{
    const QDate date;//存储尝试时间的数组
    const QTime time;//存储每次尝试用时的数组
    STACK* undolist;
    STACK* redolist;
    HISTORY();
    void add(elem e);
    void add(int x,int y,int before,int after);
    elem undo();
    elem redo();
    void operator=(HISTORY& h);
    void print();
};

class SUDOKU{//每个数独游戏的信息
    const int type;//谜题类型：内置为0,DIY为1,谜题库加载为2,随机生成为3
    string id;//谜题编号:第1位代表谜题库类型,内置为A,DIY为D,随机生成为R,谜题库加载为L
    //第2至3位代表所属谜题库编号,第4位代表难度等级,第5-7位代表顺次编号,每种谜题库最多99个,最多每个谜题库的每种难度最多999道题目,总计7位
    const int level;
    int collect;//标记是否收藏（-1为未收藏，否则为收藏库编号）
    int state;//标记状态：尝试0，完成1，未尝试-1
    const int count;//历史尝试次数
    MAT prob;//初盘
    MAT res;//终盘
    Solver sol;//求解器
public:
    MAT cur;//当前盘
    MAT clash;//冲突盘
    HISTORY* history;//历史尝试记录数组
    SUDOKU(int type,int level);//根据类型和难度等级随机生成谜题存入数独格局中
    SUDOKU(MAT prag);
    MAT PROB();
    MAT RES();
    int LEVEL();//返回level等级
    int LIB();//返回谜题库编号
    int COUNT();//返回尝试次数
    void AddHistory();
};

class LIBRARY{//每个谜题库的信息（内置，DIY，谜题库，随机库,收藏库，历史库）
    int type;//谜题库类型，优先级为内置>>谜题库>>DIY，可以与收藏库和历史库共存
    int id;//谜题库编号，按照每种库进行编号
    int maxn;//谜题库最多谜题数目
    string name;//谜题库名称
    string filepath;//加载库的文件路径
    const int average_level;//该库平均难度等级
    SUDOKU *data;//指向存储当前库的所有数独数组
public:
    LIBRARY(int type=0,string filename="");//根据谜题库类型和谜题库路径加载库
};

#endif // SUDOKU_H
