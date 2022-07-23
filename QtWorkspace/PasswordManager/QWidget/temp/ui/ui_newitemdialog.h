/********************************************************************************
** Form generated from reading UI file 'newitemdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWITEMDIALOG_H
#define UI_NEWITEMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newItemDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *common;
    QWidget *layoutWidget;
    QHBoxLayout *confirmLayout;
    QPushButton *confirm;
    QPushButton *cancel;
    QGroupBox *infoGroupBox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *layoutWidget_1;
    QVBoxLayout *infoLayout;
    QGroupBox *groupBox;
    QTextEdit *tip;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *groupTypeNameLayout;
    QLabel *groupTypeNameLabel;
    QLabel *groupTypeName;
    QHBoxLayout *groupTypeCreateTimeLayout;
    QLabel *groupTypeCreateTimeLabel;
    QLabel *groupTypeCreateTime;
    QHBoxLayout *groupTypeLastEditTimeLayout;
    QLabel *groupTypeLastEditTimeLabel;
    QLabel *groupTypeLastEditTime;
    QFrame *frame;

    void setupUi(QDialog *newItemDialog)
    {
        if (newItemDialog->objectName().isEmpty())
            newItemDialog->setObjectName(QString::fromUtf8("newItemDialog"));
        newItemDialog->resize(680, 500);
        newItemDialog->setMinimumSize(QSize(680, 500));
        newItemDialog->setMaximumSize(QSize(680, 500));
        tabWidget = new QTabWidget(newItemDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 641, 431));
        QFont font;
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        common = new QWidget();
        common->setObjectName(QString::fromUtf8("common"));
        layoutWidget = new QWidget(common);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(430, 360, 195, 31));
        confirmLayout = new QHBoxLayout(layoutWidget);
        confirmLayout->setObjectName(QString::fromUtf8("confirmLayout"));
        confirmLayout->setContentsMargins(0, 0, 0, 0);
        confirm = new QPushButton(layoutWidget);
        confirm->setObjectName(QString::fromUtf8("confirm"));

        confirmLayout->addWidget(confirm);

        cancel = new QPushButton(layoutWidget);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        confirmLayout->addWidget(cancel);

        infoGroupBox = new QGroupBox(common);
        infoGroupBox->setObjectName(QString::fromUtf8("infoGroupBox"));
        infoGroupBox->setGeometry(QRect(10, 10, 371, 381));
        scrollArea = new QScrollArea(infoGroupBox);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 30, 351, 341));
        scrollArea->setStyleSheet(QString::fromUtf8(""));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 349, 339));
        layoutWidget_1 = new QWidget(scrollAreaWidgetContents);
        layoutWidget_1->setObjectName(QString::fromUtf8("layoutWidget_1"));
        layoutWidget_1->setGeometry(QRect(0, 0, 351, 341));
        infoLayout = new QVBoxLayout(layoutWidget_1);
        infoLayout->setObjectName(QString::fromUtf8("infoLayout"));
        infoLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);
        groupBox = new QGroupBox(common);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(390, 10, 231, 341));
        tip = new QTextEdit(groupBox);
        tip->setObjectName(QString::fromUtf8("tip"));
        tip->setGeometry(QRect(10, 210, 211, 121));
        tip->setFont(font);
        tip->setUndoRedoEnabled(false);
        tip->setReadOnly(true);
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 30, 211, 171));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupTypeNameLayout = new QHBoxLayout();
        groupTypeNameLayout->setObjectName(QString::fromUtf8("groupTypeNameLayout"));
        groupTypeNameLabel = new QLabel(layoutWidget_2);
        groupTypeNameLabel->setObjectName(QString::fromUtf8("groupTypeNameLabel"));
        groupTypeNameLabel->setAlignment(Qt::AlignCenter);

        groupTypeNameLayout->addWidget(groupTypeNameLabel);

        groupTypeName = new QLabel(layoutWidget_2);
        groupTypeName->setObjectName(QString::fromUtf8("groupTypeName"));
        groupTypeName->setWordWrap(true);

        groupTypeNameLayout->addWidget(groupTypeName);


        verticalLayout->addLayout(groupTypeNameLayout);

        groupTypeCreateTimeLayout = new QHBoxLayout();
        groupTypeCreateTimeLayout->setObjectName(QString::fromUtf8("groupTypeCreateTimeLayout"));
        groupTypeCreateTimeLabel = new QLabel(layoutWidget_2);
        groupTypeCreateTimeLabel->setObjectName(QString::fromUtf8("groupTypeCreateTimeLabel"));
        groupTypeCreateTimeLabel->setAlignment(Qt::AlignCenter);

        groupTypeCreateTimeLayout->addWidget(groupTypeCreateTimeLabel);

        groupTypeCreateTime = new QLabel(layoutWidget_2);
        groupTypeCreateTime->setObjectName(QString::fromUtf8("groupTypeCreateTime"));
        groupTypeCreateTime->setScaledContents(true);
        groupTypeCreateTime->setWordWrap(true);

        groupTypeCreateTimeLayout->addWidget(groupTypeCreateTime);


        verticalLayout->addLayout(groupTypeCreateTimeLayout);

        groupTypeLastEditTimeLayout = new QHBoxLayout();
        groupTypeLastEditTimeLayout->setObjectName(QString::fromUtf8("groupTypeLastEditTimeLayout"));
        groupTypeLastEditTimeLabel = new QLabel(layoutWidget_2);
        groupTypeLastEditTimeLabel->setObjectName(QString::fromUtf8("groupTypeLastEditTimeLabel"));
        groupTypeLastEditTimeLabel->setAlignment(Qt::AlignCenter);

        groupTypeLastEditTimeLayout->addWidget(groupTypeLastEditTimeLabel);

        groupTypeLastEditTime = new QLabel(layoutWidget_2);
        groupTypeLastEditTime->setObjectName(QString::fromUtf8("groupTypeLastEditTime"));
        groupTypeLastEditTime->setScaledContents(true);
        groupTypeLastEditTime->setWordWrap(true);

        groupTypeLastEditTimeLayout->addWidget(groupTypeLastEditTime);


        verticalLayout->addLayout(groupTypeLastEditTimeLayout);

        tabWidget->addTab(common, QString());
        layoutWidget->raise();
        groupBox->raise();
        infoGroupBox->raise();
        frame = new QFrame(newItemDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 661, 481));
        frame->setStyleSheet(QString::fromUtf8("border:0px;\n"
"border-radius:10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        tabWidget->raise();

        retranslateUi(newItemDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(newItemDialog);
    } // setupUi

    void retranslateUi(QDialog *newItemDialog)
    {
        newItemDialog->setWindowTitle(QCoreApplication::translate("newItemDialog", "Dialog", nullptr));
        confirm->setText(QCoreApplication::translate("newItemDialog", "\347\241\256\345\256\232", nullptr));
        cancel->setText(QCoreApplication::translate("newItemDialog", "\345\217\226\346\266\210", nullptr));
        infoGroupBox->setTitle(QCoreApplication::translate("newItemDialog", "\344\277\241\346\201\257\345\241\253\345\206\231", nullptr));
        groupBox->setTitle(QCoreApplication::translate("newItemDialog", "\345\257\206\347\240\201\347\261\273\345\236\213\344\277\241\346\201\257", nullptr));
        tip->setHtml(QCoreApplication::translate("newItemDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\257\206\347\240\201\347\261\273\345\236\213\350\257\264\346\230\216\357\274\232\346\255\244\347\261\273\345\236\213\345\257\206\347\240\201\347\224\250\344\272\216\346\224\257\346\214\201WebDav\347\255\211\347\275\221\347\273\234\345\255\230\345\202\250\346\226\207\344\273\266\345\205\261\344\272\253\346\234\215\345\212\241\347\232\204\350\264\246\345\217\267\344\270\255\344\270\272\345\272\224\347\224\250\345\274\200\345\220\257\347\232\204\346\216\210\346\235\203\345\257\206\347\240\201\343\200\202</p></body></html>", nullptr));
        tip->setPlaceholderText(QString());
        groupTypeNameLabel->setText(QCoreApplication::translate("newItemDialog", "\345\257\206\347\240\201\347\261\273\345\236\213\345\220\215\347\247\260:", nullptr));
        groupTypeName->setText(QString());
        groupTypeCreateTimeLabel->setText(QCoreApplication::translate("newItemDialog", "\347\261\273\345\236\213\345\210\233\345\273\272\346\227\266\351\227\264:", nullptr));
        groupTypeCreateTime->setText(QString());
        groupTypeLastEditTimeLabel->setText(QCoreApplication::translate("newItemDialog", "\347\261\273\345\236\213\344\277\256\346\224\271\346\227\266\351\227\264:", nullptr));
        groupTypeLastEditTime->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(common), QCoreApplication::translate("newItemDialog", "\351\273\230\350\256\244\347\261\273\345\236\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newItemDialog: public Ui_newItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWITEMDIALOG_H
