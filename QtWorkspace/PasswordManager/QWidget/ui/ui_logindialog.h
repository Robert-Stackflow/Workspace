/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginDialog
{
public:
    QPushButton *yes;
    QFrame *frame;
    QLabel *portrait;
    QWidget *layoutWidget_1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *usernameLabel;
    QComboBox *username;
    QPushButton *space;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passwordLabel;
    QLineEdit *password;
    QPushButton *passwordJudge;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *remember;
    QCheckBox *autoLogin;

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName(QString::fromUtf8("loginDialog"));
        loginDialog->resize(383, 524);
        yes = new QPushButton(loginDialog);
        yes->setObjectName(QString::fromUtf8("yes"));
        yes->setGeometry(QRect(70, 380, 241, 51));
        frame = new QFrame(loginDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 361, 501));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        portrait = new QLabel(frame);
        portrait->setObjectName(QString::fromUtf8("portrait"));
        portrait->setGeometry(QRect(130, 80, 100, 100));
        portrait->setAlignment(Qt::AlignCenter);
        layoutWidget_1 = new QWidget(frame);
        layoutWidget_1->setObjectName(QString::fromUtf8("layoutWidget_1"));
        layoutWidget_1->setGeometry(QRect(20, 230, 321, 91));
        verticalLayout = new QVBoxLayout(layoutWidget_1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        usernameLabel = new QLabel(layoutWidget_1);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        usernameLabel->setMinimumSize(QSize(70, 0));
        usernameLabel->setMaximumSize(QSize(70, 16777215));
        QFont font;
        usernameLabel->setFont(font);
        usernameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(usernameLabel);

        username = new QComboBox(layoutWidget_1);
        username->setObjectName(QString::fromUtf8("username"));

        horizontalLayout->addWidget(username);

        space = new QPushButton(layoutWidget_1);
        space->setObjectName(QString::fromUtf8("space"));
        space->setMinimumSize(QSize(35, 35));
        space->setMaximumSize(QSize(35, 35));

        horizontalLayout->addWidget(space);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        passwordLabel = new QLabel(layoutWidget_1);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setMinimumSize(QSize(70, 0));
        passwordLabel->setMaximumSize(QSize(70, 16777215));
        passwordLabel->setFont(font);
        passwordLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(passwordLabel);

        password = new QLineEdit(layoutWidget_1);
        password->setObjectName(QString::fromUtf8("password"));

        horizontalLayout_2->addWidget(password);

        passwordJudge = new QPushButton(layoutWidget_1);
        passwordJudge->setObjectName(QString::fromUtf8("passwordJudge"));
        passwordJudge->setMinimumSize(QSize(35, 35));
        passwordJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_2->addWidget(passwordJudge);


        verticalLayout->addLayout(horizontalLayout_2);

        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 450, 241, 31));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        remember = new QCheckBox(widget);
        remember->setObjectName(QString::fromUtf8("remember"));
        remember->setMaximumSize(QSize(100, 16777215));
        remember->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_3->addWidget(remember);

        autoLogin = new QCheckBox(widget);
        autoLogin->setObjectName(QString::fromUtf8("autoLogin"));
        autoLogin->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(autoLogin);

        frame->raise();
        yes->raise();

        retranslateUi(loginDialog);

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QCoreApplication::translate("loginDialog", "Dialog", nullptr));
        yes->setText(QCoreApplication::translate("loginDialog", "\347\231\273\345\275\225", nullptr));
        portrait->setText(QString());
        usernameLabel->setText(QCoreApplication::translate("loginDialog", "\347\224\250\346\210\267\345\220\215:", nullptr));
        space->setText(QString());
        passwordLabel->setText(QCoreApplication::translate("loginDialog", "\345\257\206\347\240\201:", nullptr));
        passwordJudge->setText(QString());
        remember->setText(QCoreApplication::translate("loginDialog", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        autoLogin->setText(QCoreApplication::translate("loginDialog", "\350\207\252\345\212\250\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
