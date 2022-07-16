#include "dialog/logindialog.h"
#include "ui/ui_logindialog.h"
#include "dialog/widget.h"
#include "ui/ui_widget.h"
#include "controller/titleBar.h"
#include <QFile>
#include<QGraphicsDropShadowEffect>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    QFont font;
    font.setFamily("黑体");
    this->setFont(font);
    this->setWindowIcon(QIcon(":custom/logos/logo.png"));
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);

    TitleBar *m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":custom/logos/logo.png");
    m_titleBar->setWindowTitle("Password Manager");
    m_titleBar->forbiddenMaxmizeButton();
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    m_titleBar->setFixedWidth(ui->frame->width());
    m_titleBar->forbiddenUserButton();

    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor(128,128,128,255));
    shadow_effect->setBlurRadius(20);
    shadow_effect->setOffset(0, 0);
    ui->frame->setGraphicsEffect(shadow_effect);

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

    QPixmap img1;
    img1.load("D:/Ruida/Pictures/面孔/魈/1620050232879_20210808_215712_086.jpg");
    QPixmap pixMap= img1.scaled(100,100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pixMap=PixmapToRound(pixMap,50);
    ui->portrait->setPixmap(pixMap);

    ui->portrait->setScaledContents(true);
//    ui->portrait->setPixmap(QPixmap("D:/HUST-Sources/画廊/面孔/魈/IMG_20220119_151256.jpg"));
//    ui->portrait->setStyleSheet("min-width:100px;max-width:100px;min-height:100px;max-height:100px;border-radius:50px;border-width: 0 0 0 0;");

    ui->username->setEditable(true);
    ui->username->lineEdit()->setStyleSheet(styleSheet);
    ui->username->lineEdit()->setStyleSheet("border:0px");
    ui->space->setStyleSheet("border:0px;background-color:transparent");

    ui->password->setEchoMode(QLineEdit::Password);
    ui->passwordJudge->setStyleSheet("border:0px;background-color:transparent");
    ui->passwordJudge->setIcon(QIcon(":custom/icons/nosee.png"));
    ui->passwordJudge->setStatusTip("nosee");

    connect(ui->yes,SIGNAL(clicked()),this,SLOT(yes_clicked()));
    connect(ui->passwordJudge,SIGNAL(clicked()),this,SLOT(passwordJudge_clicked()));
}

loginDialog::~loginDialog()
{
    delete ui;
}
void loginDialog::yes_clicked()
{
    Widget *w=new Widget();
    w->show();
    this->close();
}
void loginDialog::passwordJudge_clicked()
{
    QPushButton* send=(QPushButton*)sender();
    if(send->statusTip()=="nosee")
    {
        send->setIcon(QIcon(":custom/icons/see.png"));
        send->setStatusTip("see");
        ui->password->setEchoMode(QLineEdit::Normal);
    }
    else if(send->statusTip()=="see")
    {
        send->setIcon(QIcon(":custom/icons/nosee.png"));
        send->setStatusTip("nosee");
        ui->password->setEchoMode(QLineEdit::Password);
    }
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
