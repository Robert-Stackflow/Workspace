#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "include.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Ui::MainWindow *ui;
    QTextToSpeech *tts;
    friend class Option;
    friend class Library;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Game And Edition Events
    void level_changed(bool);
    void type_changed(bool);
    void fill();
    void fill(int i, int j);
    void NewGame();
    void LoadPuzzle();
    void TestResult();
    void conflict(int x, int y, int num);
    void ClearConflict();
    void copy();
    void paste();
    void undo();
    void redo();
    void AddtoDB();
    // Operation MenuBar Events
    void result_triggered();
    void Restart();
    void LoadResult();
    void timerstart(bool);
    void timeupdate();
    void timerreset();
    // Tool MenuBar Events
    void collection_triggered();
    void option_triggered();
    // View MenuBar Events
    void color_triggered();
    void full_triggered(bool checked);   // full screen mode
    void simple_triggered(bool checked); // simple mode
    // Music MenuBar Events
    void play_triggered(bool); // play or stop the music
    void volume_triggered(bool);
    void music_triggered();
    // Help MenuBar Events
    void help_triggered();
    void feedback_triggered();
    void contact_triggered();
    void update_triggered();
    void tips_triggered();
    // ToolBar Trigger Events
    void toolbarhide_triggered();      // Hide all the toobars
    void toolbardisplay_triggered();   // display all the toolbars
    void toolbar_1_toggled();
    void toolbar_2_toggled();
    void toolbar_3_toggled();
    void toolbar_4_toggled();
    void statusbarvisible_triggered(); // control whether to display the statusbar
    // Trayicon Trigger Events
    void trayiconhide_triggered();                             // hide the trayicon
    void trayiconlight_triggered();                            // choose the light trayicon
    void trayiconnight_triggered();                            // choose the night trayicon
    void closeEvent(QCloseEvent *event);                       // monitor the close event
    void changeEvent(QEvent *event);                           // monitor the change event
    void activeTray(QSystemTrayIcon::ActivationReason reason); // choose whether to show the window through mouse and trayicon
    void TraywindowSlot();                                     // choose whether to show the window through the context
    void quit();                                               // choose to quit the exe through the context
    //Settings .int Events
    void WriteSettings();
    void ReadSettings();
    void LoadSettings();
    // Mouse And Key Events
    QString FoundCertainButton(int type,int x,int y);
    void keyPressEvent(QKeyEvent *event);
    //    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void Initial();
    void MyMenuBar();
    void MyGameMenuBar();
    void MyEditMenuBar();
    void MyOperateMenuBar();
    void MyToolMenuBar();
    void MyViewMenuBar();
    void MyMusicMenuBar();
    void MyHelpMenuBar();
    void MyTrayIcon();
    void MyToolBar();
    void MyStatusBar();
    void MyTimer();
    void MyTTS();
    void MyQSS();
    void MyPlate();
    void MyPlayer();

private:
    // Interface Controller
    QMenuBar *menuBar;
    MenuAction Menus[7];
    QToolBar *ToolBars[4];
    QPushButton ***plate;
    QLabel coor[9][2];
    TrayIcon *trayicon;
    // Sudoku controller
    SUDOKU *sudoku;
    QTimer *Timer;
    QTime *TimerRecord;
    QLCDNumber *TimerBoard;
    QMediaPlayer *player;
    // Dialog Objective
    Theme *theme=NULL;
    AboutDialog *about=NULL;
    HelpDialog *help=NULL;
    Option *option=NULL;
    Library *collection=NULL;
    musicdialog *music=NULL;
    // System Neccesity
    QString styleSheet;
    QSettings *settings;
    SYNC *sync;
};
#endif // MAINWINDOW_H
