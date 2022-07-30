/********************************************************************************
** Form generated from reading UI file 'customdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMDIALOG_H
#define UI_CUSTOMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>

QT_BEGIN_NAMESPACE

class Ui_CustomDialog
{
public:
    QFrame *frame;

    void setupUi(QDialog *CustomDialog)
    {
        if (CustomDialog->objectName().isEmpty())
            CustomDialog->setObjectName(QString::fromUtf8("CustomDialog"));
        CustomDialog->resize(400, 300);
        frame = new QFrame(CustomDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 380, 280));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(CustomDialog);

        QMetaObject::connectSlotsByName(CustomDialog);
    } // setupUi

    void retranslateUi(QDialog *CustomDialog)
    {
        CustomDialog->setWindowTitle(QCoreApplication::translate("CustomDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomDialog: public Ui_CustomDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMDIALOG_H
