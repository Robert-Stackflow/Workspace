/********************************************************************************
** Form generated from reading UI file 'customComboBox.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMCOMBOBOX_H
#define UI_CUSTOMCOMBOBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_customComboBox
{
public:

    void setupUi(QWidget *customComboBox)
    {
        if (customComboBox->objectName().isEmpty())
            customComboBox->setObjectName(QString::fromUtf8("customComboBox"));
        customComboBox->resize(400, 300);

        retranslateUi(customComboBox);

        QMetaObject::connectSlotsByName(customComboBox);
    } // setupUi

    void retranslateUi(QWidget *customComboBox)
    {
        customComboBox->setWindowTitle(QCoreApplication::translate("customComboBox", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class customComboBox: public Ui_customComboBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMCOMBOBOX_H
