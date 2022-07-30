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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newGroupDialog
{
public:
    QFrame *frame;
    QTextEdit *describe;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *groupNameLayout;
    QVBoxLayout *groupTypeLayout;
    QWidget *layoutWidget_13;
    QHBoxLayout *confirmLayout;
    QPushButton *confirm;
    QPushButton *cancel;

    void setupUi(QDialog *newGroupDialog)
    {
        if (newGroupDialog->objectName().isEmpty())
            newGroupDialog->setObjectName(QString::fromUtf8("newGroupDialog"));
        newGroupDialog->resize(680, 500);
        newGroupDialog->setMinimumSize(QSize(680, 500));
        newGroupDialog->setMaximumSize(QSize(680, 500));
        frame = new QFrame(newGroupDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 661, 481));
        frame->setStyleSheet(QString::fromUtf8("border:0px;\n"
"border-radius:10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        describe = new QTextEdit(newGroupDialog);
        describe->setObjectName(QString::fromUtf8("describe"));
        describe->setGeometry(QRect(30, 150, 621, 281));
        layoutWidget = new QWidget(newGroupDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 80, 621, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        groupNameLayout = new QVBoxLayout();
        groupNameLayout->setObjectName(QString::fromUtf8("groupNameLayout"));

        horizontalLayout->addLayout(groupNameLayout);

        groupTypeLayout = new QVBoxLayout();
        groupTypeLayout->setObjectName(QString::fromUtf8("groupTypeLayout"));

        horizontalLayout->addLayout(groupTypeLayout);

        layoutWidget_13 = new QWidget(newGroupDialog);
        layoutWidget_13->setObjectName(QString::fromUtf8("layoutWidget_13"));
        layoutWidget_13->setGeometry(QRect(430, 440, 231, 37));
        confirmLayout = new QHBoxLayout(layoutWidget_13);
        confirmLayout->setObjectName(QString::fromUtf8("confirmLayout"));
        confirmLayout->setContentsMargins(0, 0, 0, 0);
        confirm = new QPushButton(layoutWidget_13);
        confirm->setObjectName(QString::fromUtf8("confirm"));
        confirm->setMinimumSize(QSize(0, 30));

        confirmLayout->addWidget(confirm);

        cancel = new QPushButton(layoutWidget_13);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setMinimumSize(QSize(0, 30));

        confirmLayout->addWidget(cancel);


        retranslateUi(newGroupDialog);

        QMetaObject::connectSlotsByName(newGroupDialog);
    } // setupUi

    void retranslateUi(QDialog *newGroupDialog)
    {
        newGroupDialog->setWindowTitle(QCoreApplication::translate("newGroupDialog", "Dialog", nullptr));
        describe->setPlaceholderText(QCoreApplication::translate("newGroupDialog", "\347\274\226\350\276\221\345\244\207\346\263\250", nullptr));
        confirm->setText(QCoreApplication::translate("newGroupDialog", "\347\241\256\345\256\232", nullptr));
        cancel->setText(QCoreApplication::translate("newGroupDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newGroupDialog: public Ui_newGroupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWGROUPDIALOG_H
