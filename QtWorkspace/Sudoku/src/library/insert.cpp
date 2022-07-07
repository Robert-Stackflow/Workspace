#include "include/include.h"
int insertTimes=0;
Insert::Insert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Insert)
{
    ui->setupUi(this);
    this->setWindowTitle("新建");
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet+= QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
    QStringList typeList;
    typeList<<"我的创建"<<"我的收藏";
    ui->libTypeBox->addItems(typeList);
    ui->libTypeBox->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(type);
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(updateView(int)));
    connect(ui->libPathButton,SIGNAL(clicked()),this,SLOT(getNewLibName()));
    connect(ui->newLibraryYes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->newPuzzleYes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->newTableYes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->newLibraryNo,SIGNAL(clicked()),this,SLOT(no_clicked()));
    connect(ui->newPuzzleNo,SIGNAL(clicked()),this,SLOT(no_clicked()));
    connect(ui->newTableNo,SIGNAL(clicked()),this,SLOT(no_clicked()));
    ui->libPathEdit->setReadOnly(true);
    connect(ui->tableIdEdit,SIGNAL(textEdited(QString)),this,SLOT(tableId_textEdited(QString)));
    connect(ui->puzzleIdEdit,SIGNAL(textEdited(QString)),this,SLOT(puzzleId_textEdited(QString)));
    connect(ui->puzzlecontentEdit,SIGNAL(textEdited(QString)),this,SLOT(puzzlecontent_textEdited(QString)));
}
Insert::~Insert()
{
    delete ui;
}
void Insert::recSignal()
{
    Library *p= (Library *)parentWidget();
    p->newPuzzleInfo=new PUZZLEINFO;
    p->newTableInfo=new TABLEINFO;
    p->newLibraryInfo=new LIBRARYINFO;
    ui->tabWidget->setCurrentIndex(p->main->currentIndex());
}
void Insert::updateView(int index)
{
    Library *p= (Library *)parentWidget();
    p->windowstate=index+1;
    p->main->setCurrentIndex(index);
}
void Insert::getNewLibName()
{
    QString filePath=QFileDialog::getSaveFileName(this, "新建数据库","./",tr("DataBase files(*.db)"));
    ui->libPathEdit->setText(filePath);
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",--insertTimes));
    data.setHostName("localhost");
    data.setDatabaseName(filePath);
    data.setUserName("data");
    data.setPassword("123456");
    if(!data.open())
    {
        QMessageBox::critical(0, QObject::tr("数据库连接错误"), data.lastError().text());
        return;
    }
    else
    {
        QPixmap wrong;
        QPixmap right;
        right.load(":/icons/icons/right.png");
        wrong.load(":/icons/icons/wrong.png");
        right.scaled(ui->libPathtipLabel->size(),Qt::KeepAspectRatio);
        wrong.scaled(ui->libPathtipLabel->size(),Qt::KeepAspectRatio);
        ui->libPathtipLabel->setScaledContents(true);
        QFileInfo temp=QFileInfo(ui->libPathEdit->text());
        if(temp.isFile())
            ui->libPathtipLabel->setPixmap(QPixmap(right)),ui->libPathtipLabel->setStatusTip("valid");
        else
            ui->libPathtipLabel->setPixmap(QPixmap(wrong)),ui->libPathtipLabel->setStatusTip("invalid");
    }
}
void Insert::yes_clicked()
{
    Library *p= (Library *)parentWidget();
    if(ui->tabWidget->currentIndex()==0)
    {
        if(ui->libPathtipLabel->statusTip()=="valid")
        {
            p->newLibraryInfo->remarkName=ui->libRemarkNameEdit->text();
            p->newLibraryInfo->createTime=QDateTime::currentDateTime();
            p->newLibraryInfo->averageLevel=0;
            p->newLibraryInfo->successRate=-1;
            p->newLibraryInfo->flag=1;
            p->newLibraryInfo->fileInfo=QFileInfo(ui->libPathEdit->text());
            p->newLibraryInfo->puzzleCount=0;
            p->newLibraryInfo->tableCount=0;
            p->newLibraryInfo->type=ui->libTypeBox->currentIndex()+2;
        }
        else
        {
            p->newLibraryInfo->flag=0;
        }
    }
    else if(ui->tabWidget->currentIndex()==1)
    {
        if(ui->tableinlibtypeBox->currentIndex()!=-1&&ui->tableinlibBox->currentIndex()!=-1&&ui->tableIdtipLabel->statusTip()=="valid")
        {
            p->newTableInfo->remarkName=ui->tableRemarkNameEdit->text();
            p->newTableInfo->tableName=ui->tableIdEdit->text();
            p->newTableInfo->averageLevel=0;
            p->newTableInfo->puzzleCount=0;
            p->newTableInfo->successRate=-1;
            p->newTableInfo->flag=1;
            p->newTableInfo->createTime=QDateTime::currentDateTime();
            p->newTableInfo->type=p->field->currentIndex();
        }
        else
        {
            p->newTableInfo->flag=0;
        }
    }
    else if(ui->tabWidget->currentIndex()==2)
    {
        if(ui->puzzleinlibtypeBox->currentIndex()!=-1&&ui->puzzleinlibBox->currentIndex()!=-1&&ui->puzzleintableBox->currentIndex()!=-1&&ui->puzzleIdtipLabel->statusTip()=="valid"&&ui->puzzlecontenttipLabel->statusTip()=="valid")
        {
            p->newPuzzleInfo->id=ui->puzzleIdEdit->text();
            p->newPuzzleInfo->puzzle=ui->puzzlecontentEdit->text();
            int count=0;
            for(int i=0;i<p->newPuzzleInfo->puzzle.length();i++)
                if(p->newPuzzleInfo->puzzle.toLatin1().data()[i]=='.')
                    count++;
            if(count>=11&&count<=20)
                p->newPuzzleInfo->level=0;
            if(count>=21&&count<=30)
                p->newPuzzleInfo->level=1;
            if(count>=31&&count<=40)
                p->newPuzzleInfo->level=2;
            if(count>=41&&count<=50)
                p->newPuzzleInfo->level=3;
            else
                p->newPuzzleInfo->level=4;
            p->newPuzzleInfo->state=0;
            p->newPuzzleInfo->collection=0;
            p->newPuzzleInfo->flag=1;
            p->newPuzzleInfo->type=p->field->currentIndex();
        }
        else
        {
            p->newPuzzleInfo->flag=0;
        }
    }
    this->close();
}

