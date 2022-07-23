/********************************************************************************
** Form generated from reading UI file 'customTextEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMTEXTEDIT_H
#define UI_CUSTOMTEXTEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_customTextEdit
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *mainLayout;
    QLabel *controllerLabel;
    QTextEdit *controller;
    QPushButton *controllerJudge;

    void setupUi(QWidget *customTextEdit)
    {
        if (customTextEdit->objectName().isEmpty())
            customTextEdit->setObjectName(QString::fromUtf8("customTextEdit"));
        customTextEdit->resize(321, 201);
        customTextEdit->setMinimumSize(QSize(321, 201));
        customTextEdit->setMaximumSize(QSize(321, 201));
        layoutWidget = new QWidget(customTextEdit);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 321, 201));
        mainLayout = new QHBoxLayout(layoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        controllerLabel = new QLabel(layoutWidget);
        controllerLabel->setObjectName(QString::fromUtf8("controllerLabel"));
        controllerLabel->setMinimumSize(QSize(80, 40));
        controllerLabel->setMaximumSize(QSize(80, 40));
        controllerLabel->setAlignment(Qt::AlignCenter);
        controllerLabel->setWordWrap(true);

        mainLayout->addWidget(controllerLabel, 0, Qt::AlignTop);

        controller = new QTextEdit(layoutWidget);
        controller->setObjectName(QString::fromUtf8("controller"));

        mainLayout->addWidget(controller);

        controllerJudge = new QPushButton(layoutWidget);
        controllerJudge->setObjectName(QString::fromUtf8("controllerJudge"));
        controllerJudge->setMinimumSize(QSize(35, 35));
        controllerJudge->setMaximumSize(QSize(35, 35));

        mainLayout->addWidget(controllerJudge);


        retranslateUi(customTextEdit);

        QMetaObject::connectSlotsByName(customTextEdit);
    } // setupUi

    void retranslateUi(QWidget *customTextEdit)
    {
        customTextEdit->setWindowTitle(QCoreApplication::translate("customTextEdit", "Form", nullptr));
        controllerLabel->setText(QString());
        controllerJudge->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class customTextEdit: public Ui_customTextEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMTEXTEDIT_H
