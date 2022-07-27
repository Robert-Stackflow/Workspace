#include "dialog/logindialog.h"
#include "ui_logindialog.h"
#include "widget.h"
#include "QsLog.h"
#include "util/shareddata.h"
#include "util/datapathgetter.h"
#include "util/databasetablenamegetter.h"
#include "controller/titleBar.h"
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QCompleter>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    //初始化Dialog
    initDialog();
    //初始化其他控件与槽函数
    initOther();
    //加载数据库
    loadAccounts();
}
void loginDialog::initDialog(){
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
void loginDialog::initOther(){
    //新建用户数据目录
    QDir dir;
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
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
    //绑定槽函数
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(onConfirmClicked()));
    connect(this,SIGNAL(portraitDesPathChanged()),this,SLOT(onPortraitDesPathChanged()));
    connect(username,SIGNAL(currentIndexChanged()),this,SLOT(onUsernameCurrentIndexChanged()));
}
void loginDialog::loadAccounts(){
    //获取各单例类
    SharedData& sharedData = SharedData::instace();
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
    QsLogging::Logger& logger=QsLogging::Logger::getFileLogger("PUBLIC","Account");
    DataBaseTableNameGetter& dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    //加载数据库中的账户与头像
    sharedData.database.setDatabaseName(dataPathGetter.getAccountsDataBasePath());
    QSqlQuery query(sharedData.database);
    if(!sharedData.database.open()){
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
        return;
    }else{
        QStringList tables=sharedData.database.tables();
        QString accountsTableName=dataBaseTableNameGetter.getAccountsTableName();
        if(!tables.contains(accountsTableName)){
            //如果不存在accounts表,则提示创建用户，并创建accounts表
            ui->confirm->setText("创建用户");
            ui->confirm->setStatusTip("createAccount");
            query.exec("create table "+accountsTableName+" (username varchar(200),password varchar(200),portraitPath text,createTime varchar(200),lastEditTime varchar(200))");
        }else{
            //否则加载accounts表中的账户列表
            query.exec("select * from accounts");
            for(int i=0;query.next();i++){
                QString newUsername=query.value(0).toString();
                QString newPortraitPath=query.value(2).toString();
                QDateTime newCreateTime=query.value(3).toDateTime();
                QDateTime newLastEditTime=query.value(4).toDateTime();
                Account* newAccount=new Account(newUsername,newCreateTime,newLastEditTime,newPortraitPath);
                sharedData.accountList<<newAccount;
            }
            if(sharedData.accountList.count()==0){
                //如果用户数量为0，提示创建用户
                ui->confirm->setText("创建用户");
                ui->confirm->setStatusTip("createAccount");
            }else{
                //否则提示登录
                ui->confirm->setText("登录");
                ui->confirm->setStatusTip("login");
                //将用户名加载到username控件，并设置自动补全
                username->addItems(sharedData.accountList.getUsernames());
                QCompleter *completer = new QCompleter(sharedData.accountList.getUsernames(), this);
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
void loginDialog::onConfirmClicked()
{
    SharedData& sharedData = SharedData::instace();
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter& dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    if(ui->confirm->statusTip()=="createAccount"){
        //如果是创建用户，判断用户名和密码是否合法
        if(username->isValid()&&password->isValid()){
            //记录头像图片路径
            sharedData.accountList.getAccount(username->currentText())->setPortraitPath(dataPathGetter.getPortraitDir()+"/"+QFileInfo(tempPortraitPath).fileName());
            //向username添加新用户并更新completer
            username->clear();
            username->addItems(sharedData.accountList.getUsernames());
            QCompleter *completer = new QCompleter(sharedData.accountList.getUsernames(), this);
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
                query.bindValue(":3",sharedData.accountList.getAccount(username->currentText())->getPortraitPath());
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
        if(!sharedData.accountList.has(username->currentText())){
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
            sharedData.accountList.setActiveAccount(username->currentText());
            QsLogging::Logger::getFileLogger(username->currentText(),"Account");
            QLOG_INFO()<<"Login Account:Login Successfully!";
            Widget *w=new Widget();
            w->show();
            this->close();
        }
    }
}
void loginDialog::onUsernameCurrentIndexChanged(){
    SharedData& sharedData = SharedData::instace();
    tempPortraitPath=sharedData.accountList.getAccount(username->currentText())->getPortraitPath();
    if(tempPortraitPath=="")
        return;
    QPixmap image;
    image.load(tempPortraitPath);
    QPixmap pixMap = image.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->portrait->setPixmap(PixmapToRound(pixMap,50));
    ui->portrait->setScaledContents(true);
}
bool loginDialog::eventFilter(QObject *obj, QEvent *event){
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
    if(obj==ui->portrait){
        if (event->type() == QEvent::MouseButtonPress){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton){
                QString path = QFileDialog::getOpenFileName(this, tr("选择头像"), ".", tr("Image Files(*.jpg *.png)"));
                tempPortraitPath=copyFileToPath(path,dataPathGetter.getPortraitDir());
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
QString loginDialog::copyFileToPath(QString srcPath,QString desDir)
{
    QString desPath=QFileInfo(desDir).absolutePath()+'/'
            +desDir+"/"+QFileInfo(srcPath).baseName()+'_'
            +QString::number(QDateTime::currentDateTime().toTime_t())+'.'
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
    SharedData& sharedData = SharedData::instace();
    DataPathGetter& dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter& dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    QString currentUsername=username->currentText();
    if(!sharedData.accountList.has(currentUsername))
        return;
    else{
        QsLogging::Logger::getFileLogger(currentUsername,"Account");
        QLOG_INFO()<<"Change Portrait:"<<QString("From '"+sharedData.accountList.getAccount(currentUsername)->getPortraitPath()+"' To '"+tempPortraitPath+"'");
        sharedData.accountList.getAccount(currentUsername)->setPortraitPath(tempPortraitPath);
        sharedData.accountList.getAccount(currentUsername)->setLastEditTime();
        //更新数据库
        sharedData.database.setDatabaseName(dataPathGetter.getAccountsDataBasePath());
        QSqlQuery query(sharedData.database);
        if(!sharedData.database.open()){
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
            return;
        }else{
            QString sql=QString("update "+dataBaseTableNameGetter.getAccountsTableName()+" set portraitPath='%1',lastEditTime='%2' where username='%3'")
                    .arg(sharedData.accountList.getAccount(currentUsername)->getPortraitPath())
                    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(currentUsername);
            query.exec(sql);
            sharedData.database.close();
        }
    }
}
loginDialog::~loginDialog()
{
    delete ui;
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
