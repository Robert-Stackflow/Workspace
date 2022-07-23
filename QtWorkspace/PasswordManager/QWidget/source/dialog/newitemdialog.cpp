#include "dialog/newitemdialog.h"
#include "customField/customComboBox.h"
#include "customField/customLineEdit.h"
#include "customField/customTextEdit.h"
#include "ui_newitemdialog.h"
#include "widget.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
newItemDialog::newItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newItemDialog)
{
    ui->setupUi(this);
    //删除标题栏
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义标题栏
    m_titleBar=new TitleBar(this);
    m_titleBar->setTitleBarIcon(":/custom/logos/logo.png");
    //设置标题栏字体
    QFont font;
    font.setBold(true);
    font.setPointSize(11);
    font.setFamily("黑体");
    m_titleBar->m_titleLabel->setFont(font);
    //隐藏标题栏按钮
    m_titleBar->forbiddenUserButton();
    m_titleBar->forbiddenMaxmizeButton();
    //设定标题栏位置与大小
    m_titleBar->setFixedWidth(ui->frame->width());
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    //设定阴影效果
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor(128,128,128,255));
    shadow_effect->setBlurRadius(20);
    shadow_effect->setOffset(0, 0);
    ui->frame->setGraphicsEffect(shadow_effect);
    //隐藏tabWidget标题栏
    ui->tabWidget->tabBar()->hide();
    //加载QSS样式
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString temp = this->styleSheet;
        temp += QLatin1String(file.readAll());
        this->styleSheet=temp;
        this->setStyleSheet(styleSheet);
        file.close();
    }
    ui->scrollAreaWidgetContents->setLayout(ui->infoLayout);
}
newItemDialog::~newItemDialog()
{
    delete ui;
}
void newItemDialog::loadGroupType(int index){
    Widget* parent=(Widget*)this->parent();
    GroupType* groupType=parent->groupTypes->at(index);
    for(int i=0;i<groupType->count();i++)
    {
        AbstractCustomField* currentField=groupType->at(i);
        AbstractCustomField* newField=nullptr;
        qDebug()<<currentField->getControllerType();
        switch(currentField->getControllerType())
        {
        case AbstractCustomField::LINEEDIT:
            newField=new customLineEdit(currentField->getFieldName(),currentField->getIsRequired(),currentField->getDataType(),this);
            ui->infoLayout->addWidget(newField);
            break;
        case AbstractCustomField::COMBOBOX:
            newField=new customComboBox(currentField->getFieldName(),currentField->getIsRequired(),currentField->getDataType(),this);
            ui->infoLayout->addWidget(newField);
            break;
        case AbstractCustomField::TEXTEDIT:
            newField=new customTextEdit(currentField->getFieldName(),currentField->getIsRequired(),currentField->getDataType(),this);
            ui->infoLayout->addWidget(newField);
            break;
        }
    }
    ui->groupTypeName->setText(groupType->getGroupTypeName());
    ui->groupTypeCreateTime->setText(groupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->groupTypeLastEditTime->setText(groupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"));
}
void newItemDialog::onConfirmClicked(){

}
void newItemDialog::onCancelClicked(){

}
