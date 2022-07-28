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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
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
    QGroupBox *groupBox_9;
    QTextEdit *textEdit;
    QWidget *file;
    QGroupBox *groupBox;
    QListWidget *listWidget;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *fileTypeLabel;
    QComboBox *fileType;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *fileTypeLabel_2;
    QComboBox *fileType_2;
    QToolButton *toolButton;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *fileTypeLabel_3;
    QComboBox *fileType_3;
    QWidget *tab;
    QGroupBox *groupBox_6;
    QGroupBox *groupBox_8;
    QWidget *tab_2;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *fileTypeLabel_4;
    QComboBox *fileType_4;
    QWidget *layoutWidget_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *fileTypeLabel_5;
    QComboBox *fileType_5;
    QToolButton *toolButton_2;
    QWidget *layoutWidget_8;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *autoLockThresholdLabel_2;
    QSpinBox *autoLockThreshold_2;
    QWidget *layoutWidget_9;
    QHBoxLayout *horizontalLayout_9;
    QLabel *autoLockThresholdLabel_3;
    QSpinBox *autoLockThreshold_3;
    QCheckBox *autoLock_2;
    QGroupBox *groupBox_5;
    QListWidget *listWidget_2;
    QFrame *frame;

    void setupUi(QDialog *optionDialog)
    {
        if (optionDialog->objectName().isEmpty())
            optionDialog->setObjectName(QString::fromUtf8("optionDialog"));
        optionDialog->resize(680, 500);
        optionDialog->setMinimumSize(QSize(680, 500));
        optionDialog->setMaximumSize(QSize(680, 500));
        tabWidget = new QTabWidget(optionDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 641, 431));
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setTabBarAutoHide(false);
        secure = new QWidget();
        secure->setObjectName(QString::fromUtf8("secure"));
        groupBox_3 = new QGroupBox(secure);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 10, 311, 381));
        autoLock = new QCheckBox(groupBox_3);
        autoLock->setObjectName(QString::fromUtf8("autoLock"));
        autoLock->setGeometry(QRect(10, 30, 291, 30));
        layoutWidget_1 = new QWidget(groupBox_3);
        layoutWidget_1->setObjectName(QString::fromUtf8("layoutWidget_1"));
        layoutWidget_1->setGeometry(QRect(30, 70, 261, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget_1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        autoLockThresholdLabel = new QLabel(layoutWidget_1);
        autoLockThresholdLabel->setObjectName(QString::fromUtf8("autoLockThresholdLabel"));
        autoLockThresholdLabel->setMinimumSize(QSize(0, 30));
        autoLockThresholdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(autoLockThresholdLabel);

        autoLockThreshold = new QSpinBox(layoutWidget_1);
        autoLockThreshold->setObjectName(QString::fromUtf8("autoLockThreshold"));
        autoLockThreshold->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(autoLockThreshold);

        autoLock_4 = new QCheckBox(groupBox_3);
        autoLock_4->setObjectName(QString::fromUtf8("autoLock_4"));
        autoLock_4->setGeometry(QRect(10, 110, 291, 30));
        autoLock_4->setMinimumSize(QSize(0, 30));
        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 150, 261, 30));
        lineEdit->setMinimumSize(QSize(0, 30));
        groupBox_9 = new QGroupBox(secure);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(320, 10, 311, 381));
        textEdit = new QTextEdit(groupBox_9);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 30, 291, 341));
        tabWidget->addTab(secure, QString());
        file = new QWidget();
        file->setObjectName(QString::fromUtf8("file"));
        groupBox = new QGroupBox(file);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(330, 10, 301, 381));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 30, 281, 341));
        groupBox_2 = new QGroupBox(file);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 10, 321, 381));
        layoutWidget_3 = new QWidget(groupBox_2);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 30, 257, 32));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        fileTypeLabel = new QLabel(layoutWidget_3);
        fileTypeLabel->setObjectName(QString::fromUtf8("fileTypeLabel"));
        fileTypeLabel->setMinimumSize(QSize(124, 30));
        fileTypeLabel->setMaximumSize(QSize(124, 16777215));
        fileTypeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(fileTypeLabel);

        fileType = new QComboBox(layoutWidget_3);
        fileType->setObjectName(QString::fromUtf8("fileType"));
        fileType->setMinimumSize(QSize(124, 30));
        fileType->setMaximumSize(QSize(124, 16777215));

        horizontalLayout_3->addWidget(fileType);

        layoutWidget_4 = new QWidget(groupBox_2);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 70, 291, 32));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        fileTypeLabel_2 = new QLabel(layoutWidget_4);
        fileTypeLabel_2->setObjectName(QString::fromUtf8("fileTypeLabel_2"));
        fileTypeLabel_2->setMinimumSize(QSize(0, 30));
        fileTypeLabel_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(fileTypeLabel_2);

        fileType_2 = new QComboBox(layoutWidget_4);
        fileType_2->setObjectName(QString::fromUtf8("fileType_2"));
        fileType_2->setMinimumSize(QSize(124, 30));

        horizontalLayout_4->addWidget(fileType_2);

        toolButton = new QToolButton(layoutWidget_4);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setMinimumSize(QSize(27, 27));
        toolButton->setMaximumSize(QSize(27, 27));

        horizontalLayout_4->addWidget(toolButton);

        layoutWidget_5 = new QWidget(groupBox_2);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(10, 110, 257, 32));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        fileTypeLabel_3 = new QLabel(layoutWidget_5);
        fileTypeLabel_3->setObjectName(QString::fromUtf8("fileTypeLabel_3"));
        fileTypeLabel_3->setMinimumSize(QSize(124, 30));
        fileTypeLabel_3->setMaximumSize(QSize(124, 16777215));
        fileTypeLabel_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(fileTypeLabel_3);

        fileType_3 = new QComboBox(layoutWidget_5);
        fileType_3->setObjectName(QString::fromUtf8("fileType_3"));
        fileType_3->setMinimumSize(QSize(124, 30));
        fileType_3->setMaximumSize(QSize(124, 16777215));

        horizontalLayout_5->addWidget(fileType_3);

        tabWidget->addTab(file, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 10, 321, 381));
        groupBox_8 = new QGroupBox(tab);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(330, 10, 301, 381));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 10, 321, 381));
        layoutWidget_6 = new QWidget(groupBox_4);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 70, 257, 32));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        fileTypeLabel_4 = new QLabel(layoutWidget_6);
        fileTypeLabel_4->setObjectName(QString::fromUtf8("fileTypeLabel_4"));
        fileTypeLabel_4->setMinimumSize(QSize(124, 30));
        fileTypeLabel_4->setMaximumSize(QSize(124, 16777215));
        fileTypeLabel_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(fileTypeLabel_4);

        fileType_4 = new QComboBox(layoutWidget_6);
        fileType_4->setObjectName(QString::fromUtf8("fileType_4"));
        fileType_4->setMinimumSize(QSize(124, 30));
        fileType_4->setMaximumSize(QSize(124, 16777215));

        horizontalLayout_6->addWidget(fileType_4);

        layoutWidget_7 = new QWidget(groupBox_4);
        layoutWidget_7->setObjectName(QString::fromUtf8("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(10, 110, 291, 32));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget_7);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        fileTypeLabel_5 = new QLabel(layoutWidget_7);
        fileTypeLabel_5->setObjectName(QString::fromUtf8("fileTypeLabel_5"));
        fileTypeLabel_5->setMinimumSize(QSize(0, 30));
        fileTypeLabel_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(fileTypeLabel_5);

        fileType_5 = new QComboBox(layoutWidget_7);
        fileType_5->setObjectName(QString::fromUtf8("fileType_5"));
        fileType_5->setMinimumSize(QSize(124, 30));

        horizontalLayout_7->addWidget(fileType_5);

        toolButton_2 = new QToolButton(layoutWidget_7);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setMinimumSize(QSize(27, 27));
        toolButton_2->setMaximumSize(QSize(27, 27));

        horizontalLayout_7->addWidget(toolButton_2);

        layoutWidget_8 = new QWidget(groupBox_4);
        layoutWidget_8->setObjectName(QString::fromUtf8("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(10, 30, 291, 32));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_8);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget_8);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 30));

        horizontalLayout_8->addWidget(pushButton);

        layoutWidget_2 = new QWidget(groupBox_4);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(30, 190, 261, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        autoLockThresholdLabel_2 = new QLabel(layoutWidget_2);
        autoLockThresholdLabel_2->setObjectName(QString::fromUtf8("autoLockThresholdLabel_2"));
        autoLockThresholdLabel_2->setMinimumSize(QSize(0, 30));
        autoLockThresholdLabel_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(autoLockThresholdLabel_2);

        autoLockThreshold_2 = new QSpinBox(layoutWidget_2);
        autoLockThreshold_2->setObjectName(QString::fromUtf8("autoLockThreshold_2"));
        autoLockThreshold_2->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(autoLockThreshold_2);

        layoutWidget_9 = new QWidget(groupBox_4);
        layoutWidget_9->setObjectName(QString::fromUtf8("layoutWidget_9"));
        layoutWidget_9->setGeometry(QRect(30, 230, 261, 32));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget_9);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        autoLockThresholdLabel_3 = new QLabel(layoutWidget_9);
        autoLockThresholdLabel_3->setObjectName(QString::fromUtf8("autoLockThresholdLabel_3"));
        autoLockThresholdLabel_3->setMinimumSize(QSize(0, 30));
        autoLockThresholdLabel_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(autoLockThresholdLabel_3);

        autoLockThreshold_3 = new QSpinBox(layoutWidget_9);
        autoLockThreshold_3->setObjectName(QString::fromUtf8("autoLockThreshold_3"));
        autoLockThreshold_3->setMinimumSize(QSize(0, 30));
        autoLockThreshold_3->setMinimum(1);
        autoLockThreshold_3->setMaximum(10);

        horizontalLayout_9->addWidget(autoLockThreshold_3);

        autoLock_2 = new QCheckBox(groupBox_4);
        autoLock_2->setObjectName(QString::fromUtf8("autoLock_2"));
        autoLock_2->setGeometry(QRect(10, 150, 291, 30));
        autoLock_2->setMinimumSize(QSize(0, 30));
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(330, 10, 301, 381));
        listWidget_2 = new QListWidget(groupBox_5);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(10, 30, 281, 341));
        tabWidget->addTab(tab_2, QString());
        frame = new QFrame(optionDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 661, 481));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        tabWidget->raise();

        retranslateUi(optionDialog);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(optionDialog);
    } // setupUi

    void retranslateUi(QDialog *optionDialog)
    {
        optionDialog->setWindowTitle(QCoreApplication::translate("optionDialog", "Dialog", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("optionDialog", "\345\256\211\345\205\250\351\224\201", nullptr));
        autoLock->setText(QCoreApplication::translate("optionDialog", "\346\211\223\345\274\200\345\256\211\345\205\250\351\224\201(\345\256\232\346\227\266\351\224\201\345\256\232\347\225\214\351\235\242)", nullptr));
        autoLockThresholdLabel->setText(QCoreApplication::translate("optionDialog", "\350\207\252\345\212\250\351\224\201\345\256\232\346\227\266\351\227\264\351\230\210\345\200\274(min)", nullptr));
        autoLock_4->setText(QCoreApplication::translate("optionDialog", "\344\275\277\347\224\250\347\224\250\346\210\267\345\257\206\347\240\201\350\247\243\351\224\201", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("optionDialog", "\350\276\223\345\205\245\345\256\211\345\205\250\351\224\201\350\247\243\351\224\201\345\257\206\347\240\201", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("optionDialog", "\346\225\260\346\215\256\345\272\223", nullptr));
        textEdit->setHtml(QCoreApplication::translate("optionDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\211\223\345\274\200\346\225\260\346\215\256\345\272\223\344\275\215\347\275\256</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\225\260\346\215\256\345\272\223\346\226\207\344\273\266\350\267\257\345\276\204</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\230\257\345\220\246\344\270\272\346\225\260\346\215\256\345\272\223\346\267\273\345\212\240\345\257\206"
                        "\347\240\201</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\344\275\277\347\224\250\347\224\250\346\210\267\345\257\206\347\240\201</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\344\275\277\347\224\250\351\273\230\350\256\244\345\257\206\347\240\201</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\207\252\345\256\232\344\271\211\345\257\206\347\240\201</p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(secure), QCoreApplication::translate("optionDialog", "\345\256\211\345\205\250", nullptr));
        groupBox->setTitle(QCoreApplication::translate("optionDialog", "\345\257\274\345\207\272\350\256\260\345\275\225", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("optionDialog", "\350\256\276\347\275\256", nullptr));
        fileTypeLabel->setText(QCoreApplication::translate("optionDialog", "\351\273\230\350\256\244\345\257\274\345\207\272\346\226\271\345\274\217", nullptr));
        fileTypeLabel_2->setText(QCoreApplication::translate("optionDialog", "\351\273\230\350\256\244\345\257\274\345\207\272\350\267\257\345\276\204", nullptr));
        toolButton->setText(QCoreApplication::translate("optionDialog", "...", nullptr));
        fileTypeLabel_3->setText(QCoreApplication::translate("optionDialog", "\345\257\274\345\207\272\345\256\214\346\210\220\345\220\216\346\223\215\344\275\234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(file), QCoreApplication::translate("optionDialog", "\345\257\274\345\207\272", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("optionDialog", "\344\270\273\351\242\230\344\270\216\351\205\215\350\211\262", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("optionDialog", "\346\211\230\347\233\230\344\270\216\345\233\276\346\240\207", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("optionDialog", "\350\247\206\345\233\276", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("optionDialog", "\350\256\276\347\275\256", nullptr));
        fileTypeLabel_4->setText(QCoreApplication::translate("optionDialog", "\346\227\245\345\277\227\350\256\260\345\275\225\347\255\211\347\272\247", nullptr));
        fileTypeLabel_5->setText(QCoreApplication::translate("optionDialog", "\346\227\245\345\277\227\345\255\230\345\202\250\350\267\257\345\276\204", nullptr));
        toolButton_2->setText(QCoreApplication::translate("optionDialog", "...", nullptr));
        pushButton->setText(QCoreApplication::translate("optionDialog", "\346\211\223\345\274\200\346\227\245\345\277\227", nullptr));
        autoLockThresholdLabel_2->setText(QCoreApplication::translate("optionDialog", "\346\227\245\345\277\227\345\256\271\351\207\217\351\230\210\345\200\274(KB)", nullptr));
        autoLockThresholdLabel_3->setText(QCoreApplication::translate("optionDialog", "\346\227\247\346\227\245\345\277\227(\345\244\207\344\273\275)\344\270\252\346\225\260", nullptr));
        autoLock_2->setText(QCoreApplication::translate("optionDialog", "\345\220\257\347\224\250\346\227\245\345\277\227\346\226\207\344\273\266\345\210\206\345\211\262", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("optionDialog", "\346\227\245\345\277\227\351\242\204\350\247\210", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("optionDialog", "\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optionDialog: public Ui_optionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONDIALOG_H
