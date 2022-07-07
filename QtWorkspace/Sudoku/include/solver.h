#ifndef SOLVER_H
#define SOLVER_H
#include <QObject>
#include <QDebug>
extern const int pos[9][9];
struct MAT{
    int m[9][9];
    MAT(){
        for(int i=0;i<9;++i)
            for(int j=0;j<9;++j)
                m[i][j]=0;
    }
    int NumofZero(){
        int count=0;
        for(int i=0;i<9;++i)
            for(int j=0;j<9;++j)
                if(m[i][j]==0)
                    count++;
        return count;
    }
    bool operator!=(const MAT&a)const{
        for(int i=0;i<9;++i)
            for(int j=0;j<9;++j)
                if(m[i][j]!=a.m[i][j])
                    return 1;
        return 0;
    }
    int init(const QString&a){
        int count=0;
        int len=a.length();
        for(int i=0;i<len;++i)
            if(a[i]=='.'||a[i]=='_')
                m[count/9][count%9]=0,count++;
            else if(a[i]>='0'&&a[i]<='9')
                m[count/9][count%9]=a[i].digitValue(),count++;
        return count==81;
    }
    QString print(){
        QString s;
        for(int i=0;i<9;++i)
            for(int j=0;j<9;++j)
                if(m[i][j]==0)s+='.';
                else s+=m[i][j]+'0';
        qDebug()<<s;
        return s;
    }
};

struct Trip{int x,y,v;};

class Solver : public QObject
{
    Q_OBJECT
public:
    explicit Solver(QObject *parent = 0);
public:
    MAT a;
    MAT showtime;
    int idx[1024];
private:
    int s0[9],s1[9],s2[9],ans,tot,limit,cnt;
    Trip swp,p[100],q[100];
    MAT tmp,zero;
    void dfs(int t);
    int only1sol(int m,int symm);
    int generate(int symm);
public slots:
    int calc(int x);
    int solve(MAT _,int lim=2);
    int generate_range(int l,int r,int symm=0);
};
bool check(int (*Parameter)[9],int x,int y,int num);
#endif // SOLVER_H
