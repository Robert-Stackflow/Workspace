/********************************************************************************
** Form generated from reading UI file 'additemdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITEMDIALOG_H
#define UI_ADDITEMDIALOG_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addItemDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *common;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *yes;
    QPushButton *no;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *nameLabel;
    QLineEdit *name;
    QPushButton *space_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *nickNameLabel;
    QLineEdit *nickName;
    QPushButton *space_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *idLabel;
    QLineEdit *id;
    QPushButton *space_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *passwordLabel;
    QLineEdit *password;
    QPushButton *passwordJudge;
    QHBoxLayout *horizontalLayout_5;
    QLabel *mobileLabel;
    QComboBox *mobile;
    QPushButton *mobileJudge;
    QHBoxLayout *horizontalLayout_6;
    QLabel *mailLabel;
    QComboBox *mail;
    QPushButton *mailJudge;
    QHBoxLayout *horizontalLayout_7;
    QLabel *websiteLabel;
    QLineEdit *website;
    QPushButton *websiteJudge;
    QTextEdit *remark;
    QGroupBox *groupBox;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *wechat;
    QCheckBox *qq;
    QCheckBox *weibo;
    QCheckBox *github;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *alipay;
    QCheckBox *huawei;
    QCheckBox *xiaomi;
    QCheckBox *taobao;
    QWidget *mailKey;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *mail_nameLabel;
    QLineEdit *mail_name;
    QPushButton *space;
    QHBoxLayout *horizontalLayout_16;
    QLabel *mail_mailLabel;
    QComboBox *mail_mail;
    QPushButton *mail_mailJudge;
    QHBoxLayout *horizontalLayout_19;
    QLabel *mail_subNameLabel;
    QLineEdit *mail_subName;
    QPushButton *mail_subNameJudge;
    QHBoxLayout *horizontalLayout_14;
    QLabel *mail_passwordLabel;
    QLineEdit *mail_password;
    QPushButton *mail_passwordJudge;
    QHBoxLayout *horizontalLayout_17;
    QLabel *mail_websiteLabel;
    QComboBox *mail_website;
    QPushButton *mail_websiteJudge;
    QTextEdit *mail_remark;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *mail_yes;
    QPushButton *mail_no;
    QWidget *jianguoyun;
    QWidget *layoutWidget_6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QLabel *jgy_nameLabel;
    QLineEdit *jgy_name;
    QPushButton *space_5;
    QHBoxLayout *horizontalLayout_23;
    QLabel *jgy_mailLabel;
    QComboBox *jgy_mail;
    QPushButton *jgy_mailJudge;
    QHBoxLayout *horizontalLayout_24;
    QLabel *jgy_websiteLabel;
    QComboBox *jgy_website;
    QPushButton *jgy_websiteJudge;
    QHBoxLayout *horizontalLayout_21;
    QLabel *jgy_passwordLabel;
    QLineEdit *jgy_password;
    QPushButton *jgy_passwordJudge;
    QWidget *layoutWidget_7;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *jgy_yes;
    QPushButton *jgy_no;
    QTextEdit *jgy_remark;
    QTextEdit *jgy_tip;
    QWidget *other;
    QWidget *layoutWidget_8;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_20;
    QLabel *other_nameLabel;
    QLineEdit *other_name;
    QPushButton *space_6;
    QHBoxLayout *horizontalLayout_22;
    QLabel *other_passwordLabel;
    QLineEdit *other_password;
    QPushButton *other_passwordJudge;
    QWidget *layoutWidget_9;
    QHBoxLayout *horizontalLayout_29;
    QPushButton *other_yes;
    QPushButton *other_no;
    QTextEdit *other_remark;
    QWidget *newGroup;
    QWidget *layoutWidget_10;
    QHBoxLayout *horizontalLayout_30;
    QPushButton *group_yes;
    QPushButton *group_no;
    QTextEdit *group_remark;
    QWidget *layoutWidget_11;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *groupNameLabel;
    QLineEdit *groupName;
    QPushButton *groupNameJudge;
    QHBoxLayout *horizontalLayout_53;
    QLabel *groupNameWarning;
    QPushButton *space_15;
    QHBoxLayout *horizontalLayout_18;
    QLabel *groupTypeLabel;
    QComboBox *groupType;
    QPushButton *space_7;
    QFrame *frame;

    void setupUi(QDialog *addItemDialog)
    {
        if (addItemDialog->objectName().isEmpty())
            addItemDialog->setObjectName(QString::fromUtf8("addItemDialog"));
        addItemDialog->resize(680, 510);
        addItemDialog->setMinimumSize(QSize(680, 510));
        addItemDialog->setMaximumSize(QSize(680, 510));
        tabWidget = new QTabWidget(addItemDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 50, 641, 441));
        QFont font;
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        common = new QWidget();
        common->setObjectName(QString::fromUtf8("common"));
        layoutWidget = new QWidget(common);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(420, 360, 195, 31));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        yes = new QPushButton(layoutWidget);
        yes->setObjectName(QString::fromUtf8("yes"));

        horizontalLayout_10->addWidget(yes);

        no = new QPushButton(layoutWidget);
        no->setObjectName(QString::fromUtf8("no"));

        horizontalLayout_10->addWidget(no);

        groupBox_2 = new QGroupBox(common);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 321, 381));
        layoutWidget_1 = new QWidget(groupBox_2);
        layoutWidget_1->setObjectName(QString::fromUtf8("layoutWidget_1"));
        layoutWidget_1->setGeometry(QRect(10, 30, 301, 341));
        verticalLayout = new QVBoxLayout(layoutWidget_1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        nameLabel = new QLabel(layoutWidget_1);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setMinimumSize(QSize(60, 0));
        nameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(nameLabel);

        name = new QLineEdit(layoutWidget_1);
        name->setObjectName(QString::fromUtf8("name"));
        name->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(name);

        space_2 = new QPushButton(layoutWidget_1);
        space_2->setObjectName(QString::fromUtf8("space_2"));
        space_2->setMinimumSize(QSize(35, 35));
        space_2->setMaximumSize(QSize(35, 35));
        space_2->setStyleSheet(QString::fromUtf8("border:0px;background-color:transparent"));

        horizontalLayout->addWidget(space_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        nickNameLabel = new QLabel(layoutWidget_1);
        nickNameLabel->setObjectName(QString::fromUtf8("nickNameLabel"));
        nickNameLabel->setMinimumSize(QSize(60, 0));
        nickNameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(nickNameLabel);

        nickName = new QLineEdit(layoutWidget_1);
        nickName->setObjectName(QString::fromUtf8("nickName"));
        nickName->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(nickName);

        space_3 = new QPushButton(layoutWidget_1);
        space_3->setObjectName(QString::fromUtf8("space_3"));
        space_3->setMinimumSize(QSize(35, 35));
        space_3->setMaximumSize(QSize(35, 35));
        space_3->setStyleSheet(QString::fromUtf8("border:0px;background-color:transparent"));

        horizontalLayout_2->addWidget(space_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        idLabel = new QLabel(layoutWidget_1);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));
        idLabel->setMinimumSize(QSize(60, 0));
        idLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(idLabel);

        id = new QLineEdit(layoutWidget_1);
        id->setObjectName(QString::fromUtf8("id"));
        id->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(id);

        space_4 = new QPushButton(layoutWidget_1);
        space_4->setObjectName(QString::fromUtf8("space_4"));
        space_4->setMinimumSize(QSize(35, 35));
        space_4->setMaximumSize(QSize(35, 35));
        space_4->setStyleSheet(QString::fromUtf8("border:0px;background-color:transparent"));

        horizontalLayout_3->addWidget(space_4);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        passwordLabel = new QLabel(layoutWidget_1);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setMinimumSize(QSize(60, 0));
        passwordLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(passwordLabel);

        password = new QLineEdit(layoutWidget_1);
        password->setObjectName(QString::fromUtf8("password"));
        password->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(password);

        passwordJudge = new QPushButton(layoutWidget_1);
        passwordJudge->setObjectName(QString::fromUtf8("passwordJudge"));
        passwordJudge->setMinimumSize(QSize(35, 35));
        passwordJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_4->addWidget(passwordJudge);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        mobileLabel = new QLabel(layoutWidget_1);
        mobileLabel->setObjectName(QString::fromUtf8("mobileLabel"));
        mobileLabel->setMinimumSize(QSize(60, 0));
        mobileLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(mobileLabel);

        mobile = new QComboBox(layoutWidget_1);
        mobile->setObjectName(QString::fromUtf8("mobile"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mobile->sizePolicy().hasHeightForWidth());
        mobile->setSizePolicy(sizePolicy);
        mobile->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(mobile);

        mobileJudge = new QPushButton(layoutWidget_1);
        mobileJudge->setObjectName(QString::fromUtf8("mobileJudge"));
        mobileJudge->setMinimumSize(QSize(35, 35));
        mobileJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_5->addWidget(mobileJudge);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        mailLabel = new QLabel(layoutWidget_1);
        mailLabel->setObjectName(QString::fromUtf8("mailLabel"));
        mailLabel->setMinimumSize(QSize(60, 0));
        mailLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(mailLabel);

        mail = new QComboBox(layoutWidget_1);
        mail->setObjectName(QString::fromUtf8("mail"));
        sizePolicy.setHeightForWidth(mail->sizePolicy().hasHeightForWidth());
        mail->setSizePolicy(sizePolicy);
        mail->setMinimumSize(QSize(0, 30));

        horizontalLayout_6->addWidget(mail);

        mailJudge = new QPushButton(layoutWidget_1);
        mailJudge->setObjectName(QString::fromUtf8("mailJudge"));
        mailJudge->setMinimumSize(QSize(35, 35));
        mailJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_6->addWidget(mailJudge);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        websiteLabel = new QLabel(layoutWidget_1);
        websiteLabel->setObjectName(QString::fromUtf8("websiteLabel"));
        websiteLabel->setMinimumSize(QSize(60, 0));
        websiteLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(websiteLabel);

        website = new QLineEdit(layoutWidget_1);
        website->setObjectName(QString::fromUtf8("website"));
        website->setMinimumSize(QSize(0, 30));

        horizontalLayout_7->addWidget(website);

        websiteJudge = new QPushButton(layoutWidget_1);
        websiteJudge->setObjectName(QString::fromUtf8("websiteJudge"));
        websiteJudge->setMinimumSize(QSize(35, 35));
        websiteJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_7->addWidget(websiteJudge);


        verticalLayout->addLayout(horizontalLayout_7);

        remark = new QTextEdit(common);
        remark->setObjectName(QString::fromUtf8("remark"));
        remark->setGeometry(QRect(350, 180, 271, 171));
        groupBox = new QGroupBox(common);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(350, 10, 271, 161));
        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(20, 30, 231, 121));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        wechat = new QCheckBox(layoutWidget_2);
        wechat->setObjectName(QString::fromUtf8("wechat"));

        verticalLayout_2->addWidget(wechat);

        qq = new QCheckBox(layoutWidget_2);
        qq->setObjectName(QString::fromUtf8("qq"));

        verticalLayout_2->addWidget(qq);

        weibo = new QCheckBox(layoutWidget_2);
        weibo->setObjectName(QString::fromUtf8("weibo"));

        verticalLayout_2->addWidget(weibo);

        github = new QCheckBox(layoutWidget_2);
        github->setObjectName(QString::fromUtf8("github"));

        verticalLayout_2->addWidget(github);


        horizontalLayout_11->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        alipay = new QCheckBox(layoutWidget_2);
        alipay->setObjectName(QString::fromUtf8("alipay"));

        verticalLayout_3->addWidget(alipay);

        huawei = new QCheckBox(layoutWidget_2);
        huawei->setObjectName(QString::fromUtf8("huawei"));

        verticalLayout_3->addWidget(huawei);

        xiaomi = new QCheckBox(layoutWidget_2);
        xiaomi->setObjectName(QString::fromUtf8("xiaomi"));

        verticalLayout_3->addWidget(xiaomi);

        taobao = new QCheckBox(layoutWidget_2);
        taobao->setObjectName(QString::fromUtf8("taobao"));

        verticalLayout_3->addWidget(taobao);


        horizontalLayout_11->addLayout(verticalLayout_3);

        tabWidget->addTab(common, QString());
        mailKey = new QWidget();
        mailKey->setObjectName(QString::fromUtf8("mailKey"));
        layoutWidget_3 = new QWidget(mailKey);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(30, 20, 311, 251));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        mail_nameLabel = new QLabel(layoutWidget_3);
        mail_nameLabel->setObjectName(QString::fromUtf8("mail_nameLabel"));
        mail_nameLabel->setMinimumSize(QSize(60, 0));
        mail_nameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(mail_nameLabel);

        mail_name = new QLineEdit(layoutWidget_3);
        mail_name->setObjectName(QString::fromUtf8("mail_name"));
        mail_name->setMinimumSize(QSize(0, 30));

        horizontalLayout_9->addWidget(mail_name);

        space = new QPushButton(layoutWidget_3);
        space->setObjectName(QString::fromUtf8("space"));
        space->setMinimumSize(QSize(35, 35));
        space->setMaximumSize(QSize(35, 35));
        space->setStyleSheet(QString::fromUtf8("border:0px;background-color:transparent"));

        horizontalLayout_9->addWidget(space);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        mail_mailLabel = new QLabel(layoutWidget_3);
        mail_mailLabel->setObjectName(QString::fromUtf8("mail_mailLabel"));
        mail_mailLabel->setMinimumSize(QSize(60, 0));
        mail_mailLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(mail_mailLabel);

        mail_mail = new QComboBox(layoutWidget_3);
        mail_mail->setObjectName(QString::fromUtf8("mail_mail"));
        sizePolicy.setHeightForWidth(mail_mail->sizePolicy().hasHeightForWidth());
        mail_mail->setSizePolicy(sizePolicy);
        mail_mail->setMinimumSize(QSize(0, 30));

        horizontalLayout_16->addWidget(mail_mail);

        mail_mailJudge = new QPushButton(layoutWidget_3);
        mail_mailJudge->setObjectName(QString::fromUtf8("mail_mailJudge"));
        mail_mailJudge->setMinimumSize(QSize(35, 35));
        mail_mailJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_16->addWidget(mail_mailJudge);


        verticalLayout_4->addLayout(horizontalLayout_16);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        mail_subNameLabel = new QLabel(layoutWidget_3);
        mail_subNameLabel->setObjectName(QString::fromUtf8("mail_subNameLabel"));
        mail_subNameLabel->setMinimumSize(QSize(60, 0));
        mail_subNameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_19->addWidget(mail_subNameLabel);

        mail_subName = new QLineEdit(layoutWidget_3);
        mail_subName->setObjectName(QString::fromUtf8("mail_subName"));
        mail_subName->setMinimumSize(QSize(0, 30));

        horizontalLayout_19->addWidget(mail_subName);

        mail_subNameJudge = new QPushButton(layoutWidget_3);
        mail_subNameJudge->setObjectName(QString::fromUtf8("mail_subNameJudge"));
        mail_subNameJudge->setMinimumSize(QSize(35, 35));
        mail_subNameJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_19->addWidget(mail_subNameJudge);


        verticalLayout_4->addLayout(horizontalLayout_19);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        mail_passwordLabel = new QLabel(layoutWidget_3);
        mail_passwordLabel->setObjectName(QString::fromUtf8("mail_passwordLabel"));
        mail_passwordLabel->setMinimumSize(QSize(60, 0));
        mail_passwordLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(mail_passwordLabel);

        mail_password = new QLineEdit(layoutWidget_3);
        mail_password->setObjectName(QString::fromUtf8("mail_password"));
        mail_password->setMinimumSize(QSize(0, 30));

        horizontalLayout_14->addWidget(mail_password);

        mail_passwordJudge = new QPushButton(layoutWidget_3);
        mail_passwordJudge->setObjectName(QString::fromUtf8("mail_passwordJudge"));
        mail_passwordJudge->setMinimumSize(QSize(35, 35));
        mail_passwordJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_14->addWidget(mail_passwordJudge);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        mail_websiteLabel = new QLabel(layoutWidget_3);
        mail_websiteLabel->setObjectName(QString::fromUtf8("mail_websiteLabel"));
        mail_websiteLabel->setMinimumSize(QSize(60, 0));
        mail_websiteLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(mail_websiteLabel);

        mail_website = new QComboBox(layoutWidget_3);
        mail_website->setObjectName(QString::fromUtf8("mail_website"));
        sizePolicy.setHeightForWidth(mail_website->sizePolicy().hasHeightForWidth());
        mail_website->setSizePolicy(sizePolicy);
        mail_website->setMinimumSize(QSize(0, 30));

        horizontalLayout_17->addWidget(mail_website);

        mail_websiteJudge = new QPushButton(layoutWidget_3);
        mail_websiteJudge->setObjectName(QString::fromUtf8("mail_websiteJudge"));
        mail_websiteJudge->setMinimumSize(QSize(35, 35));
        mail_websiteJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_17->addWidget(mail_websiteJudge);


        verticalLayout_4->addLayout(horizontalLayout_17);

        mail_remark = new QTextEdit(mailKey);
        mail_remark->setObjectName(QString::fromUtf8("mail_remark"));
        mail_remark->setGeometry(QRect(360, 20, 261, 331));
        layoutWidget_5 = new QWidget(mailKey);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(420, 360, 195, 31));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        mail_yes = new QPushButton(layoutWidget_5);
        mail_yes->setObjectName(QString::fromUtf8("mail_yes"));

        horizontalLayout_12->addWidget(mail_yes);

        mail_no = new QPushButton(layoutWidget_5);
        mail_no->setObjectName(QString::fromUtf8("mail_no"));

        horizontalLayout_12->addWidget(mail_no);

        tabWidget->addTab(mailKey, QString());
        jianguoyun = new QWidget();
        jianguoyun->setObjectName(QString::fromUtf8("jianguoyun"));
        layoutWidget_6 = new QWidget(jianguoyun);
        layoutWidget_6->setObjectName(QString::fromUtf8("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(30, 20, 311, 201));
        verticalLayout_5 = new QVBoxLayout(layoutWidget_6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        jgy_nameLabel = new QLabel(layoutWidget_6);
        jgy_nameLabel->setObjectName(QString::fromUtf8("jgy_nameLabel"));
        jgy_nameLabel->setMinimumSize(QSize(60, 0));
        jgy_nameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(jgy_nameLabel);

        jgy_name = new QLineEdit(layoutWidget_6);
        jgy_name->setObjectName(QString::fromUtf8("jgy_name"));
        jgy_name->setMinimumSize(QSize(0, 30));

        horizontalLayout_13->addWidget(jgy_name);

        space_5 = new QPushButton(layoutWidget_6);
        space_5->setObjectName(QString::fromUtf8("space_5"));
        space_5->setMinimumSize(QSize(35, 35));
        space_5->setMaximumSize(QSize(35, 35));
        space_5->setStyleSheet(QString::fromUtf8("border:0px;background-color:transparent"));

        horizontalLayout_13->addWidget(space_5);


        verticalLayout_5->addLayout(horizontalLayout_13);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        jgy_mailLabel = new QLabel(layoutWidget_6);
        jgy_mailLabel->setObjectName(QString::fromUtf8("jgy_mailLabel"));
        jgy_mailLabel->setMinimumSize(QSize(60, 0));
        jgy_mailLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_23->addWidget(jgy_mailLabel);

        jgy_mail = new QComboBox(layoutWidget_6);
        jgy_mail->setObjectName(QString::fromUtf8("jgy_mail"));
        sizePolicy.setHeightForWidth(jgy_mail->sizePolicy().hasHeightForWidth());
        jgy_mail->setSizePolicy(sizePolicy);
        jgy_mail->setMinimumSize(QSize(0, 30));

        horizontalLayout_23->addWidget(jgy_mail);

        jgy_mailJudge = new QPushButton(layoutWidget_6);
        jgy_mailJudge->setObjectName(QString::fromUtf8("jgy_mailJudge"));
        jgy_mailJudge->setMinimumSize(QSize(35, 35));
        jgy_mailJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_23->addWidget(jgy_mailJudge);


        verticalLayout_5->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        jgy_websiteLabel = new QLabel(layoutWidget_6);
        jgy_websiteLabel->setObjectName(QString::fromUtf8("jgy_websiteLabel"));
        jgy_websiteLabel->setMinimumSize(QSize(60, 0));
        jgy_websiteLabel->setMaximumSize(QSize(60, 16777215));
        jgy_websiteLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_24->addWidget(jgy_websiteLabel);

        jgy_website = new QComboBox(layoutWidget_6);
        jgy_website->setObjectName(QString::fromUtf8("jgy_website"));
        sizePolicy.setHeightForWidth(jgy_website->sizePolicy().hasHeightForWidth());
        jgy_website->setSizePolicy(sizePolicy);
        jgy_website->setMinimumSize(QSize(0, 30));

        horizontalLayout_24->addWidget(jgy_website);

        jgy_websiteJudge = new QPushButton(layoutWidget_6);
        jgy_websiteJudge->setObjectName(QString::fromUtf8("jgy_websiteJudge"));
        jgy_websiteJudge->setMinimumSize(QSize(35, 35));
        jgy_websiteJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_24->addWidget(jgy_websiteJudge);


        verticalLayout_5->addLayout(horizontalLayout_24);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        jgy_passwordLabel = new QLabel(layoutWidget_6);
        jgy_passwordLabel->setObjectName(QString::fromUtf8("jgy_passwordLabel"));
        jgy_passwordLabel->setMinimumSize(QSize(60, 0));
        jgy_passwordLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_21->addWidget(jgy_passwordLabel);

        jgy_password = new QLineEdit(layoutWidget_6);
        jgy_password->setObjectName(QString::fromUtf8("jgy_password"));
        jgy_password->setMinimumSize(QSize(0, 30));

        horizontalLayout_21->addWidget(jgy_password);

        jgy_passwordJudge = new QPushButton(layoutWidget_6);
        jgy_passwordJudge->setObjectName(QString::fromUtf8("jgy_passwordJudge"));
        jgy_passwordJudge->setMinimumSize(QSize(35, 35));
        jgy_passwordJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_21->addWidget(jgy_passwordJudge);


        verticalLayout_5->addLayout(horizontalLayout_21);

        layoutWidget_7 = new QWidget(jianguoyun);
        layoutWidget_7->setObjectName(QString::fromUtf8("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(420, 360, 195, 31));
        horizontalLayout_15 = new QHBoxLayout(layoutWidget_7);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        jgy_yes = new QPushButton(layoutWidget_7);
        jgy_yes->setObjectName(QString::fromUtf8("jgy_yes"));

        horizontalLayout_15->addWidget(jgy_yes);

        jgy_no = new QPushButton(layoutWidget_7);
        jgy_no->setObjectName(QString::fromUtf8("jgy_no"));

        horizontalLayout_15->addWidget(jgy_no);

        jgy_remark = new QTextEdit(jianguoyun);
        jgy_remark->setObjectName(QString::fromUtf8("jgy_remark"));
        jgy_remark->setGeometry(QRect(30, 230, 591, 121));
        jgy_tip = new QTextEdit(jianguoyun);
        jgy_tip->setObjectName(QString::fromUtf8("jgy_tip"));
        jgy_tip->setGeometry(QRect(360, 20, 261, 201));
        jgy_tip->setFont(font);
        jgy_tip->setUndoRedoEnabled(false);
        jgy_tip->setReadOnly(true);
        tabWidget->addTab(jianguoyun, QString());
        other = new QWidget();
        other->setObjectName(QString::fromUtf8("other"));
        layoutWidget_8 = new QWidget(other);
        layoutWidget_8->setObjectName(QString::fromUtf8("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(30, 20, 311, 91));
        verticalLayout_6 = new QVBoxLayout(layoutWidget_8);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        other_nameLabel = new QLabel(layoutWidget_8);
        other_nameLabel->setObjectName(QString::fromUtf8("other_nameLabel"));
        other_nameLabel->setMinimumSize(QSize(60, 0));
        other_nameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_20->addWidget(other_nameLabel);

        other_name = new QLineEdit(layoutWidget_8);
        other_name->setObjectName(QString::fromUtf8("other_name"));
        other_name->setMinimumSize(QSize(0, 30));

        horizontalLayout_20->addWidget(other_name);

        space_6 = new QPushButton(layoutWidget_8);
        space_6->setObjectName(QString::fromUtf8("space_6"));
        space_6->setMinimumSize(QSize(35, 35));
        space_6->setMaximumSize(QSize(35, 35));
        space_6->setStyleSheet(QString::fromUtf8("border:0px;background-color:transparent"));

        horizontalLayout_20->addWidget(space_6);


        verticalLayout_6->addLayout(horizontalLayout_20);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        other_passwordLabel = new QLabel(layoutWidget_8);
        other_passwordLabel->setObjectName(QString::fromUtf8("other_passwordLabel"));
        other_passwordLabel->setMinimumSize(QSize(60, 0));
        other_passwordLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_22->addWidget(other_passwordLabel);

        other_password = new QLineEdit(layoutWidget_8);
        other_password->setObjectName(QString::fromUtf8("other_password"));
        other_password->setMinimumSize(QSize(0, 30));

        horizontalLayout_22->addWidget(other_password);

        other_passwordJudge = new QPushButton(layoutWidget_8);
        other_passwordJudge->setObjectName(QString::fromUtf8("other_passwordJudge"));
        other_passwordJudge->setMinimumSize(QSize(35, 35));
        other_passwordJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_22->addWidget(other_passwordJudge);


        verticalLayout_6->addLayout(horizontalLayout_22);

        layoutWidget_9 = new QWidget(other);
        layoutWidget_9->setObjectName(QString::fromUtf8("layoutWidget_9"));
        layoutWidget_9->setGeometry(QRect(420, 360, 195, 31));
        horizontalLayout_29 = new QHBoxLayout(layoutWidget_9);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(0, 0, 0, 0);
        other_yes = new QPushButton(layoutWidget_9);
        other_yes->setObjectName(QString::fromUtf8("other_yes"));

        horizontalLayout_29->addWidget(other_yes);

        other_no = new QPushButton(layoutWidget_9);
        other_no->setObjectName(QString::fromUtf8("other_no"));

        horizontalLayout_29->addWidget(other_no);

        other_remark = new QTextEdit(other);
        other_remark->setObjectName(QString::fromUtf8("other_remark"));
        other_remark->setGeometry(QRect(360, 20, 261, 331));
        tabWidget->addTab(other, QString());
        newGroup = new QWidget();
        newGroup->setObjectName(QString::fromUtf8("newGroup"));
        layoutWidget_10 = new QWidget(newGroup);
        layoutWidget_10->setObjectName(QString::fromUtf8("layoutWidget_10"));
        layoutWidget_10->setGeometry(QRect(420, 360, 195, 31));
        horizontalLayout_30 = new QHBoxLayout(layoutWidget_10);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        horizontalLayout_30->setContentsMargins(0, 0, 0, 0);
        group_yes = new QPushButton(layoutWidget_10);
        group_yes->setObjectName(QString::fromUtf8("group_yes"));

        horizontalLayout_30->addWidget(group_yes);

        group_no = new QPushButton(layoutWidget_10);
        group_no->setObjectName(QString::fromUtf8("group_no"));

        horizontalLayout_30->addWidget(group_no);

        group_remark = new QTextEdit(newGroup);
        group_remark->setObjectName(QString::fromUtf8("group_remark"));
        group_remark->setGeometry(QRect(360, 20, 261, 331));
        layoutWidget_11 = new QWidget(newGroup);
        layoutWidget_11->setObjectName(QString::fromUtf8("layoutWidget_11"));
        layoutWidget_11->setGeometry(QRect(31, 21, 304, 127));
        verticalLayout_7 = new QVBoxLayout(layoutWidget_11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        groupNameLabel = new QLabel(layoutWidget_11);
        groupNameLabel->setObjectName(QString::fromUtf8("groupNameLabel"));
        groupNameLabel->setMinimumSize(QSize(80, 0));
        groupNameLabel->setMaximumSize(QSize(80, 16777215));
        groupNameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(groupNameLabel);

        groupName = new QLineEdit(layoutWidget_11);
        groupName->setObjectName(QString::fromUtf8("groupName"));
        groupName->setMinimumSize(QSize(0, 30));

        horizontalLayout_8->addWidget(groupName);

        groupNameJudge = new QPushButton(layoutWidget_11);
        groupNameJudge->setObjectName(QString::fromUtf8("groupNameJudge"));
        groupNameJudge->setMinimumSize(QSize(35, 35));
        groupNameJudge->setMaximumSize(QSize(35, 35));

        horizontalLayout_8->addWidget(groupNameJudge);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout_53 = new QHBoxLayout();
        horizontalLayout_53->setObjectName(QString::fromUtf8("horizontalLayout_53"));
        groupNameWarning = new QLabel(layoutWidget_11);
        groupNameWarning->setObjectName(QString::fromUtf8("groupNameWarning"));
        groupNameWarning->setStyleSheet(QString::fromUtf8("color:red;"));
        groupNameWarning->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_53->addWidget(groupNameWarning);

        space_15 = new QPushButton(layoutWidget_11);
        space_15->setObjectName(QString::fromUtf8("space_15"));
        space_15->setMinimumSize(QSize(35, 35));
        space_15->setMaximumSize(QSize(35, 35));
        space_15->setStyleSheet(QString::fromUtf8("border:0px;background-color:transparent"));

        horizontalLayout_53->addWidget(space_15);


        verticalLayout_7->addLayout(horizontalLayout_53);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        groupTypeLabel = new QLabel(layoutWidget_11);
        groupTypeLabel->setObjectName(QString::fromUtf8("groupTypeLabel"));
        groupTypeLabel->setMinimumSize(QSize(80, 0));
        groupTypeLabel->setMaximumSize(QSize(80, 16777215));
        groupTypeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_18->addWidget(groupTypeLabel);

        groupType = new QComboBox(layoutWidget_11);
        groupType->setObjectName(QString::fromUtf8("groupType"));

        horizontalLayout_18->addWidget(groupType);

        space_7 = new QPushButton(layoutWidget_11);
        space_7->setObjectName(QString::fromUtf8("space_7"));
        space_7->setMinimumSize(QSize(35, 35));
        space_7->setMaximumSize(QSize(35, 35));
        space_7->setStyleSheet(QString::fromUtf8("border:0px;background-color:transparent"));

        horizontalLayout_18->addWidget(space_7);


        verticalLayout_7->addLayout(horizontalLayout_18);

        tabWidget->addTab(newGroup, QString());
        frame = new QFrame(addItemDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 661, 491));
        frame->setStyleSheet(QString::fromUtf8("border:0px;\n"
"border-radius:10px;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        tabWidget->raise();

        retranslateUi(addItemDialog);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(addItemDialog);
    } // setupUi

    void retranslateUi(QDialog *addItemDialog)
    {
        addItemDialog->setWindowTitle(QCoreApplication::translate("addItemDialog", "Dialog", nullptr));
        yes->setText(QCoreApplication::translate("addItemDialog", "\347\241\256\345\256\232", nullptr));
        no->setText(QCoreApplication::translate("addItemDialog", "\345\217\226\346\266\210", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("addItemDialog", "\344\277\241\346\201\257\345\241\253\345\206\231", nullptr));
        nameLabel->setText(QCoreApplication::translate("addItemDialog", "\345\220\215\347\247\260*", nullptr));
        name->setPlaceholderText(QCoreApplication::translate("addItemDialog", "\347\275\221\347\253\231\357\274\214\345\272\224\347\224\250\346\210\226\347\224\250\351\200\224\345\220\215\347\247\260", nullptr));
        space_2->setText(QString());
        nickNameLabel->setText(QCoreApplication::translate("addItemDialog", "\346\230\265\347\247\260*", nullptr));
        space_3->setText(QString());
        idLabel->setText(QCoreApplication::translate("addItemDialog", "ID", nullptr));
        space_4->setText(QString());
        passwordLabel->setText(QCoreApplication::translate("addItemDialog", "\345\257\206\347\240\201*", nullptr));
        passwordJudge->setText(QString());
        mobileLabel->setText(QCoreApplication::translate("addItemDialog", "\346\211\213\346\234\272", nullptr));
        mobileJudge->setText(QString());
        mailLabel->setText(QCoreApplication::translate("addItemDialog", "\351\202\256\347\256\261", nullptr));
        mailJudge->setText(QString());
        websiteLabel->setText(QCoreApplication::translate("addItemDialog", "\345\256\230\347\275\221", nullptr));
        websiteJudge->setText(QString());
        remark->setPlaceholderText(QCoreApplication::translate("addItemDialog", "\345\241\253\345\206\231\345\244\207\346\263\250", nullptr));
        groupBox->setTitle(QCoreApplication::translate("addItemDialog", "\350\264\246\345\217\267\345\205\263\350\201\224", nullptr));
        wechat->setText(QCoreApplication::translate("addItemDialog", "\345\276\256\344\277\241", nullptr));
        qq->setText(QCoreApplication::translate("addItemDialog", "QQ", nullptr));
        weibo->setText(QCoreApplication::translate("addItemDialog", "\345\276\256\345\215\232", nullptr));
        github->setText(QCoreApplication::translate("addItemDialog", "Github", nullptr));
        alipay->setText(QCoreApplication::translate("addItemDialog", "\346\224\257\344\273\230\345\256\235", nullptr));
        huawei->setText(QCoreApplication::translate("addItemDialog", "\345\215\216\344\270\272", nullptr));
        xiaomi->setText(QCoreApplication::translate("addItemDialog", "\345\260\217\347\261\263", nullptr));
        taobao->setText(QCoreApplication::translate("addItemDialog", "\346\267\230\345\256\235", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(common), QCoreApplication::translate("addItemDialog", "\346\231\256\351\200\232\345\257\206\347\240\201", nullptr));
        mail_nameLabel->setText(QCoreApplication::translate("addItemDialog", "\345\220\215\347\247\260*", nullptr));
        mail_name->setPlaceholderText(QCoreApplication::translate("addItemDialog", "\347\275\221\347\253\231\357\274\214\345\272\224\347\224\250\346\210\226\347\224\250\351\200\224\345\220\215\347\247\260", nullptr));
        space->setText(QString());
        mail_mailLabel->setText(QCoreApplication::translate("addItemDialog", "\351\202\256\347\256\261*", nullptr));
        mail_mailJudge->setText(QString());
        mail_subNameLabel->setText(QCoreApplication::translate("addItemDialog", "\345\210\253\345\220\215", nullptr));
        mail_subNameJudge->setText(QString());
        mail_passwordLabel->setText(QCoreApplication::translate("addItemDialog", "\345\257\206\347\240\201*", nullptr));
        mail_passwordJudge->setText(QString());
        mail_websiteLabel->setText(QCoreApplication::translate("addItemDialog", "\345\256\230\347\275\221*", nullptr));
        mail_websiteJudge->setText(QString());
        mail_remark->setPlaceholderText(QCoreApplication::translate("addItemDialog", "\345\241\253\345\206\231\345\244\207\346\263\250", nullptr));
        mail_yes->setText(QCoreApplication::translate("addItemDialog", "\347\241\256\345\256\232", nullptr));
        mail_no->setText(QCoreApplication::translate("addItemDialog", "\345\217\226\346\266\210", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(mailKey), QCoreApplication::translate("addItemDialog", "\351\202\256\347\256\261\345\257\206\347\240\201", nullptr));
        jgy_nameLabel->setText(QCoreApplication::translate("addItemDialog", "\345\220\215\347\247\260*", nullptr));
        jgy_name->setPlaceholderText(QCoreApplication::translate("addItemDialog", "\347\275\221\347\253\231\357\274\214\345\272\224\347\224\250\346\210\226\347\224\250\351\200\224\345\220\215\347\247\260", nullptr));
        space_5->setText(QString());
        jgy_mailLabel->setText(QCoreApplication::translate("addItemDialog", "\351\202\256\347\256\261*", nullptr));
        jgy_mailJudge->setText(QString());
        jgy_websiteLabel->setText(QCoreApplication::translate("addItemDialog", "\345\234\260\345\235\200*", nullptr));
        jgy_websiteJudge->setText(QString());
        jgy_passwordLabel->setText(QCoreApplication::translate("addItemDialog", "\346\216\210\346\235\203\347\240\201*", nullptr));
        jgy_passwordJudge->setText(QString());
        jgy_yes->setText(QCoreApplication::translate("addItemDialog", "\347\241\256\345\256\232", nullptr));
        jgy_no->setText(QCoreApplication::translate("addItemDialog", "\345\217\226\346\266\210", nullptr));
        jgy_remark->setPlaceholderText(QCoreApplication::translate("addItemDialog", "\345\241\253\345\206\231\345\244\207\346\263\250", nullptr));
        jgy_tip->setHtml(QCoreApplication::translate("addItemDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1.\346\255\244\351\200\211\351\241\271\347\224\250\344\272\216\346\224\257\346\214\201WebDav,DropBox,Google Drive\347\255\211\347\275\221\347\273\234\345\255\230\345\202\250\346\226\207\344\273\266\345\205\261\344\272\253\346\234\215\345\212\241\347\232\204\350\264\246\345\217\267\344\270\255\344\270\272\345\272\224\347\224\250\345\274\200\345\220\257\347\232\204\346\216\210\346\235\203\345\257\206\347\240\201\343\200\202</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-inden"
                        "t:0; text-indent:0px;\">2.\345\235\232\346\236\234\344\272\221WebDav\346\234\215\345\212\241\345\234\260\345\235\200\344\270\272</p>\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">https://dav.jianguoyun.com/dav</span></p></body></html>", nullptr));
        jgy_tip->setPlaceholderText(QString());
        tabWidget->setTabText(tabWidget->indexOf(jianguoyun), QCoreApplication::translate("addItemDialog", "\345\205\261\344\272\253\346\234\215\345\212\241\346\216\210\346\235\203\347\240\201", nullptr));
        other_nameLabel->setText(QCoreApplication::translate("addItemDialog", "\345\220\215\347\247\260*", nullptr));
        other_name->setPlaceholderText(QCoreApplication::translate("addItemDialog", "\347\275\221\347\253\231\357\274\214\345\272\224\347\224\250\346\210\226\347\224\250\351\200\224\345\220\215\347\247\260", nullptr));
        space_6->setText(QString());
        other_passwordLabel->setText(QCoreApplication::translate("addItemDialog", "\345\257\206\347\240\201*", nullptr));
        other_passwordJudge->setText(QString());
        other_yes->setText(QCoreApplication::translate("addItemDialog", "\347\241\256\345\256\232", nullptr));
        other_no->setText(QCoreApplication::translate("addItemDialog", "\345\217\226\346\266\210", nullptr));
        other_remark->setPlaceholderText(QCoreApplication::translate("addItemDialog", "\345\241\253\345\206\231\345\244\207\346\263\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(other), QCoreApplication::translate("addItemDialog", "\345\205\266\344\273\226\345\257\206\347\240\201", nullptr));
        group_yes->setText(QCoreApplication::translate("addItemDialog", "\347\241\256\345\256\232", nullptr));
        group_no->setText(QCoreApplication::translate("addItemDialog", "\345\217\226\346\266\210", nullptr));
        group_remark->setPlaceholderText(QCoreApplication::translate("addItemDialog", "\345\241\253\345\206\231\345\244\207\346\263\250", nullptr));
        groupNameLabel->setText(QCoreApplication::translate("addItemDialog", "\345\210\206\347\273\204\345\220\215\347\247\260*", nullptr));
        groupNameJudge->setText(QString());
        groupNameWarning->setText(QString());
        space_15->setText(QString());
        groupTypeLabel->setText(QCoreApplication::translate("addItemDialog", "\345\210\206\347\273\204\347\261\273\345\236\213*", nullptr));
        space_7->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(newGroup), QCoreApplication::translate("addItemDialog", "\346\226\260\345\273\272\345\210\206\347\273\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addItemDialog: public Ui_addItemDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEMDIALOG_H
