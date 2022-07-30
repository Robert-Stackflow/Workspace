#ifndef TITLEBAR_H
#define TITLEBAR_H
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

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = NULL);
    void setWindowTitle(const QString& title);
    void setTitleBarIcon(const QString& iconPath);
    void forbiddenMaxmizeButton();
    void forbiddenUserButton();
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
    bool m_leftButtonPressed;
    bool m_maximizeForbidden=false;
    QPoint m_end;
    QPoint m_start;
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QPushButton* m_optionButton;
    QPushButton* m_userButton;
    QPushButton* m_minimizeButton;
    QPushButton* m_maximizeButton;
    QPushButton* m_closeButton;
};

#endif // TITLEBAR_H
