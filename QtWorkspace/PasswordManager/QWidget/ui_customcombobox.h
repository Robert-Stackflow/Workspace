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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_customComboBox
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *mainLayout;
    QLabel *controllerLabel;
    QComboBox *controller;
    QPushButton *controllerJudge;

    void setupUi(QWidget *customComboBox)
    {
        if (customComboBox->objectName().isEmpty())
            customComboBox->setObjectName(QString::fromUtf8("customComboBox"));
        customComboBox->resize(300, 40);
        customComboBox->setMinimumSize(QSize(300, 40));
        customComboBox->setMaximumSize(QSize(300, 40));
        layoutWidget = new QWidget(customComboBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 301, 42));
        mainLayout = new QHBoxLayout(layoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        controllerLabel = new QLabel(layoutWidget);
        controllerLabel->setObjectName(QString::fromUtf8("controllerLabel"));
        controllerLabel->setMinimumSize(QSize(60, 40));
        controllerLabel->setMaximumSize(QSize(60, 40));
        controllerLabel->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(controllerLabel);

        controller = new QComboBox(layoutWidget);
        controller->setObjectName(QString::fromUtf8("controller"));
        controller->setMinimumSize(QSize(188, 30));
        controller->setMaximumSize(QSize(188, 30));

        mainLayout->addWidget(controller);

        controllerJudge = new QPushButton(layoutWidget);
        controllerJudge->setObjectName(QString::fromUtf8("controllerJudge"));
        controllerJudge->setMinimumSize(QSize(35, 35));
        controllerJudge->setMaximumSize(QSize(35, 35));

        mainLayout->addWidget(controllerJudge);


        retranslateUi(customComboBox);

        QMetaObject::connectSlotsByName(customComboBox);
    } // setupUi

    void retranslateUi(QWidget *customComboBox)
    {
        customComboBox->setWindowTitle(QCoreApplication::translate("customComboBox", "Form", nullptr));
        controllerLabel->setText(QString());
        controllerJudge->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class customComboBox: public Ui_customComboBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMCOMBOBOX_H
