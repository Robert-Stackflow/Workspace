/********************************************************************************
** Form generated from reading UI file 'groupbox.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPBOX_H
#define UI_GROUPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>

QT_BEGIN_NAMESPACE

class Ui_GroupBox
{
public:

    void setupUi(QGroupBox *GroupBox)
    {
        if (GroupBox->objectName().isEmpty())
            GroupBox->setObjectName(QString::fromUtf8("GroupBox"));
        GroupBox->resize(400, 300);

        retranslateUi(GroupBox);

        QMetaObject::connectSlotsByName(GroupBox);
    } // setupUi

    void retranslateUi(QGroupBox *GroupBox)
    {
        GroupBox->setWindowTitle(QCoreApplication::translate("GroupBox", "GroupBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupBox: public Ui_GroupBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPBOX_H
