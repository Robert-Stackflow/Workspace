#ifndef MUSICDIALOG_H
#define MUSICDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlTableModel>
#include <QTableWidget>
#include <QHeaderView>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QPoint>
#include <QDate>
#include <QComboBox>
#include <QInputDialog>
#include <QBoxLayout>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QMediaMetaData>
namespace Ui {
class musicdialog;
}
typedef struct musicInfo
{
    QMediaPlayer *player;
    QString filePath;
    QString albumArtist;
    QString albumTitle;
    qint64 duration;
    QString lyricsPath;
}MUSICINFO;
typedef struct listInfo
{
    int songCount;
    QString filePath;
    QList<MUSICINFO*> music;
}LISTINFO;
class musicdialog : public QDialog
{
    Q_OBJECT

public:
    QStackedWidget *mainWidget;
    QTableWidget *activeWidget;
    QHBoxLayout *headerLayout;
    QVBoxLayout *windowLayout;
    //Side Bar
    QVBoxLayout *sideLayout;
    QPushButton *localMusic;
    QPushButton *playList;
    QPushButton *curList;
    //My Music
    QWidget *myMusicWidget;
    QVBoxLayout *myMusicLayout;
    QTableWidget *myMusicTableWidget;
    QHBoxLayout *addMusicLayout;
    QPushButton *scanFolder;
    QPushButton *playAll;
    //Play List
    QWidget *myListWidget;
    QVBoxLayout *myListLayout;
    QTableWidget *listTableWidget;
    QHBoxLayout *listEditLayout;
    QLabel *listLabel;
    QComboBox *lists;
    QPushButton *insertList;
    QPushButton *loadList;
    QPushButton *removeList;
    //Current List
    QWidget *curListWidget;
    QVBoxLayout *curListLayout;
    QTableWidget *curListTableWidget;
    QHBoxLayout *curListEditLayout;
    QPushButton *clearCurList;
    QPushButton *playCurrentList;
    QPushButton *saveCurList;
    //Footer
    QHBoxLayout *functionLayout;
    QHBoxLayout *playLayout;
    QVBoxLayout *footerLayout;
    QLabel *nameLabel;
    QLabel *timeLabel;
    QPushButton *mode;
    QPushButton *pre;
    QPushButton *next;
    QPushButton *play;
    QSlider *timeSlider;
    QPushButton *volume;
    QSlider *volumeSlider;
    explicit musicdialog(QWidget *parent = nullptr);
    ~musicdialog();
signals:
    void MetaDataLoaded(QString);
public slots:
    void stackedWidgetView();
    void scanFolderSlot();
    void findFile(const QString & path);
    void loadListSlot();
    void insertListSlot();
    void removeListSlot();
    void listView(int index);
    void LoadMetaData(QMediaPlayer::MediaStatus);
    void fillData();
    void playCurrentListSlot();
    void playNext();
    void playPre();
    void playMode();
    void playButton();
    void playAllSlot();
    void clearCurListSlot();
    void saveCurListSlot();
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 position);
public:
    void InitTableWidget(QTableWidget *tableWidget);
    void UpdateWidgetView();
    void updateUserFile();
    void loadUserFile();
    void InitView();
    int musicCount;
    int loadedCount;
    int curIndex;
    QMediaPlayer *curPlayer;
    QList<MUSICINFO *> music;
    QList<MUSICINFO *> curMusicList;
    QList<LISTINFO *> musicList;
    QStringList musicPathList;
    QStringList lrcList;
    QStringList playListList;
    QStringList folderList;
    Ui::musicdialog *ui;
};

#endif // MUSICDIALOG_H
