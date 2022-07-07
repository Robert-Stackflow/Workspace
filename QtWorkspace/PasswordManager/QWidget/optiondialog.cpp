#include "optiondialog.h"
#include "ui_optiondialog.h"
#include "widget.h"
#include <QDebug>
#include <QFile>
#include <QCompleter>
optionDialog::optionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::optionDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":/application/qrc/icon.png");
    m_titleBar->forbiddenMaxmizeButton();
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(11);
    font.setBold(true);
    m_titleBar->m_titleLabel->setFont(font);
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    m_titleBar->setFixedWidth(ui->frame->width());
    m_titleBar->forbiddenUserButton();

    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor());
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
}

optionDialog::~optionDialog()
{
    delete ui;
}
