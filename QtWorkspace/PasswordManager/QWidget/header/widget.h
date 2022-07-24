#ifndef WIDGET_H
#define WIDGET_H
#include "util/databasetablename.h"
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
#include <QMenu>
#include <QPainter>
#include <QClipboard>
#include <QGraphicsDropShadowEffect>
#include <QtGlobal>
#include <QCoreApplication>
#include <QtCore>
#include <QVariant>
#include <QDir>
#include "xlsxchart.h"
#include "xlsxworkbook.h"
#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#include "xlsxchartsheet.h"
#include "xlsxrichstring.h"
#include "controller/titleBar.h"
#include "dialog/optiondialog.h"
#include "dialog/newitemdialog.h"
#include "dialog/newgroupdialog.h"
#include "dialog/newgrouptypedialog.h"
#include "ui_optiondialog.h"
#include "ui_newitemdialog.h"
#include "ui_newgroupdialog.h"
#include "ui_newgrouptypedialog.h"
#include "util/keyItem.h"
#include "util/autofillInfo.h"
#include "util/groups.h"
#include "util/groupTypes.h"
#include "util/fieldTypes.h"
using namespace QXlsx;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT
public:
    //data structure
    Groups* groups;
    AutofillInfo* autofillInfo;
    GroupTypes* groupTypes;
    FieldTypes fieldTypes;
    dataBaseTableName databaseTableNameGetter;
    QSqlDatabase data;
    //widgets
    Ui::Widget *ui;
    QList<QWidget*> widgets;
    QList<QPushButton*> buttons;
    QStackedWidget* stackedWidget;
    QList<QTableWidget*> tableWidgets;
    QList<QStringList> tableWidgetHeaders;
    //Group functions
    QToolButton* save;
    QLineEdit* search;
    QPushButton* addItem;
    QPushButton* addGroup;
    QPushButton* editGroup;
    QPushButton* deleteGroup;
    //saveAs menu
    QMenu *saveAsMenu;
    QAction *saveAsPDF;
    QAction *saveAsCSV;
    QAction *saveAsExcel;
    //dialogs
    optionDialog* optiondialog;
    newItemDialog* newitemdialog;
    newGroupDialog* newgroupdialog;
    newGroupTypeDialog* newgrouptypedialog;
    //custom controllers
    TitleBar *m_titleBar;
    QMenu* tableWidgetMenu;
    //auxiliary variables
    KeyItem* newKeyItem=nullptr;
    Group* newGroup=nullptr;
    int sqlConnectionCount=0;
    //other variables
    QPoint* cursorPos;
    QString styleSheet;
public:
    friend struct Item;
    friend class newItemDialog;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //布局初始化与更新
    void initFrame();
    void updateQSS();
    int fillMoveMenu(QMenu*,int,int);
    void updateTableWidgetView(int index);
    //增删改分组
    void newGroupFunction(int mode);
    void editGroupFunction(QString oldName);
    //增删改条目
    void loadKeyItemFunction(QString& tableName);
    void newKeyItemFunction(QString& tableName);
    //加载、更新数据库
    void loadUserData();
    void updateAutofillInfo();
private slots:
    //导出功能
    void saveSlot();
    void saveMenuTriggered();
    //增删改分组
    void newGroupSlot();
    void editGroupSlot();
    void deleteGroupSlot();
    //分组切换
    void changeTab();
    void onTabIndexChanged(int);
    //增删改条目
    void newKeyItemSlot();
    //tableWidget右键菜单
    void moveKeyItemSlot();
    void copyKeyItemSlot();
    void removeKeyItemSlot();
    void openWebsiteSlot();
    void copyKeyItemInfoSlot();
    void tableWidgetContextMenuRequested(QPoint pos);
    //tableWidget查找、单击
    void searchSlot(const QString&);
    void tableWidgetClickedSlot(int,int);
    //自定义信号对应的槽
    void onGroupCountChanged();
    void onGroupTypeCountChanged();
    //界面调出槽
    void onOptionButtonClicked();
signals:
    void groupCountChanged();
    void groupTypeCountChanged();
};
#endif // WIDGET_H
