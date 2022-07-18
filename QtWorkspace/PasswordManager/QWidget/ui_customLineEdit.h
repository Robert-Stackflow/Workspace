/********************************************************************************
** Form generated from reading UI file 'customLineEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMLINEEDIT_H
#define UI_CUSTOMLINEEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_customLineEdit
{
public:

    void setupUi(QWidget *customLineEdit)
    {
        if (customLineEdit->objectName().isEmpty())
            customLineEdit->setObjectName(QString::fromUtf8("customLineEdit"));
        customLineEdit->resize(400, 300);

        retranslateUi(customLineEdit);

        QMetaObject::connectSlotsByName(customLineEdit);
    } // setupUi

    void retranslateUi(QWidget *customLineEdit)
    {
        customLineEdit->setWindowTitle(QCoreApplication::translate("customLineEdit", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class customLineEdit: public Ui_customLineEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMLINEEDIT_H
