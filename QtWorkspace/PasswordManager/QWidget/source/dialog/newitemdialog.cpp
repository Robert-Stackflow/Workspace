#include "dialog/newitemdialog.h"
#include "customField/customComboBox.h"
#include "customField/customLineEdit.h"
#include "customField/customTextEdit.h"
#include "ui_newitemdialog.h"
#include "widget.h"
#include "util/shareddata.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
newItemDialog::newItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newItemDialog)
{
    ui->setupUi(this);
    InitDialog();
    ui->scrollAreaWidgetContents->setLayout(ui->infoLayout);
}
void newItemDialog::InitDialog(){
    //删除标题栏
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义标题栏
    m_titleBar=new CustomTitleBar(this);
    m_titleBar->setWindowIcon(":/custom/logos/logo.png");
    //设置标题栏字体
    QFont font;
    font.setBold(true);
    font.setPointSize(11);
    font.setFamily("黑体");
    m_titleBar->titleLabel->setFont(font);
    //隐藏标题栏按钮
    m_titleBar->setMaximizeVisible(false);
    //设定标题栏位置与大小
    m_titleBar->setFixedWidth(ui->frame->width());
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    //设定阴影效果
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect();
    shadow_effect->setColor(QColor(128,128,128,255));
    shadow_effect->setBlurRadius(20);
    shadow_effect->setOffset(0, 0);
    ui->frame->setGraphicsEffect(shadow_effect);
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
}
newItemDialog::~newItemDialog()
{
    delete ui;
}
void newItemDialog::loadGroupType(int index){
    SharedData& sharedData = SharedData::instance();
    GroupType* groupType=sharedData.groupTypeList[index];
    currentGroupType=index;
    //清除layout内的控件
    QLayoutItem *child;
    while((child = ui->infoLayout->takeAt(0)) != 0){
        if(child->widget())
            child->widget()->setParent(nullptr);
        delete child;
    }
    //加载groupType中的字段控件
    fieldControllerList.clear();
    for(int i=0;i<groupType->count();i++)
    {
        AbstractCustomField* currentField=groupType->at(i);
        AbstractCustomField* newField=nullptr;
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
        newField->setPlaceholderText(currentField->getPlaceholderText());
        fieldControllerList<<newField;
    }
    ui->scrollAreaWidgetContents->setWindowFlags(Qt::FramelessWindowHint);
    ui->groupTypeName->setText(groupType->getGroupTypeName());
    ui->groupTypeCreateTime->setText(groupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->groupTypeLastEditTime->setText(groupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->tip->setText(groupType->getDescribe());
}
void newItemDialog::onConfirmClicked(){
    bool isValid=false;
    for(int i=0;i<fieldControllerList.count();i++)
        isValid=isValid&&fieldControllerList[i]->isValid();
    if(isValid)
    {
        QStringList fieldValueList;
        for(int i=0;i<fieldControllerList.count();i++)
            fieldValueList<<fieldControllerList[i]->text();
        newKeyItem=new KeyItem(currentGroupType,fieldValueList);
        this->close();
    }

}
void newItemDialog::onCancelClicked(){

}
