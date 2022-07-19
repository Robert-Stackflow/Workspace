﻿#include "dialog/newitemdialog.h"
#include "customItem/customComboBox.h"
#include "customItem/customLineEdit.h"
#include "ui_newitemdialog.h"
#include "dialog/widget.h"
newItemDialog::newItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newItemDialog)
{
    ui->setupUi(this);
    //删除标题栏
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义标题栏
    m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":/custom/icons/icon.png");
    //设置标题栏字体
    QFont font;
    font.setBold(true);
    font.setPointSize(11);
    font.setFamily("黑体");
    m_titleBar->m_titleLabel->setFont(font);
    //隐藏标题栏按钮
    m_titleBar->forbiddenUserButton();
    m_titleBar->forbiddenMaxmizeButton();
    //设定标题栏位置与大小
    m_titleBar->setFixedWidth(ui->frame->width());
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    //设定阴影效果
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor(128,128,128,255));
    shadow_effect->setBlurRadius(20);
    shadow_effect->setOffset(0, 0);
    ui->frame->setGraphicsEffect(shadow_effect);
    //隐藏tabWidget标题栏
    ui->tabWidget->tabBar()->hide();
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
    customLineEdit* appName=new customLineEdit("应用",abstractCustomItem::REQUIRED,abstractCustomItem::NORMAL,this);
    ui->infoLayout->addWidget(appName);
    customLineEdit* nickName=new customLineEdit("昵称",abstractCustomItem::OPTIONAL,abstractCustomItem::NORMAL,this);
    ui->infoLayout->addWidget(nickName);
    customLineEdit* id=new customLineEdit("ID",abstractCustomItem::OPTIONAL,abstractCustomItem::NORMAL,this);
    ui->infoLayout->addWidget(id);
    customLineEdit* password=new customLineEdit("密码",abstractCustomItem::REQUIRED,abstractCustomItem::PASSWORD,this);
    ui->infoLayout->addWidget(password);
    customComboBox* mobile=new customComboBox("手机",abstractCustomItem::OPTIONAL,abstractCustomItem::MOBILE,this);
    ui->infoLayout->addWidget(mobile);
    customComboBox* mail=new customComboBox("邮箱",abstractCustomItem::OPTIONAL,abstractCustomItem::MAIL,this);
    ui->infoLayout->addWidget(mail);
    customComboBox* website=new customComboBox("网址",abstractCustomItem::OPTIONAL,abstractCustomItem::WEBSITE,this);
    ui->infoLayout->addWidget(website);
}

newItemDialog::~newItemDialog()
{
    delete ui;
}
