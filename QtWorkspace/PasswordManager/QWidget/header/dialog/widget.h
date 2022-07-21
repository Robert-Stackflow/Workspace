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
#include "optiondialog.h"
#include "newitemdialog.h"
#include "newgroupdialog.h"
#include "grouptypemanagerdialog.h"
#include "ui_optiondialog.h"
#include "ui_newitemdialog.h"
#include "ui_newgroupdialog.h"
#include "ui_grouptypemanagerdialog.h"
#include "util/structures.h"
#include "util/groupType.h"
#include "controller/titleBar.h"
using namespace QXlsx;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT
public:
    //data structure
    int groupCount;
    QList<GROUP*> groups;
    AUTOFILLINFO* autofillInfo;
    groupTypes* groupTypes;
    itemTypes itemTypes;
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
    groupTypeManagerDialog* grouptypemanagerdialog;
    //custom controllers
    TitleBar *m_titleBar;
    QMenu* tableWidgetMenu;
    //auxiliary variables
    ITEM* newKey=NULL;
    GROUP* newGroup=NULL;
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
    void initFrame();
    void editGroupFunction(QString oldName);
    void loadItemFunction(QString& tableName);
    void newItemFunction(QString &tableName);
    void newGroupFunction(QString name,int type=0);
    void updateQSS();
    void myHeaderList();
    void updateTableWidgetView(int index);
    void loadUserData();
    void updateAutofillInfo();
    int fillMoveMenu(QMenu*,int,int);
private slots:
    void saveSlot();
    void saveMenuTriggered();
    void newGroupSlot();
    void deleteGroupSlot();
    void editGroupSlot();
    void changeTab();
    void newItemSlot();
    //tableWidgetMenu
    void moveItemSlot();
    void copyItemSlot();
    void removeItemSlot();
    void openWebsiteSlot();
    void copyItemInfoSlot();
    void onGroupCountChanged();
    void onTabIndexChanged(int);
    void searchSlot(const QString&);
    void tableWidgetContextMenuRequested(QPoint pos);
    void tableWidgetClickedSlot(int,int);
    void optionButtonClicked();
    void onGroupTypeCountChanged();
signals:
    void groupCountChanged();
};
#endif // WIDGET_H
