#include "dialog/newgroupdialog.h"
#include "ui_newgroupdialog.h"
#include "dialog/widget.h"
newGroupDialog::newGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGroupDialog)
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
    //    //隐藏tabWidget标题栏
    //    ui->tabWidget->tabBar()->hide();
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
}

newGroupDialog::~newGroupDialog()
{
    delete ui;
}
void newGroupDialog::setWindowTitle(const QString& title){
    m_titleBar->setWindowTitle(title);
}
