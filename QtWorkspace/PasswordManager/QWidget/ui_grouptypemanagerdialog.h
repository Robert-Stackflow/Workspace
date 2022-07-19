/********************************************************************************
** Form generated from reading UI file 'grouptypemanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPTYPEMANAGERDIALOG_H
#define UI_GROUPTYPEMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_groupTypeManagerDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *defaultType;
    QWidget *layoutWidget;
    QVBoxLayout *typeNameLayout_defaultType;
    QTextEdit *remark_defaultType;
    QGroupBox *editFields_defaultType;
    QPushButton *saveChange_defaultType;
    QWidget *typeManager;
    QWidget *newType;
    QWidget *layoutWidget_10;
    QHBoxLayout *confirmBoxLayout;
    QPushButton *confirm;
    QPushButton *cancle;
    QWidget *widget;
    QVBoxLayout *typeNameLayout_newType;
    QTextEdit *remark_newType;
    QGroupBox *editFields_newType;
    QFrame *frame;

    void setupUi(QDialog *groupTypeManagerDialog)
    {
        if (groupTypeManagerDialog->objectName().isEmpty())
            groupTypeManagerDialog->setObjectName(QString::fromUtf8("groupTypeManagerDialog"));
        groupTypeManagerDialog->resize(680, 510);
        tabWidget = new QTabWidget(groupTypeManagerDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 641, 441));
        QFont font;
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        defaultType = new QWidget();
        defaultType->setObjectName(QString::fromUtf8("defaultType"));
        layoutWidget = new QWidget(defaultType);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 311, 41));
        typeNameLayout_defaultType = new QVBoxLayout(layoutWidget);
        typeNameLayout_defaultType->setObjectName(QString::fromUtf8("typeNameLayout_defaultType"));
        typeNameLayout_defaultType->setContentsMargins(0, 0, 0, 0);
        remark_defaultType = new QTextEdit(defaultType);
        remark_defaultType->setObjectName(QString::fromUtf8("remark_defaultType"));
        remark_defaultType->setGeometry(QRect(10, 60, 311, 331));
        editFields_defaultType = new QGroupBox(defaultType);
        editFields_defaultType->setObjectName(QString::fromUtf8("editFields_defaultType"));
        editFields_defaultType->setGeometry(QRect(340, 10, 281, 341));
        saveChange_defaultType = new QPushButton(defaultType);
        saveChange_defaultType->setObjectName(QString::fromUtf8("saveChange_defaultType"));
        saveChange_defaultType->setGeometry(QRect(520, 360, 93, 29));
        tabWidget->addTab(defaultType, QString());
        typeManager = new QWidget();
        typeManager->setObjectName(QString::fromUtf8("typeManager"));
        tabWidget->addTab(typeManager, QString());
        newType = new QWidget();
        newType->setObjectName(QString::fromUtf8("newType"));
        layoutWidget_10 = new QWidget(newType);
        layoutWidget_10->setObjectName(QString::fromUtf8("layoutWidget_10"));
        layoutWidget_10->setGeometry(QRect(420, 360, 195, 31));
        confirmBoxLayout = new QHBoxLayout(layoutWidget_10);
        confirmBoxLayout->setObjectName(QString::fromUtf8("confirmBoxLayout"));
        confirmBoxLayout->setContentsMargins(0, 0, 0, 0);
        confirm = new QPushButton(layoutWidget_10);
        confirm->setObjectName(QString::fromUtf8("confirm"));

        confirmBoxLayout->addWidget(confirm);

        cancle = new QPushButton(layoutWidget_10);
        cancle->setObjectName(QString::fromUtf8("cancle"));

        confirmBoxLayout->addWidget(cancle);

        widget = new QWidget(newType);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 311, 41));
        typeNameLayout_newType = new QVBoxLayout(widget);
        typeNameLayout_newType->setObjectName(QString::fromUtf8("typeNameLayout_newType"));
        typeNameLayout_newType->setContentsMargins(0, 0, 0, 0);
        remark_newType = new QTextEdit(newType);
        remark_newType->setObjectName(QString::fromUtf8("remark_newType"));
        remark_newType->setGeometry(QRect(10, 60, 311, 331));
        editFields_newType = new QGroupBox(newType);
        editFields_newType->setObjectName(QString::fromUtf8("editFields_newType"));
        editFields_newType->setGeometry(QRect(340, 10, 281, 341));
        tabWidget->addTab(newType, QString());
        frame = new QFrame(groupTypeManagerDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 661, 491));
        frame->setStyleSheet(QString::fromUtf8("border:0px;\n"
"border-radius:10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        tabWidget->raise();

        retranslateUi(groupTypeManagerDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(groupTypeManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *groupTypeManagerDialog)
    {
        groupTypeManagerDialog->setWindowTitle(QCoreApplication::translate("groupTypeManagerDialog", "Dialog", nullptr));
        remark_defaultType->setPlaceholderText(QCoreApplication::translate("groupTypeManagerDialog", "\345\241\253\345\206\231\347\261\273\345\236\213\350\257\264\346\230\216", nullptr));
        editFields_defaultType->setTitle(QCoreApplication::translate("groupTypeManagerDialog", "\347\274\226\350\276\221\345\255\227\346\256\265", nullptr));
        saveChange_defaultType->setText(QCoreApplication::translate("groupTypeManagerDialog", "\344\277\235\345\255\230\344\277\256\346\224\271", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(defaultType), QCoreApplication::translate("groupTypeManagerDialog", "\351\273\230\350\256\244\347\261\273\345\236\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(typeManager), QCoreApplication::translate("groupTypeManagerDialog", "\347\261\273\345\236\213\347\256\241\347\220\206", nullptr));
        confirm->setText(QCoreApplication::translate("groupTypeManagerDialog", "\347\241\256\345\256\232", nullptr));
        cancle->setText(QCoreApplication::translate("groupTypeManagerDialog", "\345\217\226\346\266\210", nullptr));
        remark_newType->setPlaceholderText(QCoreApplication::translate("groupTypeManagerDialog", "\345\241\253\345\206\231\347\261\273\345\236\213\350\257\264\346\230\216", nullptr));
        editFields_newType->setTitle(QCoreApplication::translate("groupTypeManagerDialog", "\347\274\226\350\276\221\345\255\227\346\256\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(newType), QCoreApplication::translate("groupTypeManagerDialog", "\346\226\260\345\273\272\347\261\273\345\236\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class groupTypeManagerDialog: public Ui_groupTypeManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPTYPEMANAGERDIALOG_H
