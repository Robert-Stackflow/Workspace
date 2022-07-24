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
    QString portraitDesPath;
    QString tempPortraitPath;
    QMap<QString,QString> usernameToPortraitPathMap;
    customComboBox* username;
    customLineEdit* password;
    QPixmap PixmapToRound(const QPixmap &src, int radius);
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();
    bool eventFilter(QObject *obj, QEvent *event);
    QString copyFileToPath(QString srcPath,QString desDir);
private:
    QString styleSheet;
private slots:
    void onConfirmClicked();
    void onPortraitDesPathChanged();
    void onUsernameCurrentIndexChanged();
signals:
    void portraitDesPathChanged();
};

#endif // LOGINDIALOG_H
