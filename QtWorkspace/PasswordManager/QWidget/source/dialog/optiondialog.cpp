#include "dialog/optiondialog.h"
#include "ui_optiondialog.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
optionDialog::optionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::optionDialog)
{
    ui->setupUi(this);
    //设置窗口样式
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义标题栏
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(11);
    font.setBold(true);
    m_titleBar=new CustomTitleBar(this);
    m_titleBar->setWindowIcon(":custom/logos/logo.png");
    m_titleBar->setMaximizeVisible(false);
    m_titleBar->titleLabel->setFont(font);
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    m_titleBar->setFixedWidth(ui->frame->width());
    //设置阴影效果
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor());
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
}

optionDialog::~optionDialog()
{
    delete ui;
}
