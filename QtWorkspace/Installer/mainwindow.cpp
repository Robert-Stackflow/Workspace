#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QProxyStyle>
#include <QStyleOptionTab>
class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,const QSize &size, const QWidget *widget) const
    {
        QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            s.transpose();
            s.rwidth() = 90;
            s.rheight() = 44;
        }
        return s;
    }
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel) {
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;
                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x89cfff);
                    painter->setBrush(QBrush(0x89cfff));
                    painter->drawRect(allRect.adjusted(6, 6, -6, -6));
                    painter->restore();
                }
                QTextOption option;
                option.setAlignment(Qt::AlignCenter);
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);
                }
                else {
                    painter->setPen(0x5d5d5d);
                }
                painter->drawText(allRect, tab->text, option);
                return;
            }
        }
        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);
        }
    }
};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->statusBar()->setSizeGripEnabled(false);
    this->setWindowTitle("Your Installer");
    this->setWindowIcon(QIcon(":/application/icon.png"));
    all=new QWidget();
    allLayout=new QVBoxLayout();
    all->setLayout(allLayout);
    option=new QWidget();
    super=new QTabWidget(this);
    super->setGeometry(10,10,this->geometry().width()-200,this->geometry().height()-200);
    super->addTab(all,"全部应用");
    super->addTab(option,"选项");
    super->setTabsClosable(false);
    super->setTabPosition(QTabWidget::West);
    super->tabBar()->setStyle(new CustomTabStyle);
    APP *test=new APP("D:\\Portable Program\\ScreenToGif.exe","naN","naN","naN","naN");
    qDebug()<<"e";
    allLayout->addLayout(test->main);
}

MainWindow::~MainWindow()
{
    delete ui;
}
APP::APP(QString filePathString,QString infoString,QString websiteString,QString parameterString,QString groupString)
{
    QFile file(filePathString);
    filePath=filePathString;
    website=websiteString;
    int sizeInt=file.size()/1024/1024;
    QString newInfo=QString::number(sizeInt)+"MB|"+infoString+"|"+groupString;
    name.setText(QFileInfo(filePathString).completeBaseName());
    info.setText(newInfo);
    parameter=parameterString;
    main=new QHBoxLayout();
    nameInfo=new QVBoxLayout();
    openFolder=new QPushButton("打开文件夹");
    update=new QPushButton("更新信息");
    goWebsite=new QPushButton("访问官网");
    nameInfo->addWidget(&name);
    nameInfo->addWidget(&info);
    main->addWidget(&icon);
    main->addLayout(nameInfo);
    main->addWidget(openFolder);
    main->addWidget(update);
    main->addWidget(goWebsite);
}
