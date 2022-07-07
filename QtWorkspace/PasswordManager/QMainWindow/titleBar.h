#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPoint>
#include <QPixmap>
#include <QString>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = NULL);
    void setWindowTitle(const QString& title);
    void setTitleBarIcon(const QString& iconPath);
    void forbiddenMaxmizeButton();
    void forbiddenUserButton();
    QLabel* m_titleLabel;
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual bool eventFilter(QObject *obj, QEvent *event);
    void updateMaximize();

protected slots:
    void onClicked();

private:
    bool m_maximizeForbidden=false;
    QLabel* m_iconLabel;
    QPushButton* m_settingButton;
    QPushButton* m_userButton;
    QPushButton* m_minimizeButton;
    QPushButton* m_maximizeButton;
    QPushButton* m_closeButton;
    QPoint m_start;
    QPoint m_end;
    bool m_leftButtonPressed;
};

#endif // TITLEBAR_H
