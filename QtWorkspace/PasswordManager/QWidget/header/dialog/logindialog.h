#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "customField/customComboBox.h"
#include "customField/customLineEdit.h"
#include <QDialog>
namespace Ui {
class loginDialog;
}
class loginDialog : public QDialog
{
    Q_OBJECT
public:
    Ui::loginDialog *ui;
    //辅助变量，便于不同函数间传递数据
    QString tempPortraitPath;
    //自定义控件
    customComboBox* username;
    customLineEdit* password;
private:
    QString styleSheet;
public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();
    bool eventFilter(QObject *obj, QEvent *event);
    QString copyFileToPath(QString srcPath,QString desDir);
    QPixmap PixmapToRound(const QPixmap &src, int radius);
private:
    void initDialog();
    void loadAccounts();
private slots:
    void onConfirmClicked();
    void onPortraitDesPathChanged();
    void onUsernameCurrentIndexChanged();
signals:
    void portraitDesPathChanged();
};

#endif // LOGINDIALOG_H
