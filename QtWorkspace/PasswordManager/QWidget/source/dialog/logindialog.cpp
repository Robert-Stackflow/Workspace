#include "dialog/logindialog.h"
#include "widget.h"
#include "ui_logindialog.h"
#include "controller/titleBar.h"
#include "util/data.h"
#include "QsLog.h"
#include <QFile>
#include <QDir>
#include <QCompleter>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QGraphicsDropShadowEffect>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
using namespace Data;
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    InitDialog();
    //新建用户数据目录
    QDir dir;
    if(!dir.exists(dataPathGetter.getDataDir()))
        if(!dir.mkpath(QDir(dataPathGetter.getDataDir()).absolutePath()))
            QMessageBox::critical(this,"错误","无法创建用户数据文件夹!");
    if(!dir.exists(dataPathGetter.getPortraitDir()))
        if(!dir.mkpath(QDir(dataPathGetter.getPortraitDir()).absolutePath()))
            QMessageBox::critical(this,"错误","无法创建用户数据文件夹!");
    if(!dir.exists(dataPathGetter.getLogsDir()))
        if(!dir.mkpath(dataPathGetter.getLogsDir()))
            QMessageBox::critical(this,"错误","无法创建用户数据文件夹!");
    //添加自定义控件
    username=new customComboBox("用户名",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
    username->setPlaceholderText("输入用户名");
    password=new customLineEdit("密码",AbstractCustomField::REQUIRED,AbstractCustomField::PASSWORD,this);
    password->setPlaceholderText("输入密码");
    ui->verticalLayout->addWidget(username);
    ui->verticalLayout->addWidget(password);
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(onConfirmClicked()));
    connect(username,SIGNAL(currentIndexChanged()),this,SLOT(onUsernameCurrentIndexChanged()));
    connect(this,SIGNAL(portraitDesPathChanged()),this,SLOT(onPortraitDesPathChanged()));
    //设置用户名与密码
    sharedData.database.setDatabaseName(dataPathGetter.getAccountsDataBasePath());
    QSqlQuery query(sharedData.database);
    if(!sharedData.database.open()){
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
        return;
    }else{
        QStringList tableNames=sharedData.database.tables();
        if(!tableNames.contains(dataBaseTableNameGetter.getAccountsTableName())){
            //如果不包含accounts表,则提示创建用户，并创建account表
            ui->confirm->setText("创建用户");
            ui->confirm->setStatusTip("createAccount");
            query.exec("create table "+dataBaseTableNameGetter.getAccountsTableName()+" (username varchar(200),password varchar(200),portraitPath text,createTime varchar(200),lastEditTime varchar(200))");
        }else{
            //否则加载accounts表中的内容
            query.exec("select * from accounts");
            for(int i=0;query.next();i++){
                QString tempUsername=query.value(0).toString();
                QString tempPortraitPath=query.value(2).toString();
                usernameToPortraitPathMap[tempUsername]=tempPortraitPath;
            }
            if(usernameToPortraitPathMap.count()==0){
                //如果用户数量为0，提示创建用户
                ui->confirm->setText("创建用户");
                ui->confirm->setStatusTip("createAccount");
            }else{
                //否则提示登录
                ui->confirm->setText("登录");
                ui->confirm->setStatusTip("login");
                //将用户名加载到username控件，并设置自动补全
                username->addItems(usernameToPortraitPathMap.keys());
                QCompleter *completer = new QCompleter(usernameToPortraitPathMap.keys(), this);
                completer->setCaseSensitivity(Qt::CaseInsensitive);
                username->setCompleter(completer);
                //更改index以手动触发槽
                username->setCurrentIndex(-1);
                username->setCurrentIndex(0);
            }
        }
        sharedData.database.close();
    }
}
void loginDialog::InitDialog(){
    //设置字体
    QFont font;
    font.setFamily("黑体");
    setFont(font);
    //设置窗口样式
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowIcon(QIcon(":custom/logos/logo.png"));
    //添加自定义标题栏
    TitleBar *m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":custom/logos/logo.png");
    m_titleBar->setWindowTitle("Password Manager");
    m_titleBar->forbiddenMaxmizeButton();
    m_titleBar->forbiddenUserButton();
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    m_titleBar->setFixedWidth(ui->frame->width());
    //设置窗口阴影效果
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor(128,128,128,255));
    shadow_effect->setBlurRadius(20);
    shadow_effect->setOffset(0, 0);
    ui->frame->setGraphicsEffect(shadow_effect);
    //加载QSS
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
    //设置默认头像，并设置事件过滤器
    QPixmap image;
    image.load(":custom/icons/defaultPortrait.png");
    QPixmap pixMap = image.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->portrait->setToolTip("选择头像");
    ui->portrait->setPixmap(PixmapToRound(pixMap,50));
    ui->portrait->setScaledContents(true);
    ui->portrait->installEventFilter(this);
}
loginDialog::~loginDialog()
{
    delete ui;
}
void loginDialog::onConfirmClicked()
{
    if(ui->confirm->statusTip()=="createAccount"){
        //如果是创建用户，判断用户名和密码是否合法
        if(username->isValid()&&password->isValid()){
            //记录头像图片路径
            usernameToPortraitPathMap[username->currentText()]=dataPathGetter.getPortraitDir()+"/"+QFileInfo(tempPortraitPath).fileName();
            //向username添加新用户并更新completer
            username->addItem(username->currentText());
            QCompleter *completer = new QCompleter(usernameToPortraitPathMap.keys(), this);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            username->setCompleter(completer);
            //更新数据库
            sharedData.database.setDatabaseName(dataPathGetter.getAccountsDataBasePath());
            QSqlQuery query(sharedData.database);
            if(!sharedData.database.open()){
                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
                return;
            }else{
                query.prepare("insert into "+dataBaseTableNameGetter.getAccountsTableName()+" (username,password,portraitPath,createTime,lastEditTime)"
                                                              "VALUES (:1,:2,:3,:4,:5)");
                query.bindValue(":1",username->currentText());
                query.bindValue(":2",password->text());
                query.bindValue(":3",usernameToPortraitPathMap[username->currentText()]);
                query.bindValue(":4",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":5",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.exec();
                sharedData.database.close();
            }
            QsLogging::Logger::getFileLogger(username->currentText(),"Account");
            QLOG_INFO()<<"Create Account:"<<username->currentText();
            QMessageBox::information(this,"创建用户","成功创建用户\""+username->currentText()+"\"!\n请进行登录!");
            //进行登录
            password->clear();
            ui->confirm->setText("登录");
            ui->confirm->setStatusTip("login");
        }else{
            QString message="无法创建用户:\n";
            if(!username->isValid())
                message+="用户名不合法!\n";
            if(!password->isValid())
                message+="密码不合法!";
            QMessageBox::warning(this,"警告",message);
        }
    }else if(ui->confirm->statusTip()=="login"){
        //如果是登录操作,分步判断用户名是否存在、密码是否正确
        bool isSuccessful=false;
        if(!usernameToPortraitPathMap.contains(username->currentText())){
            //如果用户名不存在，提示是否创建新用户
            int choice=QMessageBox::question(this,"是否创建新用户","用户名\""+username->currentText()+"\"不存在,是否创建新用户?");
            if(choice==QMessageBox::Yes){
                password->clear();
                ui->confirm->setText("创建用户");
                ui->confirm->setStatusTip("createAccount");
                QPixmap image;
                image.load(":custom/icons/defaultPortrait.png");
                QPixmap pixMap = image.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                ui->portrait->setPixmap(PixmapToRound(pixMap,50));
                ui->portrait->setScaledContents(true);
            }
        }else{
            //用户名正确时，读取用户名对应的密码，比较是否与用户输入的密码一致
            sharedData.database.setDatabaseName(dataPathGetter.getAccountsDataBasePath());
            QSqlQuery query(sharedData.database);
            if(!sharedData.database.open()){
                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
                return;
            }else{
                query.exec("select password from accounts where username='"+username->currentText()+"'");
                if(query.first()){
                    if(query.value(0).toString()==password->text())
                        isSuccessful=true;
                    else{
                        QMessageBox::warning(this,"警告","密码不正确");
                        QsLogging::Logger::getFileLogger(username->currentText(),"Account");
                        QLOG_WARN()<<"Login Account:Wrong Password!";
                    }
                }
                sharedData.database.close();
            }
        }
        if(isSuccessful){
            //登陆成功，加载Widget
            QsLogging::Logger::getFileLogger(username->currentText(),"Account");
            QLOG_INFO()<<"Login Account:Login Successfully!";
            Widget *w=new Widget();
            w->show();
            this->close();
        }
    }
}
void loginDialog::onUsernameCurrentIndexChanged(){
    tempPortraitPath=usernameToPortraitPathMap[username->currentText()];
    if(tempPortraitPath=="")
        return;
    QPixmap image;
    image.load(tempPortraitPath);
    QPixmap pixMap = image.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->portrait->setPixmap(PixmapToRound(pixMap,50));
    ui->portrait->setScaledContents(true);
}
bool loginDialog::eventFilter(QObject *obj, QEvent *event){
    if(obj==ui->portrait){
        if (event->type() == QEvent::MouseButtonPress){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton){
                QString path = QFileDialog::getOpenFileName(this, tr("选择头像"), ".", tr("Image Files(*.jpg *.png)"));
                tempPortraitPath=copyFileToPath(path,portraitDesPath);
                if(tempPortraitPath=="")
                    return false;
                QPixmap image;
                image.load(tempPortraitPath);
                QPixmap pixMap = image.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                ui->portrait->setPixmap(PixmapToRound(pixMap,50));
                ui->portrait->setScaledContents(true);
                emit portraitDesPathChanged();
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
    else{
        return QWidget::eventFilter(obj, event);
    }
}
QPixmap loginDialog::PixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull())
        return QPixmap();
    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 50, 50);
    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}
