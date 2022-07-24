#ifndef NEWGROUPTYPEDIALOG_H
#define NEWGROUPTYPEDIALOG_H
#include <QDialog>
#include "util/groupType.h"
#include "controller/titleBar.h"
#include "customField/customLineEdit.h"
namespace Ui {
class newGroupTypeDialog;
}
class newGroupTypeDialog : public QDialog
{
    Q_OBJECT

public:
    //表头
    QStringList typeManagerTableWidgetHeader;
    QStringList editFieldsTableWidgetHeader;
    //自定义控件
    TitleBar *m_titleBar;
    customLineEdit* typeName;
    customLineEdit* addFieldName;
    customLineEdit* addFieldTip;
    //辅助变量
    GroupType* currentGroupType;
    QString chosenOldName;
    GroupType* newGroupType;
    QList<AbstractCustomField*> tempFields;
    //辅助变量
    int currentRow=-1;
    int currentMode=-1;//0-新建,1-编辑
private:
    QString styleSheet;
public:
    explicit newGroupTypeDialog(QWidget *parent = nullptr);
    ~newGroupTypeDialog();
    virtual bool eventFilter(QObject *obj, QEvent *e) override;
    virtual void closeEvent(QCloseEvent* event) override;
    void loadGroupTypes();
private:
    Ui::newGroupTypeDialog *ui;
    void initDialog();
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

#endif // NEWGROUPTYPEDIALOG_H
