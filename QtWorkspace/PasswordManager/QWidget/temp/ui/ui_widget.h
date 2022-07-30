/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QListWidget *listWidget;
    QVBoxLayout *rightLayout;
    QHBoxLayout *groupInfoLayout;
    QLabel *groupNameLabel;
    QLabel *groupDescribeLabel;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget;
    QHBoxLayout *bottomLayout;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *search;
    QPushButton *addGroup;
    QPushButton *deleteGroup;
    QPushButton *editGroup;
    QPushButton *addItem;
    QToolButton *save;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1200, 840);
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 60, 1181, 761));
        mainLayout = new QVBoxLayout(widget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        topLayout = new QHBoxLayout();
        topLayout->setObjectName(QString::fromUtf8("topLayout"));
        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setMaximumSize(QSize(200, 16777215));

        topLayout->addWidget(listWidget);

        rightLayout = new QVBoxLayout();
        rightLayout->setObjectName(QString::fromUtf8("rightLayout"));
        groupInfoLayout = new QHBoxLayout();
        groupInfoLayout->setObjectName(QString::fromUtf8("groupInfoLayout"));
        groupNameLabel = new QLabel(widget);
        groupNameLabel->setObjectName(QString::fromUtf8("groupNameLabel"));
        groupNameLabel->setMinimumSize(QSize(0, 50));
        groupNameLabel->setMaximumSize(QSize(16777215, 16777215));
        groupNameLabel->setBaseSize(QSize(200, 50));
        groupNameLabel->setScaledContents(true);

        groupInfoLayout->addWidget(groupNameLabel);

        groupDescribeLabel = new QLabel(widget);
        groupDescribeLabel->setObjectName(QString::fromUtf8("groupDescribeLabel"));
        groupDescribeLabel->setMinimumSize(QSize(500, 50));

        groupInfoLayout->addWidget(groupDescribeLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        groupInfoLayout->addItem(horizontalSpacer);


        rightLayout->addLayout(groupInfoLayout);

        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(1000, 620));
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);

        rightLayout->addWidget(tabWidget);


        topLayout->addLayout(rightLayout);


        mainLayout->addLayout(topLayout);

        bottomLayout = new QHBoxLayout();
        bottomLayout->setObjectName(QString::fromUtf8("bottomLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottomLayout->addItem(horizontalSpacer_2);

        search = new QLineEdit(widget);
        search->setObjectName(QString::fromUtf8("search"));
        search->setMinimumSize(QSize(0, 30));

        bottomLayout->addWidget(search);

        addGroup = new QPushButton(widget);
        addGroup->setObjectName(QString::fromUtf8("addGroup"));
        addGroup->setMinimumSize(QSize(80, 30));

        bottomLayout->addWidget(addGroup);

        deleteGroup = new QPushButton(widget);
        deleteGroup->setObjectName(QString::fromUtf8("deleteGroup"));
        deleteGroup->setMinimumSize(QSize(80, 30));

        bottomLayout->addWidget(deleteGroup);

        editGroup = new QPushButton(widget);
        editGroup->setObjectName(QString::fromUtf8("editGroup"));
        editGroup->setMinimumSize(QSize(80, 30));

        bottomLayout->addWidget(editGroup);

        addItem = new QPushButton(widget);
        addItem->setObjectName(QString::fromUtf8("addItem"));
        addItem->setMinimumSize(QSize(80, 30));

        bottomLayout->addWidget(addItem);

        save = new QToolButton(widget);
        save->setObjectName(QString::fromUtf8("save"));
        save->setMinimumSize(QSize(100, 30));
        save->setPopupMode(QToolButton::DelayedPopup);
        save->setToolButtonStyle(Qt::ToolButtonIconOnly);

        bottomLayout->addWidget(save);


        mainLayout->addLayout(bottomLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupNameLabel->setText(QString());
        groupDescribeLabel->setText(QString());
        addGroup->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        deleteGroup->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        editGroup->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        addItem->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        save->setText(QCoreApplication::translate("Widget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
