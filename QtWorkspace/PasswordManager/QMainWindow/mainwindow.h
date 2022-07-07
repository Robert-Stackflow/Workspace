#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "titleBar.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileInfo>
#include <QDebug>
#include <QTableWidget>
#include <QInputDialog>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QBitmap>
#include <QPainter>
#include <QMessageBox>
#include <QSqlError>
#include <QDateTime>
#include <QMenu>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include "additemdialog.h"
#include "ui_additemdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
typedef struct key{
    int flag=0;
    int type;//0-普通密码;1-邮箱密码;2-坚果云授权码;3-银行或者支付密码;4-双重验证密码;5-其他密码
    QString name;
    QString nickName;
    QString id;
    QString subName;
    QString password;
    QString mobile;
    QString mail;
    QString website;
    QString tableName;
    QString remark;
    QDateTime createTime;
    QDateTime lastEditTime;
    bool account[8];//微信,QQ,微博,Github,支付宝,华为,小米,淘宝
}KEY;
typedef struct Table{
    int type;
    int count;
    QString name;
    QList<KEY*> keys;
    QDateTime createTime;
    QDateTime lastEditTime;
}TABLE;
typedef struct Info{
    QStringList mobiles;
    QStringList mails;
    QStringList subNames;
    QStringList mailWebsites;
    QStringList jgyWebsites;
}INFO;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initFrame();
    void addItemFunction(QString &tableName,int mode);
    void addTableFunction(QString name,int type=0);
    void updateQSS();
    void myHeaderList();
    void updateTableWidgetView(int index);
    void loadUserData();
    void updatePersonInfo();
private slots:
    void addTableSlot();
    void deleteTableSlot();
    void editTableNameSlot();
    void changeTab();
    void addItemSlot();
    void removeItemSlot();
    void openWebsiteSlot();
    void copyPasswordSlot();
    void copyAllSlot();
    void onTableCountChanged();
    void onTabIndexChanged(int);
    void tableWidgetContextMenuRequested(QPoint pos);
private:
    Ui::MainWindow *ui;
    QWidget* mainWidget;
    int tableCount;
    INFO* personInfo;
    QList<TABLE*> tables;
    QList<QWidget*> widgets;
    QList<QTableWidget*> tableWidgets;
    QList<QPushButton*> buttons;
    QList<QStringList> header;
    QString styleSheet;
    QStackedWidget* stackedWidget;
    QPushButton* addTable;
    QPushButton* deleteTable;
    QPushButton* editTableName;
    QPushButton* addItem;
    QPushButton* save;
    addItemDialog* additemdialog;
    KEY* newKey=NULL;
    TitleBar *m_titleBar;
    QPoint* cursorPos;
    QMenu* tableWidgetMenu;
    //Layout
    QVBoxLayout* mainLayout;
    QHBoxLayout* bottomLayout;
    QVBoxLayout* rightLayout;
    QVBoxLayout* buttonsLayout;
    QHBoxLayout* operationsLayout;
signals:
    void tableCountChanged();
};
#endif // MAINWINDOW_H
