#ifndef GROUPTYPEMANAGERDIALOG_H
#define GROUPTYPEMANAGERDIALOG_H
#include <QDialog>
#include "util/groupType.h"
#include "controller/titleBar.h"
#include "customField/customLineEdit.h"
namespace Ui {
class groupTypeManagerDialog;
}
class groupTypeManagerDialog : public QDialog
{
    Q_OBJECT

public:
    //表头
    QStringList typeManagerTableWidgetHeader;
    QStringList editFieldsTableWidgetHeader;
    //自定义组件
    TitleBar *m_titleBar;
    customLineEdit* typeName;
    customLineEdit* addFieldName;
    customLineEdit* addFieldTip;
    //辅助变量
    GroupType* chosenType;
    QString chosenOldName;
    GroupType* newGroupType;
    QList<AbstractCustomField*> tempFields;
    //辅助变量
    int currentRow=-1;
    int currentMode=-1;//0-新建,1-编辑
private:
    QString styleSheet;
public:
    explicit groupTypeManagerDialog(QWidget *parent = nullptr);
    ~groupTypeManagerDialog();
    virtual bool eventFilter(QObject *obj, QEvent *e) override;
    virtual void closeEvent(QCloseEvent* event) override;
private:
    Ui::groupTypeManagerDialog *ui;
    void loadGroupTypes();
    QStringList getFieldTypeNameList() const;
public slots:
    void onTypeManagerTableWidgetClicked();
    void onEditTypeClicked();
    void onDeleteTypeClicked();
    void onCopyTypeClicked();
    void onNewTypeClicked();
    void onCancelClicked();
    void onConfirmClicked();
    void onAddFieldClicked();
    void onIsReqiuredCheckBoxToggled(bool);
signals:
    void typeManagerTableWidgetClicked();
    void groupTypeCountChanged();
};

#endif // GROUPTYPEMANAGERDIALOG_H
