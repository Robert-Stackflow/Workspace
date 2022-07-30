#include "dialog/logindialog.h"
#include "QsLog.h"
#include "ui_logindialog.h"
#include "util/databasetablenamegetter.h"
#include "util/datapathgetter.h"
#include "util/shareddata.h"
#include "MuCustomWindow.h"
#include "widget.h"
#include "controller/customdialog.h"
#include <QCompleter>
#include <QDir>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
loginDialog::loginDialog(QWidget *parent) : QDialog(parent),
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
void loginDialog::initDialog()
{
    DataPathGetter &dataPathGetter = DataPathGetter::instance();
    this->setWindowIcon(QIcon(":custom/logos/logo.png"));
    this->setWindowTitle("Password Manager");
    //删除标题栏
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义标题栏
    m_titleBar=new CustomTitleBar(this);
    m_titleBar->setWindowIcon(":/custom/logos/logo.png");
    m_titleBar->setWindowTitle("Password Manager");
    //设置标题栏字体
    QFont font;
    font.setBold(true);
    font.setPointSize(11);
    font.setFamily("黑体");
    m_titleBar->titleLabel->setFont(font);
    //隐藏标题栏按钮
    m_titleBar->setMaximizeVisible(false);
    //设定标题栏位置与大小
    m_titleBar->setFixedWidth(ui->frame->width());
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    //设定阴影效果
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor(128,128,128,255));
    shadow_effect->setBlurRadius(20);
    shadow_effect->setOffset(0, 0);
    ui->frame->setGraphicsEffect(shadow_effect);
    //加载QSS样式
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString temp = this->styleSheet;
        temp += QLatin1String(file.readAll());
        this->styleSheet=temp;
        this->setStyleSheet(styleSheet);
        file.close();
    }
    //设置默认头像，并设置事件过滤器
    loadPortrait(dataPathGetter.getDefaultPortraitPath());
    ui->portrait->installEventFilter(this);
}
void loginDialog::initOther()
{
    //新建用户数据目录
    QDir dir;
    DataPathGetter &dataPathGetter = DataPathGetter::instance();
    if (!dir.exists(dataPathGetter.getDataDir()))
        if (!dir.mkpath(QDir(dataPathGetter.getDataDir()).absolutePath()))
            QMessageBox::critical(this, "错误", "无法创建用户数据文件夹!");
    if (!dir.exists(dataPathGetter.getPortraitDir()))
        if (!dir.mkpath(QDir(dataPathGetter.getPortraitDir()).absolutePath()))
            QMessageBox::critical(this, "错误", "无法创建用户数据文件夹!");
    if (!dir.exists(dataPathGetter.getLogsDir()))
        if (!dir.mkpath(dataPathGetter.getLogsDir()))
            QMessageBox::critical(this, "错误", "无法创建用户数据文件夹!");
    //添加自定义控件
    username = new customComboBox("用户名", AbstractCustomField::REQUIRED, AbstractCustomField::NORMAL, this);
    username->setPlaceholderText("输入用户名");
    password = new customLineEdit("密码", AbstractCustomField::REQUIRED, AbstractCustomField::PASSWORD, this);
    password->setPlaceholderText("输入密码");
    ui->verticalLayout->addWidget(username);
    ui->verticalLayout->addWidget(password);
    //绑定槽函数
    connect(ui->confirm, SIGNAL(clicked()), this, SLOT(onConfirmClicked()));
    connect(this, SIGNAL(portraitDesPathChanged()), this, SLOT(onPortraitDesPathChanged()));
    connect(username, SIGNAL(currentIndexChanged()), this, SLOT(onUsernameCurrentIndexChanged()));
}
void loginDialog::loadAccounts()
{
    //获取各单例类
    SharedData &sharedData = SharedData::instace();
    DataPathGetter &dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter &dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    //加载数据库中的账户与头像
    QString databaseName = dataPathGetter.getAccountsDataBasePath();
    QString accountsTableName = dataBaseTableNameGetter.getAccountsTableName();
    sharedData.database.setDatabaseName(databaseName);
    QSqlQuery query(sharedData.database);
    if (!sharedData.database.open())
    {
        QsLogging::Logger::getFileLogger("PUBLIC", "DATABASE");
        QLOG_WARN() << "Database Connection Error:" << databaseName << "!";
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
        return;
    }
    else
    {
        QsLogging::Logger::getFileLogger("PUBLIC", "DATABASE");
        QLOG_DEBUG() << "Database Connection:" << databaseName;
        if (!sharedData.database.tables().contains(accountsTableName))
        {
            //如果不存在accounts表,则提示创建用户,并创建accounts表
            ui->confirm->setText("创建用户");
            ui->confirm->setStatusTip("createAccount");
            QString createTableSql = "create table " + accountsTableName + " (username varchar(200),password varchar(200),portraitPath text,createTime varchar(200),lastEditTime varchar(200))";
            query.exec(createTableSql);
            QsLogging::Logger::getFileLogger("PUBLIC", "SQL");
            QLOG_DEBUG() << "Create Table(s):" << createTableSql;
        }
        else
        {
            //如果存在accounts表,则加载accounts表中的账户列表
            QString selectSql = "select * from accounts";
            query.exec(selectSql);
            QsLogging::Logger::getFileLogger("PUBLIC", "SQL");
            QLOG_DEBUG() << "Select Column(s):" << selectSql;
            for (int i = 0; query.next(); i++)
            {
                QString newUsername = query.value(0).toString();
                QString newPortraitPath = query.value(2).toString();
                QDateTime newCreateTime = query.value(3).toDateTime();
                QDateTime newLastEditTime = query.value(4).toDateTime();
                Account *newAccount = new Account(newUsername, newCreateTime, newLastEditTime, newPortraitPath);
                sharedData.accountList << newAccount;
                QLOG_DEBUG() << "Load Account:" << newAccount->toString();
            }
            if (sharedData.accountList.count() == 0)
            {
                //如果用户数量为0，提示创建用户
                ui->confirm->setText("创建用户");
                ui->confirm->setStatusTip("createAccount");
            }
            else
            {
                //否则提示登录
                ui->confirm->setText("登录");
                ui->confirm->setStatusTip("login");
                QsLogging::Logger::getFileLogger("PUBLIC", "ACCOUNT");
                QLOG_DEBUG() << "Load Accounts:" << sharedData.accountList.getUsernames();
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
    QString currentUsername = username->currentText();
    QsLogging::Logger::getFileLogger(currentUsername, "PROGRAM");
    QLOG_TRACE() << "Clicked Confirm Button:" << ui->confirm->text() << ui->confirm->statusTip();
    SharedData &sharedData = SharedData::instace();
    DataPathGetter &dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter &dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    if (ui->confirm->statusTip() == "createAccount")
    {
        //如果是创建用户，判断用户名和密码是否合法
        if (username->isValid() && password->isValid())
        {
            //创建新用户
            QString newPortraitPath = "";
            if (tempPortraitPath != "")
                newPortraitPath = dataPathGetter.getPortraitDir() + "/" + QFileInfo(tempPortraitPath).fileName();
            Account *newAccount = new Account(currentUsername, "", newPortraitPath);
            sharedData.accountList << newAccount;
            QsLogging::Logger::getFileLogger(currentUsername, "ACCOUNT");
            QLOG_INFO() << "Create Account:" << newAccount->toString();
            //向username添加新用户并更新completer
            username->clear();
            username->addItems(sharedData.accountList.getUsernames());
            QCompleter *completer = new QCompleter(sharedData.accountList.getUsernames(), this);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            username->setCompleter(completer);
            username->setCurrentText(currentUsername);
            //更新数据库
            QString databaseName = dataPathGetter.getAccountsDataBasePath();
            sharedData.database.setDatabaseName(databaseName);
            QSqlQuery query(sharedData.database);
            if (!sharedData.database.open())
            {
                QsLogging::Logger::getFileLogger(currentUsername, "DATABASE");
                QLOG_WARN() << "Database Connection Error:" << databaseName << "!";
                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
                return;
            }
            else
            {
                QsLogging::Logger::getFileLogger(currentUsername, "DATABASE");
                QLOG_DEBUG() << "Database Connection:" << databaseName;
                QString insertSql = "insert into " + dataBaseTableNameGetter.getAccountsTableName() + " (username,password,portraitPath,createTime,lastEditTime)"
                                                                                                      "VALUES (:1,:2,:3,:4,:5)";
                query.prepare(insertSql);
                query.bindValue(":1", currentUsername);
                query.bindValue(":2", password->text());
                query.bindValue(":3", sharedData.accountList.getAccount(currentUsername)->getPortraitPath());
                query.bindValue(":4", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":5", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.exec();
                QsLogging::Logger::getFileLogger(currentUsername, "SQL");
                QLOG_DEBUG() << "Insert Record(s):" << insertSql;
                sharedData.database.close();
            }
            QMessageBox::information(this, "创建用户", "成功创建用户\"" + currentUsername + "\"!");
            //进行登录
            password->clear();
            ui->confirm->setText("登录");
            ui->confirm->setStatusTip("login");
        }
        else
        {
            QString message = "无法创建用户:\n";
            if (!username->isValid())
                message += "用户名\"" + currentUsername + "\"不合法!\n";
            if (!password->isValid())
                message += "密码不合法!";
            QsLogging::Logger::getFileLogger(currentUsername, "ACCOUNT");
            QLOG_WARN() << "Create Account Error:" << message << "!";
            QMessageBox::warning(this, "警告", message);
        }
    }
    else if (ui->confirm->statusTip() == "login")
    {
        //如果是登录操作,分步判断用户名是否存在、密码是否正确
        bool isSuccessful = false;
        QString currentUsername = username->currentText();
        if (!sharedData.accountList.has(currentUsername))
        {
            //如果用户名不存在，提示是否创建新用户
            int choice = QMessageBox::question(this, "是否创建新用户", "用户名\"" + currentUsername + "\"不存在,是否创建新用户?");
            if (choice == QMessageBox::Yes)
            {
                password->clear();
                ui->confirm->setText("创建用户");
                ui->confirm->setStatusTip("createAccount");
                loadPortrait(dataPathGetter.getDefaultPortraitPath());
            }
        }
        else
        {
            //用户名正确时，读取用户名对应的密码，比较是否与用户输入的密码一致
            QString databaseName = dataPathGetter.getAccountsDataBasePath();
            sharedData.database.setDatabaseName(databaseName);
            QSqlQuery query(sharedData.database);
            if (!sharedData.database.open())
            {
                QsLogging::Logger::getFileLogger(currentUsername, "DATABASE");
                QLOG_WARN() << "Database Connection Error:" << databaseName << "!";
                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
                return;
            }
            else
            {
                QsLogging::Logger::getFileLogger(currentUsername, "DATABASE");
                QLOG_DEBUG() << "Database Connection:" << databaseName;
                QString selectSql = "select password from accounts where username='" + currentUsername + "'";
                query.exec(selectSql);
                QsLogging::Logger::getFileLogger(currentUsername, "SQL");
                QLOG_DEBUG() << "Select Columns:" << selectSql;
                if (query.first())
                {
                    if (query.value(0).toString() == password->text())
                        isSuccessful = true;
                    else
                    {
                        QMessageBox::warning(this, "警告", "密码不正确");
                        QsLogging::Logger::getFileLogger(currentUsername, "ACCOUNT");
                        QLOG_WARN() << "Login Account Error:Wrong Password!";
                    }
                }
                sharedData.database.close();
            }
        }
        if (isSuccessful)
        {
            //登陆成功，加载Widget
            sharedData.accountList.setActiveAccount(currentUsername);
            QsLogging::Logger::getFileLogger(currentUsername, "ACCOUNT");
            QLOG_INFO() << "Login Account:Login " << currentUsername << " Successfully!";
            Widget *w = new Widget();
            w->show();
            this->close();
        }
    }
}
void loginDialog::onUsernameCurrentIndexChanged()
{
    SharedData &sharedData = SharedData::instace();
    DataPathGetter &dataPathGetter = DataPathGetter::instance();
    Account *currentAccount = sharedData.accountList.getAccount(username->currentText());
    if (currentAccount == nullptr)
        return;
    QString imagePath = currentAccount->getPortraitPath();
    if (imagePath == "")
        imagePath = dataPathGetter.getDefaultPortraitPath();
    loadPortrait(imagePath);
}
bool loginDialog::eventFilter(QObject *obj, QEvent *event)
{
    DataPathGetter &dataPathGetter = DataPathGetter::instance();
    if (obj == ui->portrait)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
                QString path = QFileDialog::getOpenFileName(this, tr("选择头像"), ".", tr("Image Files(*.jpg *.png)"));
                QsLogging::Logger::getFileLogger(username->currentText(), "ACCOUNT");
                QLOG_DEBUG() << "Choose Portrait:" << path;
                tempPortraitPath = copyFileToPath(path, dataPathGetter.getPortraitDir());
                if (tempPortraitPath == "")
                {
                    return false;
                }
                else
                {
                    QLOG_DEBUG() << "Copy Portrait Successfully:" << tempPortraitPath;
                    loadPortrait(tempPortraitPath);
                    emit portraitDesPathChanged();
                }
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return QWidget::eventFilter(obj, event);
    }
}
QString loginDialog::copyFileToPath(QString srcPath, QString desDir)
{
    DataPathGetter &dataPathGetter = DataPathGetter::instance();
    //目标图片绝对路径
    QString desPath = QFileInfo(desDir).absolutePath() + '/' + desDir + "/" + QFileInfo(srcPath).baseName() + '_' + QString::number(QDateTime::currentDateTime().toTime_t()) + '.' + QFileInfo(srcPath).suffix();
    //目标图片相对路径
    QString relativeDesPath = dataPathGetter.getPortraitDir() + "/" + QFileInfo(desPath).fileName();
    //源图片相对路径
    QString relativeSrcPath = dataPathGetter.getPortraitDir() + "/" + QFileInfo(srcPath).fileName();
    //源图片绝对文件夹
    QString absoluteSrcDir = QFileInfo(srcPath).absolutePath();
    //目标图片绝对文件夹
    QString absoluteDesDir = QFileInfo(desPath).absolutePath();
    //如果源图片不存在,返回空值
    if (!QFile::exists(srcPath))
        return "";
    //如果源图片文件夹与目标图片文件夹相同，直接返回源图片相对路径
    if (absoluteSrcDir == absoluteDesDir)
        return relativeSrcPath;
    //如果目标文件夹不存在,创建目标文件夹，创建错误时返回空值
    if (!QDir(desDir).exists())
    {
        if (!QDir(desDir).mkdir(QDir(desDir).absolutePath()))
        {
            QsLogging::Logger::getFileLogger(username->currentText(), "ACCOUNT");
            QLOG_DEBUG() << "Copy Portrait Error!";
            QMessageBox::critical(this, "错误", "无法创建用户数据文件夹!");
            return "";
        }
    }
    //复制图片
    if (!QFile::copy(srcPath, desPath))
    {
        //如果复制错误，警告
        QsLogging::Logger::getFileLogger(username->currentText(), "ACCOUNT");
        QLOG_FATAL() << "Copy Portrait Error!";
        QMessageBox::critical(this, "错误", "无法复制头像!");
        return "";
    }
    else
    {
        //如果复制成功，返回目标图片相对路径
        QsLogging::Logger::getFileLogger(username->currentText(), "ACCOUNT");
        QLOG_DEBUG() << "Copy Portrait:"
                     << "From " << srcPath << " to " << relativeDesPath;
        return relativeDesPath;
    }
    //其余情况都返回空值
    return "";
}
void loginDialog::onPortraitDesPathChanged()
{
    SharedData &sharedData = SharedData::instace();
    DataPathGetter &dataPathGetter = DataPathGetter::instance();
    DataBaseTableNameGetter &dataBaseTableNameGetter = DataBaseTableNameGetter::instace();
    QString currentUsername = username->currentText();
    if (!sharedData.accountList.has(currentUsername))
        return;
    else
    {
        QsLogging::Logger::getFileLogger(currentUsername, "ACCOUNT");
        QLOG_INFO() << "Change Portrait:" << QString("From '" + sharedData.accountList.getAccount(currentUsername)->getPortraitPath() + "' To '" + tempPortraitPath + "'");
        sharedData.accountList.getAccount(currentUsername)->setPortraitPath(tempPortraitPath);
        sharedData.accountList.getAccount(currentUsername)->setLastEditTime();
        //更新数据库
        QString databaseName = dataPathGetter.getAccountsDataBasePath();
        sharedData.database.setDatabaseName(databaseName);
        QSqlQuery query(sharedData.database);
        if (!sharedData.database.open())
        {
            QsLogging::Logger::getFileLogger(currentUsername, "DATABASE");
            QLOG_WARN() << "Database Connection Error:" << databaseName << "!";
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
            return;
        }
        else
        {
            QsLogging::Logger::getFileLogger(currentUsername, "DATABASE");
            QLOG_DEBUG() << "Database Connection:" << databaseName;
            QString updateSql = QString("update " + dataBaseTableNameGetter.getAccountsTableName() + " set portraitPath='%1',lastEditTime='%2' where username='%3'")
                    .arg(sharedData.accountList.getAccount(currentUsername)->getPortraitPath())
                    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                    .arg(currentUsername);
            query.exec(updateSql);
            QsLogging::Logger::getFileLogger(currentUsername, "SQL");
            QLOG_DEBUG() << "Update Column(s):" << updateSql;
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
    QSize size(2 * radius, 2 * radius);
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
void loginDialog::loadPortrait(const QString &portraitPath)
{
    QPixmap image;
    image.load(portraitPath);
    QPixmap pixMap = image.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->portrait->setToolTip("选择头像");
    ui->portrait->setPixmap(PixmapToRound(pixMap, 50));
    ui->portrait->setScaledContents(true);
}