void Insert::no_clicked()
{
    Library *p= (Library *)parentWidget();
    p->newLibraryInfo->flag=p->newTableInfo->flag=p->newPuzzleInfo->flag=0;
    this->close();
}
void Insert::tableId_textEdited(const QString &arg1)
{
    QPixmap wrong;
    QPixmap right;
    right.load(":/icons/icons/right.png");
    wrong.load(":/icons/icons/wrong.png");
    right.scaled(ui->tableIdtipLabel->size(),Qt::KeepAspectRatio);
    wrong.scaled(ui->tableIdtipLabel->size(),Qt::KeepAspectRatio);
    ui->tableIdtipLabel->setScaledContents(true);
    int len=arg1.length();
    int flag=1;
    for(int i=0;i<len;i++)
        if(!(arg1.toLatin1().data()[i]=='_'||(arg1.toLatin1().data()[i]>='A'&&arg1.toLatin1().data()[i]<='Z')||(arg1.toLatin1().data()[i]>='a'&&arg1.toLatin1().data()[i]<='z')||(i!=0&&arg1.toLatin1().data()[i]>='0'&&arg1.toLatin1().data()[i]<='9')))
            flag=0;
    if(flag&&len!=0)
        ui->tableIdtipLabel->setPixmap(QPixmap(right)),ui->tableIdtipLabel->setStatusTip("valid");
    else
        ui->tableIdtipLabel->setPixmap(QPixmap(wrong)),ui->tableIdtipLabel->setStatusTip("invalid");
}
void Insert::puzzleId_textEdited(const QString &arg1)
{
    QPixmap wrong;
    QPixmap right;
    right.load(":/icons/icons/right.png");
    wrong.load(":/icons/icons/wrong.png");
    right.scaled(ui->puzzleIdtipLabel->size(),Qt::KeepAspectRatio);
    wrong.scaled(ui->puzzleIdtipLabel->size(),Qt::KeepAspectRatio);
    ui->puzzleIdtipLabel->setScaledContents(true);
    int len=arg1.length();
    int flag1=1,flag2=1,flag3=1;
    if(arg1.toLatin1().data()[0]!='A'&&arg1.toLatin1().data()[0]!='D'&&arg1.toLatin1().data()[0]!='L'&&arg1.toLatin1().data()[0]!='R')
        flag1=0;
    for(int i=1;i<len;i++)
    {
        if(!(arg1.toLatin1().data()[i]>='0'&&arg1.toLatin1().data()[i]<='9'))
            flag2=0;
    }
    if(!(arg1.toLatin1().data()[3]>='0'&&arg1.toLatin1().data()[3]<='4'))
        flag3=0;
    if(flag1&&flag2&&flag3&&len==7)
        ui->puzzleIdtipLabel->setPixmap(QPixmap(right)),ui->puzzleIdtipLabel->setStatusTip("valid");
    else
        ui->puzzleIdtipLabel->setPixmap(QPixmap(wrong)),ui->puzzleIdtipLabel->setStatusTip("invalid");
}

void Insert::puzzlecontent_textEdited(const QString &arg1)
{
    QPixmap wrong;
    QPixmap right;
    right.load(":/icons/icons/right.png");
    wrong.load(":/icons/icons/wrong.png");
    right.scaled(ui->puzzlecontenttipLabel->size(),Qt::KeepAspectRatio);
    wrong.scaled(ui->puzzlecontenttipLabel->size(),Qt::KeepAspectRatio);
    ui->puzzlecontenttipLabel->setScaledContents(true);
    char *context;
    QByteArray ba = arg1.toLatin1();
    context = ba.data();
    int flag0=1,flag1=1,flag2=1;
    if(arg1.length()<81)
        flag0=0;
    MAT temp;
    for(int i=0;i<arg1.length();i++)
    {
        if(!(context[i]=='.'||(context[i]<='9'&&context[i]>='1')))
            flag1=0;
        else if(context[i]=='.')
            temp.m[i/9][i%9]=0;
        else
            temp.m[i/9][i%9]=context[i]-'0';
    }
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(!check(temp.m,i,j,temp.m[i][j]))
                flag2=0;
    if(flag0&&flag1&&flag2)
        ui->puzzlecontenttipLabel->setPixmap(QPixmap(right)),ui->puzzlecontenttipLabel->setStatusTip("valid");
    else
        ui->puzzlecontenttipLabel->setPixmap(QPixmap(wrong)),ui->puzzlecontenttipLabel->setStatusTip("invalid");
}
