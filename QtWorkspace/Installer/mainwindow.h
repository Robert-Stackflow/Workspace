#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileInfo>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class APP : public QWidget{
public:
    QLabel icon;
    QLabel name;
    QLabel info;
    QString filePath;
    QString parameter;
    QString group;
    QString website;
    QHBoxLayout *main;
    QVBoxLayout *nameInfo;
    QPushButton *goWebsite;
    QPushButton *openFolder;
    QPushButton *update;
    APP();
    APP(QString filePathString,QString infoString,QString websiteString,QString parameterString,QString groupString);
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTabWidget* super;
    QWidget* all;
    QVBoxLayout *allLayout;
    QWidget* option;
};
#endif // MAINWINDOW_H
