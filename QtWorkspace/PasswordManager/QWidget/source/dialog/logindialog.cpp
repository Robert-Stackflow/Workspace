#include "dialog/logindialog.h"
#include "ui_logindialog.h"
#include "controller/titleBar.h"
#include "widget.h"
#include <QFile>
#include <QGraphicsDropShadowEffect>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    portraitDesPath="portrait";
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
    //设置头像
    QPixmap image;
    image.load(":custom/icons/defaultPortrait.png");
    QPixmap pixMap = image.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->portrait->setToolTip("选择头像");
    ui->portrait->setPixmap(PixmapToRound(pixMap,50));
    ui->portrait->setScaledContents(true);
    ui->portrait->installEventFilter(this);
    //添加控件
    username=new customComboBox("用户名",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
    username->setPlaceholderText("输入用户名");
    password=new customLineEdit("密码",AbstractCustomField::REQUIRED,AbstractCustomField::PASSWORD,this);
    password->setPlaceholderText("输入密码");
    ui->verticalLayout->addWidget(username);
    ui->verticalLayout->addWidget(password);
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(onConfirmClicked()));
    connect(username,SIGNAL(currentIndexChanged()),this,SLOT(onUsernameCurrentIndexChanged()));
    //设置用户名与密码
    QSqlDatabase data=QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",1));
    data.setDatabaseName("user.db");
    QSqlQuery query(data);
    if(!data.open()){
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
        return;
    }else{
        QStringList tableNames=data.tables();
        if(!tableNames.contains("accounts")){
            ui->confirm->setText("创建用户");
            ui->confirm->setStatusTip("createAccount");
            query.exec("create table accounts (username varchar(200),password varchar(200),portraitPath text,createTime varchar(200),lastEditTime varchar(200))");
        }else{
            query.exec("select * from accounts");
            for(int i=0;query.next();i++){
                QString tempUsername=query.value(0).toString();
                QString tempPortraitPath=query.value(2).toString();
                usernameToPortraitPathMap[tempUsername]=tempPortraitPath;
            }
            if(usernameToPortraitPathMap.count()==0){
                ui->confirm->setText("创建用户");
                ui->confirm->setStatusTip("createAccount");
            }else{
                ui->confirm->setText("登录");
                ui->confirm->setStatusTip("login");
                username->addItems(usernameToPortraitPathMap.keys());
                username->setCurrentIndex(-1);
                username->setCurrentIndex(0);
            }
        }
        data.close();
    }
}

loginDialog::~loginDialog()
{
    delete ui;
}
void loginDialog::onConfirmClicked()
{
    if(ui->confirm->statusTip()=="createAccount"){
        if(username->isValid()&&password->isValid()){
            qDebug()<<portraitDesPath+"/"+QFileInfo(tempPortraitPath).fileName();
            usernameToPortraitPathMap[username->currentText()]=portraitDesPath+"/"+QFileInfo(tempPortraitPath).fileName();
            username->addItem(username->currentText());
            QSqlDatabase data=QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",2));
            data.setDatabaseName("user.db");
            QSqlQuery query(data);
            if(!data.open()){
                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
                return;
            }else{
                query.prepare("insert into accounts (username,password,portraitPath,createTime,lastEditTime)"
                              "VALUES (:1,:2,:3,:4,:5)");
                query.bindValue(":1",username->currentText());
                query.bindValue(":2",password->text());
                query.bindValue(":3",usernameToPortraitPathMap[username->currentText()]);
                query.bindValue(":4",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":5",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.exec();
                data.close();
            }
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
        bool isSuccessful=false;
        if(!usernameToPortraitPathMap.contains(username->currentText())){
            int choice=QMessageBox::question(this,"是否创建新用户","用户名\""+username->currentText()+"\"不存在,是否创建新用户?");
            if(choice==QMessageBox::Yes){
                ui->confirm->setText("创建用户");
                ui->confirm->setStatusTip("createAccount");
                QPixmap image;
                image.load(":custom/icons/defaultPortrait.png");
                QPixmap pixMap = image.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                ui->portrait->setPixmap(PixmapToRound(pixMap,50));
                ui->portrait->setScaledContents(true);
            }
        }else{
            QSqlDatabase data=QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",3));
            data.setDatabaseName("user.db");
            QSqlQuery query(data);
            if(!data.open()){
                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
                return;
            }else{
                query.exec("select password from accounts where username='"+username->currentText()+"'");
                if(query.first()){
                    if(query.value(0).toString()==password->text())
                        isSuccessful=true;
                    else
                        QMessageBox::warning(this,"警告","密码不正确");
                }
                data.close();
            }
        }
        if(isSuccessful){
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
            QMessageBox::warning(this,"警告","无法复制图片到portrait目录!");
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
}
