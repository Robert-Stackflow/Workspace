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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_customLineEdit
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *mainLayout;
    QLabel *controllerLabel;
    QLineEdit *controller;
    QPushButton *controllerJudge;

    void setupUi(QWidget *customLineEdit)
    {
        if (customLineEdit->objectName().isEmpty())
            customLineEdit->setObjectName(QString::fromUtf8("customLineEdit"));
        customLineEdit->resize(320, 40);
        customLineEdit->setMinimumSize(QSize(320, 40));
        customLineEdit->setMaximumSize(QSize(320, 40));
        customLineEdit->setContextMenuPolicy(Qt::NoContextMenu);
        layoutWidget = new QWidget(customLineEdit);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 321, 42));
        mainLayout = new QHBoxLayout(layoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        controllerLabel = new QLabel(layoutWidget);
        controllerLabel->setObjectName(QString::fromUtf8("controllerLabel"));
        controllerLabel->setMinimumSize(QSize(80, 40));
        controllerLabel->setMaximumSize(QSize(80, 40));
        controllerLabel->setAlignment(Qt::AlignCenter);
        controllerLabel->setWordWrap(true);

        mainLayout->addWidget(controllerLabel);

        controller = new QLineEdit(layoutWidget);
        controller->setObjectName(QString::fromUtf8("controller"));
        controller->setMinimumSize(QSize(188, 30));
        controller->setMaximumSize(QSize(188, 30));

        mainLayout->addWidget(controller);

        controllerJudge = new QPushButton(layoutWidget);
        controllerJudge->setObjectName(QString::fromUtf8("controllerJudge"));
        controllerJudge->setMinimumSize(QSize(35, 35));
        controllerJudge->setMaximumSize(QSize(35, 35));

        mainLayout->addWidget(controllerJudge);


        retranslateUi(customLineEdit);

        QMetaObject::connectSlotsByName(customLineEdit);
    } // setupUi

    void retranslateUi(QWidget *customLineEdit)
    {
        customLineEdit->setWindowTitle(QString());
        controllerLabel->setText(QString());
        controllerJudge->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class customLineEdit: public Ui_customLineEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMLINEEDIT_H
