/********************************************************************************
** Form generated from reading UI file 'newgroupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWGROUPDIALOG_H
#define UI_NEWGROUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newGroupDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *groupManager;
    QWidget *newGroup;
    QWidget *layoutWidget_10;
    QHBoxLayout *confirmLayout;
    QPushButton *confirm_newGroup;
    QPushButton *cancel_newGroup;
    QTextEdit *remark_newGroup;
    QWidget *layoutWidget_11;
    QVBoxLayout *newGroupLayout;
    QFrame *frame;

    void setupUi(QDialog *newGroupDialog)
    {
        if (newGroupDialog->objectName().isEmpty())
            newGroupDialog->setObjectName(QString::fromUtf8("newGroupDialog"));
        newGroupDialog->resize(680, 510);
        tabWidget = new QTabWidget(newGroupDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 641, 441));
        QFont font;
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        groupManager = new QWidget();
        groupManager->setObjectName(QString::fromUtf8("groupManager"));
        tabWidget->addTab(groupManager, QString());
        newGroup = new QWidget();
        newGroup->setObjectName(QString::fromUtf8("newGroup"));
        layoutWidget_10 = new QWidget(newGroup);
        layoutWidget_10->setObjectName(QString::fromUtf8("layoutWidget_10"));
        layoutWidget_10->setGeometry(QRect(420, 360, 195, 31));
        confirmLayout = new QHBoxLayout(layoutWidget_10);
        confirmLayout->setObjectName(QString::fromUtf8("confirmLayout"));
        confirmLayout->setContentsMargins(0, 0, 0, 0);
        confirm_newGroup = new QPushButton(layoutWidget_10);
        confirm_newGroup->setObjectName(QString::fromUtf8("confirm_newGroup"));

        confirmLayout->addWidget(confirm_newGroup);

        cancel_newGroup = new QPushButton(layoutWidget_10);
        cancel_newGroup->setObjectName(QString::fromUtf8("cancel_newGroup"));

        confirmLayout->addWidget(cancel_newGroup);

        remark_newGroup = new QTextEdit(newGroup);
        remark_newGroup->setObjectName(QString::fromUtf8("remark_newGroup"));
        remark_newGroup->setGeometry(QRect(360, 20, 261, 331));
        layoutWidget_11 = new QWidget(newGroup);
        layoutWidget_11->setObjectName(QString::fromUtf8("layoutWidget_11"));
        layoutWidget_11->setGeometry(QRect(31, 21, 304, 187));
        newGroupLayout = new QVBoxLayout(layoutWidget_11);
        newGroupLayout->setObjectName(QString::fromUtf8("newGroupLayout"));
        newGroupLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(newGroup, QString());
        frame = new QFrame(newGroupDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 661, 491));
        frame->setStyleSheet(QString::fromUtf8("border:0px;\n"
"border-radius:10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        tabWidget->raise();

        retranslateUi(newGroupDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(newGroupDialog);
    } // setupUi

    void retranslateUi(QDialog *newGroupDialog)
    {
        newGroupDialog->setWindowTitle(QCoreApplication::translate("newGroupDialog", "Dialog", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(groupManager), QCoreApplication::translate("newGroupDialog", "\345\210\206\347\273\204\347\256\241\347\220\206", nullptr));
        confirm_newGroup->setText(QCoreApplication::translate("newGroupDialog", "\347\241\256\345\256\232", nullptr));
        cancel_newGroup->setText(QCoreApplication::translate("newGroupDialog", "\345\217\226\346\266\210", nullptr));
        remark_newGroup->setPlaceholderText(QCoreApplication::translate("newGroupDialog", "\345\241\253\345\206\231\345\244\207\346\263\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(newGroup), QCoreApplication::translate("newGroupDialog", "\346\226\260\345\273\272\345\210\206\347\273\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newGroupDialog: public Ui_newGroupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGROUPDIALOG_H
