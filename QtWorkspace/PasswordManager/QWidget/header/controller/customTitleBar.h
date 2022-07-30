#ifndef CUSTOMTITLEBAR_H
#define CUSTOMTITLEBAR_H
#include <QLabel>
#include <QEvent>
#include <QPoint>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>

class CustomTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTitleBar(QWidget *parent = NULL);
    void setWindowTitle(const QString& title);
    void setWindowIcon(const QString &iconPath);
    void addCustomButton(QPushButton* newButton);
    void setMaximizeVisible(bool visible);
    void setMinimizeVisible(bool visible);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *obj, QEvent *event);
    void updateMaximize();

protected slots:
    void onClicked();

public:
    bool leftButtonPressed;
    bool maximizeVisible=true;
    bool minimizeVisible=true;
    QPoint end;
    QPoint start;
    QLabel* iconLabel;
    QLabel* titleLabel;
    QPushButton* minimizeButton;
    QPushButton* maximizeButton;
    QPushButton* closeButton;
    QVBoxLayout* mainLayout;
    QHBoxLayout* topLayout;
    QHBoxLayout* leftLayout;
    QHBoxLayout* customLayout;
    QHBoxLayout* rightLayout;
};

#endif // CUSTOMTITLEBAR_H
