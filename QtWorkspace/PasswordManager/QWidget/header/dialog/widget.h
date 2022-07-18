#ifndef WIDGET_H
#define WIDGET_H
#pragma warning (disable:4819)
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDebug>
#include <QFileDialog>
#include <QTableWidget>
#include <QInputDialog>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QListWidget>
#include <QToolButton>
#include <QSqlQuery>
#include <QBitmap>
#include <QPainter>
#include <QMessageBox>
#include <QSqlError>
#include <QDateTime>
#include <QMenu>
#include <QPainter>
#include <QClipboard>
#include <QGraphicsDropShadowEffect>
#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVariant>
#include <QDir>
#include "controller/titleBar.h"
#include "additemdialog.h"
#include "ui_additemdialog.h"
#include "dialog/optiondialog.h"
#include "ui_optiondialog.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
typedef struct key{
    int flag=0;
    int type;
    QString name;
    QString nickName;
    QString id;
    QString subName;
    QString password;
    QString mobile;
    QString mail;
    QString website;
    QString remark;
    QDateTime createTime;
    QDateTime lastEditTime;
    bool account[8];//微信,QQ,微博,Github,支付宝,华为,小米,淘宝
    QString toString();
}KEY;
typedef struct Table{
    int flag=0;
    int type;
    int count;
    QString name;
    QString remark;
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
class Widget : public QWidget
{
    Q_OBJECT

public:
    friend struct key;
    friend class addItemDialog;
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initFrame();
    void editTableNameFunction(QString oldName);
    void addItemFunction(QString &tableName,int mode);
    void addTableFunction(QString name,int type=0);
    void updateQSS();
    void myHeaderList();
    void updateTableWidgetView(int index);
    void loadUserData();
    void updatePersonInfo();
    int fillMoveMenu(QMenu*,int,int);
private slots:
    void moveMenuSlot();
    void copyMenuSlot();
    void saveSlot();
    void saveMenuTriggered();
    void addTableSlot();
    void deleteTableSlot();
    void editTableNameSlot();
    void changeTab();
    void addItemSlot();
    void removeItemSlot();
    void openWebsiteSlot();
    void copyAllSlot();
    void onTableCountChanged();
    void onTabIndexChanged(int);
    void searchSlot(const QString&);
    void tableWidgetContextMenuRequested(QPoint pos);
    void tableWidgetDoubleClickedSlot(int,int);
    void tableWidgetClickedSlot(int,int);
    void optionButtonClicked();
public:
    //data structure
    bool sortUpDown=false;
    int tableCount;
    INFO* personInfo;
    QList<TABLE*> tables;
    //widgets
    Ui::Widget *ui;
    QList<QWidget*> widgets;
    QList<QStringList> header;
    QList<QPushButton*> buttons;
    QStackedWidget* stackedWidget;
    QList<QTableWidget*> tableWidgets;
    //table functions
    QToolButton* save;
    QPushButton* addItem;
    QPushButton* addTable;
    QPushButton* deleteTable;
    QPushButton* editTableName;
    QLineEdit* search;
    //save menu
    QMenu *menu;
    QAction *saveAsPDF;
    QAction *saveAsExcel;
    QAction *saveAsCSV;
    //other variables
    int times=0;
    KEY* newKey=NULL;
    QPoint* cursorPos;
    QString styleSheet;
    TitleBar *m_titleBar;
    TABLE* newGroup=NULL;
    QMenu* tableWidgetMenu;
    addItemDialog* additemdialog;
    optionDialog* optiondialog;
signals:
    void tableCountChanged();
};
#endif // WIDGET_H
