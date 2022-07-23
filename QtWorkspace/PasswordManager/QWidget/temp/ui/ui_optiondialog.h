/********************************************************************************
** Form generated from reading UI file 'optiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONDIALOG_H
#define UI_OPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optionDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *secure;
    QGroupBox *groupBox_3;
    QCheckBox *autoLock;
    QWidget *layoutWidget_1;
    QHBoxLayout *horizontalLayout;
    QLabel *autoLockThresholdLabel;
    QSpinBox *autoLockThreshold;
    QCheckBox *autoLock_4;
    QLineEdit *lineEdit;
    QGroupBox *groupBox_4;
    QCheckBox *autoHideItem;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *autoHideItemThresholdLabel;
    QSpinBox *autoHideItemThreshold;
    QLineEdit *lineEdit_2;
    QCheckBox *autoLock_5;
    QWidget *file;
    QGroupBox *groupBox;
    QListWidget *listWidget;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *fileTypeLabel;
    QComboBox *fileType;
    QCheckBox *autoLock_2;
    QCheckBox *autoLock_3;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *fileTypeLabel_2;
    QComboBox *fileType_2;
    QToolButton *toolButton;
    QWidget *tab;
    QFrame *frame;

    void setupUi(QDialog *optionDialog)
    {
        if (optionDialog->objectName().isEmpty())
            optionDialog->setObjectName(QString::fromUtf8("optionDialog"));
        optionDialog->resize(680, 510);
        tabWidget = new QTabWidget(optionDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 641, 441));
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setTabBarAutoHide(false);
        secure = new QWidget();
        secure->setObjectName(QString::fromUtf8("secure"));
        groupBox_3 = new QGroupBox(secure);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 301, 171));
        autoLock = new QCheckBox(groupBox_3);
        autoLock->setObjectName(QString::fromUtf8("autoLock"));
        autoLock->setGeometry(QRect(10, 30, 281, 21));
        layoutWidget_1 = new QWidget(groupBox_3);
        layoutWidget_1->setObjectName(QString::fromUtf8("layoutWidget_1"));
        layoutWidget_1->setGeometry(QRect(30, 60, 261, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget_1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        autoLockThresholdLabel = new QLabel(layoutWidget_1);
        autoLockThresholdLabel->setObjectName(QString::fromUtf8("autoLockThresholdLabel"));
        autoLockThresholdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(autoLockThresholdLabel);

        autoLockThreshold = new QSpinBox(layoutWidget_1);
        autoLockThreshold->setObjectName(QString::fromUtf8("autoLockThreshold"));

        horizontalLayout->addWidget(autoLockThreshold);

        autoLock_4 = new QCheckBox(groupBox_3);
        autoLock_4->setObjectName(QString::fromUtf8("autoLock_4"));
        autoLock_4->setGeometry(QRect(10, 100, 281, 24));
        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 130, 261, 25));
        groupBox_4 = new QGroupBox(secure);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(320, 10, 301, 171));
        autoHideItem = new QCheckBox(groupBox_4);
        autoHideItem->setObjectName(QString::fromUtf8("autoHideItem"));
        autoHideItem->setGeometry(QRect(10, 30, 252, 24));
        layoutWidget_2 = new QWidget(groupBox_4);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(31, 62, 251, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        autoHideItemThresholdLabel = new QLabel(layoutWidget_2);
        autoHideItemThresholdLabel->setObjectName(QString::fromUtf8("autoHideItemThresholdLabel"));
        autoHideItemThresholdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(autoHideItemThresholdLabel);

        autoHideItemThreshold = new QSpinBox(layoutWidget_2);
        autoHideItemThreshold->setObjectName(QString::fromUtf8("autoHideItemThreshold"));

        horizontalLayout_2->addWidget(autoHideItemThreshold);

        lineEdit_2 = new QLineEdit(groupBox_4);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(30, 130, 261, 25));
        autoLock_5 = new QCheckBox(groupBox_4);
        autoLock_5->setObjectName(QString::fromUtf8("autoLock_5"));
        autoLock_5->setGeometry(QRect(10, 100, 281, 24));
        tabWidget->addTab(secure, QString());
        file = new QWidget();
        file->setObjectName(QString::fromUtf8("file"));
        groupBox = new QGroupBox(file);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(340, 10, 306, 271));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 20, 291, 241));
        groupBox_2 = new QGroupBox(file);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 311, 271));
        layoutWidget_3 = new QWidget(groupBox_2);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 30, 257, 31));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        fileTypeLabel = new QLabel(layoutWidget_3);
        fileTypeLabel->setObjectName(QString::fromUtf8("fileTypeLabel"));
        fileTypeLabel->setMinimumSize(QSize(124, 0));
        fileTypeLabel->setMaximumSize(QSize(124, 16777215));
        fileTypeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(fileTypeLabel);

        fileType = new QComboBox(layoutWidget_3);
        fileType->setObjectName(QString::fromUtf8("fileType"));
        fileType->setMinimumSize(QSize(124, 0));
        fileType->setMaximumSize(QSize(124, 16777215));

        horizontalLayout_3->addWidget(fileType);

        autoLock_2 = new QCheckBox(groupBox_2);
        autoLock_2->setObjectName(QString::fromUtf8("autoLock_2"));
        autoLock_2->setGeometry(QRect(10, 110, 271, 24));
        autoLock_3 = new QCheckBox(groupBox_2);
        autoLock_3->setObjectName(QString::fromUtf8("autoLock_3"));
        autoLock_3->setGeometry(QRect(10, 140, 271, 24));
        layoutWidget_4 = new QWidget(groupBox_2);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 70, 291, 31));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        fileTypeLabel_2 = new QLabel(layoutWidget_4);
        fileTypeLabel_2->setObjectName(QString::fromUtf8("fileTypeLabel_2"));
        fileTypeLabel_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(fileTypeLabel_2);

        fileType_2 = new QComboBox(layoutWidget_4);
        fileType_2->setObjectName(QString::fromUtf8("fileType_2"));

        horizontalLayout_4->addWidget(fileType_2);

        toolButton = new QToolButton(layoutWidget_4);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout_4->addWidget(toolButton);

        tabWidget->addTab(file, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        frame = new QFrame(optionDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 661, 491));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        tabWidget->raise();

        retranslateUi(optionDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(optionDialog);
    } // setupUi

    void retranslateUi(QDialog *optionDialog)
    {
        optionDialog->setWindowTitle(QCoreApplication::translate("optionDialog", "Dialog", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("optionDialog", "\351\224\201\345\256\232\347\225\214\351\235\242", nullptr));
        autoLock->setText(QCoreApplication::translate("optionDialog", "\345\256\232\346\227\266\351\224\201\345\256\232\347\225\214\351\235\242\357\274\210\350\276\223\345\205\245\345\257\206\347\240\201\344\273\245\351\207\215\346\226\260\350\277\233\345\205\245\357\274\211", nullptr));
        autoLockThresholdLabel->setText(QCoreApplication::translate("optionDialog", "\350\207\252\345\212\250\351\224\201\345\256\232\347\225\214\351\235\242\351\230\210\345\200\274(min)", nullptr));
        autoLock_4->setText(QCoreApplication::translate("optionDialog", "\344\275\277\347\224\250\347\224\250\346\210\267\345\257\206\347\240\201\350\247\243\351\224\201", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("optionDialog", "\350\276\223\345\205\245\350\247\243\351\224\201\345\257\206\347\240\201", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("optionDialog", "\351\224\201\345\256\232\346\235\241\347\233\256", nullptr));
        autoHideItem->setText(QCoreApplication::translate("optionDialog", "\350\207\252\345\212\250\351\232\220\350\227\217\345\257\206\347\240\201\357\274\210\345\215\225\345\207\273\344\273\245\351\207\215\346\226\260\346\230\276\347\244\272\357\274\211", nullptr));
        autoHideItemThresholdLabel->setText(QCoreApplication::translate("optionDialog", "\350\207\252\345\212\250\351\232\220\350\227\217\345\257\206\347\240\201\351\230\210\345\200\274(min)", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("optionDialog", "\350\276\223\345\205\245\350\247\243\351\224\201\345\257\206\347\240\201", nullptr));
        autoLock_5->setText(QCoreApplication::translate("optionDialog", "\344\275\277\347\224\250\347\224\250\346\210\267\345\257\206\347\240\201\350\247\243\351\224\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(secure), QCoreApplication::translate("optionDialog", "\345\256\211\345\205\250", nullptr));
        groupBox->setTitle(QCoreApplication::translate("optionDialog", "\350\277\221\346\234\237\345\257\274\345\207\272\350\256\260\345\275\225", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("optionDialog", "\350\256\276\345\256\232", nullptr));
        fileTypeLabel->setText(QCoreApplication::translate("optionDialog", "\351\273\230\350\256\244\345\257\274\345\207\272\346\226\271\345\274\217", nullptr));
        autoLock_2->setText(QCoreApplication::translate("optionDialog", "\345\257\274\345\207\272\345\220\216\350\207\252\345\212\250\346\211\223\345\274\200\346\226\207\344\273\266\346\211\200\345\234\250\346\226\207\344\273\266\345\244\271", nullptr));
        autoLock_3->setText(QCoreApplication::translate("optionDialog", "\345\257\274\345\207\272\345\220\216\350\207\252\345\212\250\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        fileTypeLabel_2->setText(QCoreApplication::translate("optionDialog", "\351\273\230\350\256\244\345\257\274\345\207\272\350\267\257\345\276\204", nullptr));
        toolButton->setText(QCoreApplication::translate("optionDialog", "...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(file), QCoreApplication::translate("optionDialog", "\346\226\207\344\273\266", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("optionDialog", "\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optionDialog: public Ui_optionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONDIALOG_H
