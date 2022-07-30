#include "controller/customdialog.h"
#include "ui_customdialog.h"
#include <QIcon>
#include <QGraphicsDropShadowEffect>
CustomDialog::CustomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomDialog)
{
    ui->setupUi(this);
    //设置默认窗口样式
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    //添加自定义标题栏
    customTitleBar = new class CustomTitleBar(this);
    customTitleBar->setGeometry(customTitleBar->geometry().x()+6, customTitleBar->geometry().y(), customTitleBar->width(), customTitleBar->height());
    customTitleBar->setFixedWidth(ui->frame->width());
    //设置标题和图标
    this->setWindowTitle("Password Manager");
    this->setWindowIcon(":custom/logos/logo.png");
    //设置字体
    QFont font;
    font.setFamily("黑体");
    setFont(font);
    //设置窗口阴影效果
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setColor(QColor(128, 128, 128, 255));
    shadowEffect->setBlurRadius(20);
    shadowEffect->setOffset(0,0);
    ui->frame->setGraphicsEffect(shadowEffect);
}

CustomDialog::~CustomDialog()
{
    delete ui;
}
void CustomDialog::setMaximizeVisible(bool visible){
    customTitleBar->setMaximizeVisible(visible);
}
void CustomDialog::setMinimizeVisible(bool visible){
    customTitleBar->setMinimizeVisible(visible);
}
void CustomDialog::setWindowTitle(const QString& title){
    customTitleBar->setWindowTitle(title);
    QDialog* parent=(QDialog*)parentWidget();
    parent->setWindowTitle(title);
}
void CustomDialog::setWindowIcon(const QString& iconPath){
    customTitleBar->setWindowIcon(iconPath);
    QDialog* parent=(QDialog*)parentWidget();
    parent->setWindowIcon(QIcon(iconPath));
}
void CustomDialog::loadStyleSheet(const QString& styleSheetPath){
    QFile file(styleSheetPath);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString temp = this->styleSheet;
        temp += QLatin1String(file.readAll());
        this->styleSheet = temp;
        this->setStyleSheet(styleSheet);
        file.close();
    }
}
