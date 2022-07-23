#include "dialog/logindialog.h"
#include "ui_logindialog.h"
#include "controller/titleBar.h"
#include "customField/customComboBox.h"
#include "customField/customLineEdit.h"
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
    image.load("D:/Ruida/Pictures/面孔/魈/1620050232879_20210808_215712_086.jpg");
    QPixmap pixMap = image.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pixMap=PixmapToRound(pixMap,50);
    ui->portrait->setPixmap(pixMap);
    ui->portrait->setScaledContents(true);
    //设置用户名与密码
    customComboBox* username=new customComboBox("用户名",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
    customLineEdit* password=new customLineEdit("密码",AbstractCustomField::REQUIRED,AbstractCustomField::PASSWORD,this);
    ui->verticalLayout->addWidget(username);
    ui->verticalLayout->addWidget(password);
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(confirmClicked()));
}

loginDialog::~loginDialog()
{
    delete ui;
}
void loginDialog::confirmClicked()
{
    Widget *w=new Widget();
    w->show();
    this->close();
}
QPixmap loginDialog::PixmapToRound(const QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }
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
