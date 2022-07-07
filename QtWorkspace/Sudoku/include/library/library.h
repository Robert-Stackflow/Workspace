#ifndef LIBRARY_H
#define LIBRARY_H
#include "include/library/insert.h"
#include "ui_insert.h"
#include "include/library/filter.h"
namespace Ui {
class Library;
}
typedef struct puzzle
{
    QString id;
    int flag=0;
    int type;
    int level;
    int state;
    int collection;
    QString puzzle;
}PUZZLEINFO;
typedef struct table
{
    int type;
    int flag=0;
    QString tableName;
    int puzzleCount;
    QString remarkName;
    QDateTime createTime;
    double averageLevel;
    double successRate;
    QList<PUZZLEINFO*> puzzles;
}TABLEINFO;
typedef struct library
{
    int type;
    int flag=0;
    QFileInfo fileInfo;
    QString remarkName;
    QDateTime createTime;
    int tableCount;
    int puzzleCount;
    double averageLevel;
    double successRate;
    QList<TABLEINFO*> tables;
}LIBRARYINFO;


class Library : public QDialog
{
    Q_OBJECT

public:
    friend class Insert;
    static int times;
    int windowstate;//0表示父窗口,1表示newLibrary,2表示newTable，3表示newPuzzle
    QVBoxLayout *windowLayout;
    QTableWidget *activeWidget;
    QTableWidget *tableWidget;
    QTableWidget *LibraryWidget;
    QTableWidget *LibrariesWidget;
    QSqlTableModel *sqlmodel;
    QMenu* TWMenu;
    //Functions of aboutLibrary;
    QList<LIBRARYINFO*> file;
    QHBoxLayout *aboutLibrary;
    QLabel* mainLabel;
    QComboBox* main;
    QLabel* fieldLabel;
    QComboBox* field;
    QLabel* libLabel;
    QComboBox* lib;
    QLabel* contentLabel;
    QComboBox* content;
    QPushButton *function;
    QPushButton* newButton;
    QLineEdit* findEdit;
    QPushButton* find;
    explicit Library(QWidget *parent = nullptr);
    ~Library();

private:
    QString dbName;
    QString tableName;
    Ui::Library *ui;
    PUZZLEINFO *newPuzzleInfo;
    TABLEINFO *newTableInfo;
    LIBRARYINFO *newLibraryInfo;
    QPoint *cursorPos;
    Insert *insertDialog;
    friend class FilterWidget;
    FilterWidget* filterWidget = nullptr;
    QMap<int, QStringList> map;
private slots:
    void mainView(int);
    void fieldView(int);
    void libView(int);
    void contentView(int);
    void onHeaderClicked(int);
    void initMap();
    void filterChanged();
    void filter(int col, QStringList showList);
    bool eventFilter(QObject *target, QEvent *event);
    void closeFilterWidget();
    void LoadTable(QFileInfo info,QString& tableName);
    void LoadLibrary(QFileInfo info);
    void LoadLibraries();
    void updateUserFile(const QString& filePath="",const QString& tableName="",const QString& puzzleId="");
    void loadUserFile();
    void openFolder();
    void UpdateWidgetView();
    void IniFrame();
    void IniTableWidget();
    void IniLibraryWidget();
    void IniLibrariesWidget();
    void openLibrary();
    void insertLibrary();
    void deleteLibrary();
    void openTable();
    void insertTable();
    void deleteTable();
    void loadPuzzle();
    void copyPuzzle();
    void insertPuzzle();
    void deletePuzzle();
    void ContextMenuRequested(QPoint pos);
};

#endif // LIBRARY_H
