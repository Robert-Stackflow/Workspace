/********************************************************************************
** Form generated from reading UI file 'grouptypemanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPTYPEMANAGERDIALOG_H
#define UI_GROUPTYPEMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_groupTypeManagerDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *typeManager;
    QTableWidget *typeManagerTableWidget;
    QWidget *layoutWidget;
    QVBoxLayout *typeManagerButtonLayout;
    QPushButton *editTypeButton;
    QPushButton *deleteTypeButton;
    QPushButton *copyTypeButton;
    QPushButton *newTypeButton;
    QWidget *layoutWidget_1;
    QVBoxLayout *typeManagerChosenLayout;
    QLabel *chosenLabel;
    QLabel *chosen;
    QWidget *editType;
    QGroupBox *editFields;
    QTableWidget *editFieldsTableWidget;
    QWidget *layoutWidget_2;
    QHBoxLayout *addFieldLayout;
    QLabel *addFieldLabel;
    QComboBox *addFieldComboBox;
    QPushButton *addFieldButton;
    QWidget *layoutWidget_3;
    QVBoxLayout *addFieldNameLayout;
    QWidget *layoutWidget_4;
    QVBoxLayout *addFieldTipLayout;
    QWidget *layoutWidget_5;
    QHBoxLayout *confirmBoxLayout;
    QPushButton *confirm;
    QPushButton *cancel;
    QGroupBox *essentialInfo;
    QWidget *layoutWidget_6;
    QVBoxLayout *typeNameLayout;
    QTextEdit *remark;
    QFrame *frame;

    void setupUi(QDialog *groupTypeManagerDialog)
    {
        if (groupTypeManagerDialog->objectName().isEmpty())
            groupTypeManagerDialog->setObjectName(QString::fromUtf8("groupTypeManagerDialog"));
        groupTypeManagerDialog->resize(890, 700);
        groupTypeManagerDialog->setMinimumSize(QSize(890, 700));
        groupTypeManagerDialog->setMaximumSize(QSize(890, 700));
        tabWidget = new QTabWidget(groupTypeManagerDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 851, 631));
        QFont font;
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        typeManager = new QWidget();
        typeManager->setObjectName(QString::fromUtf8("typeManager"));
        typeManagerTableWidget = new QTableWidget(typeManager);
        typeManagerTableWidget->setObjectName(QString::fromUtf8("typeManagerTableWidget"));
        typeManagerTableWidget->setGeometry(QRect(10, 10, 651, 581));
        layoutWidget = new QWidget(typeManager);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(680, 100, 151, 301));
        typeManagerButtonLayout = new QVBoxLayout(layoutWidget);
        typeManagerButtonLayout->setObjectName(QString::fromUtf8("typeManagerButtonLayout"));
        typeManagerButtonLayout->setContentsMargins(0, 0, 0, 0);
        editTypeButton = new QPushButton(layoutWidget);
        editTypeButton->setObjectName(QString::fromUtf8("editTypeButton"));
        editTypeButton->setMinimumSize(QSize(0, 35));

        typeManagerButtonLayout->addWidget(editTypeButton);

        deleteTypeButton = new QPushButton(layoutWidget);
        deleteTypeButton->setObjectName(QString::fromUtf8("deleteTypeButton"));
        deleteTypeButton->setMinimumSize(QSize(0, 35));

        typeManagerButtonLayout->addWidget(deleteTypeButton);

        copyTypeButton = new QPushButton(layoutWidget);
        copyTypeButton->setObjectName(QString::fromUtf8("copyTypeButton"));
        copyTypeButton->setMinimumSize(QSize(0, 35));

        typeManagerButtonLayout->addWidget(copyTypeButton);

        newTypeButton = new QPushButton(layoutWidget);
        newTypeButton->setObjectName(QString::fromUtf8("newTypeButton"));
        newTypeButton->setMinimumSize(QSize(0, 35));

        typeManagerButtonLayout->addWidget(newTypeButton);

        layoutWidget_1 = new QWidget(typeManager);
        layoutWidget_1->setObjectName(QString::fromUtf8("layoutWidget_1"));
        layoutWidget_1->setGeometry(QRect(680, 20, 151, 61));
        typeManagerChosenLayout = new QVBoxLayout(layoutWidget_1);
        typeManagerChosenLayout->setObjectName(QString::fromUtf8("typeManagerChosenLayout"));
        typeManagerChosenLayout->setContentsMargins(0, 0, 0, 0);
        chosenLabel = new QLabel(layoutWidget_1);
        chosenLabel->setObjectName(QString::fromUtf8("chosenLabel"));
        chosenLabel->setAlignment(Qt::AlignCenter);

        typeManagerChosenLayout->addWidget(chosenLabel);

        chosen = new QLabel(layoutWidget_1);
        chosen->setObjectName(QString::fromUtf8("chosen"));
        chosen->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        chosen->setAlignment(Qt::AlignCenter);

        typeManagerChosenLayout->addWidget(chosen);

        tabWidget->addTab(typeManager, QString());
        editType = new QWidget();
        editType->setObjectName(QString::fromUtf8("editType"));
        editFields = new QGroupBox(editType);
        editFields->setObjectName(QString::fromUtf8("editFields"));
        editFields->setGeometry(QRect(10, 110, 821, 431));
        editFieldsTableWidget = new QTableWidget(editFields);
        editFieldsTableWidget->setObjectName(QString::fromUtf8("editFieldsTableWidget"));
        editFieldsTableWidget->setGeometry(QRect(10, 130, 801, 291));
        layoutWidget_2 = new QWidget(editFields);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 80, 381, 42));
        addFieldLayout = new QHBoxLayout(layoutWidget_2);
        addFieldLayout->setObjectName(QString::fromUtf8("addFieldLayout"));
        addFieldLayout->setContentsMargins(0, 0, 0, 0);
        addFieldLabel = new QLabel(layoutWidget_2);
        addFieldLabel->setObjectName(QString::fromUtf8("addFieldLabel"));
        addFieldLabel->setMinimumSize(QSize(65, 40));
        addFieldLabel->setMaximumSize(QSize(65, 40));
        addFieldLabel->setAlignment(Qt::AlignCenter);

        addFieldLayout->addWidget(addFieldLabel);

        addFieldComboBox = new QComboBox(layoutWidget_2);
        addFieldComboBox->setObjectName(QString::fromUtf8("addFieldComboBox"));
        addFieldComboBox->setMinimumSize(QSize(188, 30));
        addFieldComboBox->setMaximumSize(QSize(188, 30));

        addFieldLayout->addWidget(addFieldComboBox);

        addFieldButton = new QPushButton(layoutWidget_2);
        addFieldButton->setObjectName(QString::fromUtf8("addFieldButton"));
        addFieldButton->setMinimumSize(QSize(80, 35));
        addFieldButton->setMaximumSize(QSize(80, 35));

        addFieldLayout->addWidget(addFieldButton);

        layoutWidget_3 = new QWidget(editFields);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 30, 311, 41));
        addFieldNameLayout = new QVBoxLayout(layoutWidget_3);
        addFieldNameLayout->setObjectName(QString::fromUtf8("addFieldNameLayout"));
        addFieldNameLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget_4 = new QWidget(editFields);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(330, 30, 311, 41));
        addFieldTipLayout = new QVBoxLayout(layoutWidget_4);
        addFieldTipLayout->setObjectName(QString::fromUtf8("addFieldTipLayout"));
        addFieldTipLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget_5 = new QWidget(editType);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(630, 550, 195, 31));
        confirmBoxLayout = new QHBoxLayout(layoutWidget_5);
        confirmBoxLayout->setObjectName(QString::fromUtf8("confirmBoxLayout"));
        confirmBoxLayout->setContentsMargins(0, 0, 0, 0);
        confirm = new QPushButton(layoutWidget_5);
        confirm->setObjectName(QString::fromUtf8("confirm"));

        confirmBoxLayout->addWidget(confirm);

        cancel = new QPushButton(layoutWidget_5);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        confirmBoxLayout->addWidget(cancel);

        essentialInfo = new QGroupBox(editType);
        essentialInfo->setObjectName(QString::fromUtf8("essentialInfo"));
        essentialInfo->setGeometry(QRect(10, 10, 821, 91));
        layoutWidget_6 = new QWidget(essentialInfo);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 30, 311, 41));
        typeNameLayout = new QVBoxLayout(layoutWidget_6);
        typeNameLayout->setObjectName(QString::fromUtf8("typeNameLayout"));
        typeNameLayout->setContentsMargins(0, 0, 0, 0);
        remark = new QTextEdit(essentialInfo);
        remark->setObjectName(QString::fromUtf8("remark"));
        remark->setGeometry(QRect(330, 30, 481, 41));
        tabWidget->addTab(editType, QString());
        frame = new QFrame(groupTypeManagerDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 871, 681));
        frame->setStyleSheet(QString::fromUtf8("border:0px;\n"
"border-radius:10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        tabWidget->raise();

        retranslateUi(groupTypeManagerDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(groupTypeManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *groupTypeManagerDialog)
    {
        groupTypeManagerDialog->setWindowTitle(QCoreApplication::translate("groupTypeManagerDialog", "Dialog", nullptr));
        editTypeButton->setText(QCoreApplication::translate("groupTypeManagerDialog", "\347\274\226\350\276\221\347\261\273\345\236\213", nullptr));
        deleteTypeButton->setText(QCoreApplication::translate("groupTypeManagerDialog", "\345\210\240\351\231\244\347\261\273\345\236\213", nullptr));
        copyTypeButton->setText(QCoreApplication::translate("groupTypeManagerDialog", "\345\244\215\345\210\266\347\261\273\345\236\213", nullptr));
        newTypeButton->setText(QCoreApplication::translate("groupTypeManagerDialog", "\346\226\260\345\273\272\347\261\273\345\236\213", nullptr));
        chosenLabel->setText(QCoreApplication::translate("groupTypeManagerDialog", "\345\275\223\345\211\215\351\200\211\344\270\255\347\261\273\345\236\213", nullptr));
        chosen->setText(QCoreApplication::translate("groupTypeManagerDialog", "\346\234\252\351\200\211\344\270\255", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(typeManager), QCoreApplication::translate("groupTypeManagerDialog", "\347\261\273\345\236\213\347\256\241\347\220\206", nullptr));
        editFields->setTitle(QCoreApplication::translate("groupTypeManagerDialog", "\347\274\226\350\276\221\345\255\227\346\256\265", nullptr));
        addFieldLabel->setText(QCoreApplication::translate("groupTypeManagerDialog", "\345\255\227\346\256\265\347\261\273\345\236\213", nullptr));
        addFieldButton->setText(QCoreApplication::translate("groupTypeManagerDialog", "\346\267\273\345\212\240\345\255\227\346\256\265", nullptr));
        confirm->setText(QCoreApplication::translate("groupTypeManagerDialog", "\347\241\256\345\256\232", nullptr));
        cancel->setText(QCoreApplication::translate("groupTypeManagerDialog", "\345\217\226\346\266\210", nullptr));
        essentialInfo->setTitle(QCoreApplication::translate("groupTypeManagerDialog", "\345\237\272\346\234\254\344\277\241\346\201\257", nullptr));
        remark->setPlaceholderText(QCoreApplication::translate("groupTypeManagerDialog", "\347\274\226\350\276\221\347\261\273\345\236\213\350\257\264\346\230\216", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(editType), QCoreApplication::translate("groupTypeManagerDialog", "\347\274\226\350\276\221/\346\226\260\345\273\272\347\261\273\345\236\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class groupTypeManagerDialog: public Ui_groupTypeManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPTYPEMANAGERDIALOG_H
