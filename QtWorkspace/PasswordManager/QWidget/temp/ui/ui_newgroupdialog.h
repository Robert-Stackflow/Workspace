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
#include <QtWidgets/QCommandLinkButton>
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
    QWidget *editGroup;
    QWidget *layoutWidget_12;
    QVBoxLayout *groupInfoLayout;
    QTextEdit *describe;
    QWidget *layoutWidget_13;
    QHBoxLayout *confirmLayout;
    QPushButton *confirm;
    QPushButton *cancel;
    QCommandLinkButton *jumpToGroupTypeManager;
    QFrame *frame;

    void setupUi(QDialog *newGroupDialog)
    {
        if (newGroupDialog->objectName().isEmpty())
            newGroupDialog->setObjectName(QString::fromUtf8("newGroupDialog"));
        newGroupDialog->resize(680, 500);
        newGroupDialog->setMinimumSize(QSize(680, 500));
        newGroupDialog->setMaximumSize(QSize(680, 500));
        tabWidget = new QTabWidget(newGroupDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 641, 431));
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
        editGroup = new QWidget();
        editGroup->setObjectName(QString::fromUtf8("editGroup"));
        layoutWidget_12 = new QWidget(editGroup);
        layoutWidget_12->setObjectName(QString::fromUtf8("layoutWidget_12"));
        layoutWidget_12->setGeometry(QRect(11, 11, 341, 187));
        groupInfoLayout = new QVBoxLayout(layoutWidget_12);
        groupInfoLayout->setObjectName(QString::fromUtf8("groupInfoLayout"));
        groupInfoLayout->setContentsMargins(0, 0, 0, 0);
        describe = new QTextEdit(editGroup);
        describe->setObjectName(QString::fromUtf8("describe"));
        describe->setGeometry(QRect(360, 10, 261, 341));
        layoutWidget_13 = new QWidget(editGroup);
        layoutWidget_13->setObjectName(QString::fromUtf8("layoutWidget_13"));
        layoutWidget_13->setGeometry(QRect(430, 360, 195, 31));
        confirmLayout = new QHBoxLayout(layoutWidget_13);
        confirmLayout->setObjectName(QString::fromUtf8("confirmLayout"));
        confirmLayout->setContentsMargins(0, 0, 0, 0);
        confirm = new QPushButton(layoutWidget_13);
        confirm->setObjectName(QString::fromUtf8("confirm"));

        confirmLayout->addWidget(confirm);

        cancel = new QPushButton(layoutWidget_13);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        confirmLayout->addWidget(cancel);

        jumpToGroupTypeManager = new QCommandLinkButton(editGroup);
        jumpToGroupTypeManager->setObjectName(QString::fromUtf8("jumpToGroupTypeManager"));
        jumpToGroupTypeManager->setGeometry(QRect(10, 210, 141, 41));
        tabWidget->addTab(editGroup, QString());
        frame = new QFrame(newGroupDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 660, 480));
        frame->setStyleSheet(QString::fromUtf8("border:0px;\n"
"border-radius:10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        tabWidget->raise();

        retranslateUi(newGroupDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(newGroupDialog);
    } // setupUi

    void retranslateUi(QDialog *newGroupDialog)
    {
        newGroupDialog->setWindowTitle(QCoreApplication::translate("newGroupDialog", "Dialog", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(groupManager), QCoreApplication::translate("newGroupDialog", "\345\210\206\347\273\204\347\256\241\347\220\206", nullptr));
        describe->setPlaceholderText(QCoreApplication::translate("newGroupDialog", "\347\274\226\350\276\221\345\244\207\346\263\250", nullptr));
        confirm->setText(QCoreApplication::translate("newGroupDialog", "\347\241\256\345\256\232", nullptr));
        cancel->setText(QCoreApplication::translate("newGroupDialog", "\345\217\226\346\266\210", nullptr));
        jumpToGroupTypeManager->setText(QCoreApplication::translate("newGroupDialog", "\345\210\206\347\273\204\347\261\273\345\236\213\347\256\241\347\220\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(editGroup), QCoreApplication::translate("newGroupDialog", "\347\274\226\350\276\221/\346\226\260\345\273\272\345\210\206\347\273\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newGroupDialog: public Ui_newGroupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGROUPDIALOG_H