QString loginDialog::copyFileToPath(QString srcPath,QString desDir)
{
    QString desPath=QFileInfo(desDir).absolutePath()+"/"
            +desDir+"/"+QFileInfo(srcPath).baseName()+"_"
            +QString::number(QDateTime::currentDateTime().toTime_t())+"."
            +QFileInfo(srcPath).suffix();
    QString absoluteSrcDir=QFileInfo(srcPath).absolutePath();
    QString absoluteDesDir=QFileInfo(desPath).absolutePath();
    if(!QFile::exists(srcPath))
        return "";
    if(absoluteSrcDir==absoluteDesDir)
        return srcPath;
    if(!QDir(desDir).exists()){
        if(!QDir(desDir).mkdir(QDir(desDir).absolutePath())){
            QMessageBox::critical(this,"错误","无法创建用户数据文件夹!");
            return "";
        }
    }
    if(!QFile::copy(srcPath,desPath))
        return "";
    else
        return desPath;
    return "";
}
void loginDialog::onPortraitDesPathChanged(){
    QString currentUsername=username->currentText();
    if(!usernameToPortraitPathMap.contains(currentUsername))
        return;
    else{
        QsLogging::Logger::getFileLogger(currentUsername,"Account");
        QLOG_INFO()<<"Change Portrait:"<<QString("From '"+usernameToPortraitPathMap[currentUsername]+"' To '"+tempPortraitPath+"'");
        usernameToPortraitPathMap[currentUsername]=tempPortraitPath;
        //更新数据库
        QSqlDatabase data=QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",3));
        data.setDatabaseName(accountDatabasePath);
        QSqlQuery query(data);
        if(!data.open()){
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }else{
            QString sql=QString("update "+accountTableName+" set portraitPath='%1',lastEditTime='%2' where username='%3'")
                    .arg(usernameToPortraitPathMap[currentUsername])
                    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(currentUsername);
            query.exec(sql);
            data.close();
        }
    }
}
