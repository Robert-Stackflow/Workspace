#ifndef NEWGROUPDIALOG_H
#define NEWGROUPDIALOG_H
#include <QDialog>
#include "util/group.h"
#include "controller/titleBar.h"
#include "customField/customComboBox.h"
#include "customField/customLineEdit.h"
namespace Ui {
class newGroupDialog;
}

class newGroupDialog : public QDialog
{
    Q_OBJECT

public:
    TitleBar *m_titleBar;
    Ui::newGroupDialog *ui;
    customLineEdit* newGroupName;
    customComboBox* newGroupType;
    Group* newGroup;
    int currentMode;//0-新建,1-编辑
    explicit newGroupDialog(QWidget *parent = nullptr);
    ~newGroupDialog();
    void setWindowTitle(const QString& title);
    void setCurrentMode(int newCurrentMode);
private:
    QString styleSheet;
public slots:
    void onConfirmClicked();
    void onCancelClicked();
private slots:
    void onJumpToGroupTypeManagerClicked();
};

#endif // NEWGROUPDIALOG_H
