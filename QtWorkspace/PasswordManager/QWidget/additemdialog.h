#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include "titleBar.h"
namespace Ui {
class addItemDialog;
}

class addItemDialog : public QDialog
{
    Q_OBJECT

public:
    bool isNewGroup;
    void InitFrame();
    void InitCommon();
    void InitMail();
    void InitJGY();
    void InitOther();
    void InitGroup();
    void closeEvent(QCloseEvent *e);
    void passwordJudgeFunction(QPushButton* button);
    Ui::addItemDialog *ui;
    TitleBar *m_titleBar;
    QList<QCheckBox*> boxes;
    explicit addItemDialog(QWidget *parent = nullptr);
    ~addItemDialog();
private slots:
    void yes_clicked();

    void no_clicked();

    void passwordJudge_clicked();

    void websiteJudge_edited(const QString &arg);
    void mailJudge_edited(const QString &arg);
    void mobileJudge_edited(const QString &arg);
    void groupNameJudge_edited(const QString &arg);
private:
    QString styleSheet;
};

#endif // ADDITEMDIALOG_H
