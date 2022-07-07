#ifndef INCLUDE_H
#define INCLUDE_H
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLCDNumber>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QRadioButton>
#include <QSettings>
#include <QSizePolicy>
#include <QStandardItemModel>
#include <QSystemTrayIcon>
#include <QTextCodec>
#include <QTime>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QtTextToSpeech/QTextToSpeech>
#include"ui_theme.h"
#include"ui_option.h"
#include"ui_musicdialog.h"
#include"ui_library.h"
#include"ui_history.h"
#include"ui_helpdialog.h"
#include"ui_background.h"
#include"ui_aboutdialog.h"
#include"sudoku.h"
#include"include/dialog/theme.h"
#include"include/dialog/option.h"
#include"include/dialog/musicdialog.h"
#include"include/library/library.h"
#include"include/dialog/history.h"
#include"include/dialog/helpdialog.h"
#include"include/dialog/background.h"
#include"include/dialog/aboutdialog.h"
typedef struct MenuAction
{
    QMenu *main;
    MenuAction **sub;
    QAction **acts;
} MenuAction;
typedef struct TrayIcon
{
    QSystemTrayIcon *systemTray;
    QMenu *Traymenu;
    QAction *Traywindow;
    QAction *Traynew;
    QAction *Traysave;
    QAction *Trayexit;
    QAction *Trayoption;
} TrayIcon;
typedef struct sync{
    struct system{
        int startupstatus;
        struct window{
            QSize size;
            QPoint pos;
        }window;
        bool toolbars[4];
    }system;
    struct game{
        int level;
        int type;
        int candidates;
        bool conflict_tips;
        bool loadlast;
        bool auto_timing;
        bool auto_stop_timing;
        int auto_stop_threshold;
    }game;
    struct view{
        QString font;
        bool full_mode;
        bool simple_mode;
        int language;
        int trayicon;
        bool statusbar;
    }view;
    struct advanced{
        bool closed_prompt_box;
        bool closed_to_trayicon;
        bool voice;
    }advanced;
}SYNC;
#endif // INCLUDE_H
