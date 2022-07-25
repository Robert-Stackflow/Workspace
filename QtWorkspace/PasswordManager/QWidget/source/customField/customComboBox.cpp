#include "customField/customComboBox.h"
#include "ui_customComboBox.h"
#include <QDebug>
#include <QMetaEnum>
#pragma warning (disable:4100)
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
customComboBox::customComboBox(const QString& fieldName,isRequiredChoices isRequired,dataTypeChoices dataType,QWidget* parent):
    AbstractCustomField(fieldName,COMBOBOX,isRequired,dataType,parent),
    ui(new Ui::customComboBox)
{
    ui->setupUi(this);
    //设置controller
    QMetaEnum controllerTypeMeta = QMetaEnum::fromType<AbstractCustomField::controllerTypeChoices>();
    ui->controller->setObjectName(controllerTypeMeta.valueToKey(controllerType));
    ui->controller->setEditable(true);
    //设置controllerLabel
    ui->controllerLabel->setText(this->controllerFieldName);
    ui->controllerLabel->setAlignment(Qt::AlignCenter);
    ui->controllerLabel->setStyleSheet("border:0px;background-color:transparent");
    ui->controllerLabel->setObjectName(controllerTypeMeta.valueToKey(controllerType)+QString("LABEL"));
    //设置controllerJudge
    ui->controllerJudge->setStyleSheet("border:0px;background-color:transparent");
    QMetaEnum dataTypeMeta = QMetaEnum::fromType<AbstractCustomField::dataTypeChoices>();
    ui->controllerJudge->setObjectName(dataTypeMeta.valueToKey(controllerType)+QString("JUDGE"));
    //根据dataType初始化
    if(dataType==NORMAL){
        //绑定槽函数
        connect(ui->controller,SIGNAL(currentTextChanged(QString)),this,SLOT(onControllerEdited(QString)));
        connect(ui->controller,SIGNAL(currentIndexChanged(int)),this,SLOT(onControllerCurrentIndexChanged(int)));
    }else if(dataType==WEBSITE||dataType==MOBILE||dataType==MAIL){
        //设置Validator
        const QValidator* validator=getValidator();
        ui->controller->setValidator(validator);
        //绑定槽函数
        connect(ui->controller,SIGNAL(currentTextChanged(QString)),this,SLOT(onControllerEdited(QString)));
        connect(ui->controller,SIGNAL(currentIndexChanged()),this,SLOT(onControllerCurrentIndexChanged()));
    }
    setPlaceholderText(defaultPlaceholderText);
}

customComboBox::~customComboBox()
{
    delete ui;
}
bool customComboBox::isValid(){
    int position=0;
    QString value=QString(ui->controller->currentText());
    return ((value!=""&&isRequired==REQUIRED)||(getValidator()!=nullptr&&QValidator::Acceptable==getValidator()->validate(value,position)));
}
void customComboBox::onControllerCurrentIndexChanged(int){
    emit currentIndexChanged();
}
void customComboBox::onControllerEdited(const QString &arg)
{
    if(isRequired==AbstractCustomField::OPTIONAL&&dataType==NORMAL){
        ui->controllerJudge->setIcon(QIcon());
        ui->controllerJudge->setStatusTip("");
    }else if(!isValid()){
        ui->controllerJudge->setIcon(QIcon(":custom/icons/wrong.png"));
        ui->controllerJudge->setStatusTip("wrong");
    }else{
        ui->controllerJudge->setIcon(QIcon(":custom/icons/right.png"));
        ui->controllerJudge->setStatusTip("right");
    }
}
void customComboBox::setPlaceholderText(const QString &placeholderText){
    ui->controller->lineEdit()->setPlaceholderText(placeholderText);
}
QString customComboBox::getPlaceholderText(){
    return ui->controller->lineEdit()->placeholderText();
}
void customComboBox::addItem(const QString& item){
    ui->controller->addItem(item);
}
void customComboBox::addItems(const QStringList& items){
    ui->controller->addItems(items);
}
void customComboBox::addItems(const QList<QString> &items){
    QStringList itemList;
    for(int i=0;i<items.count();i++)
        itemList<<items[i];
    ui->controller->addItems(itemList);
}
void customComboBox::clear(){
    ui->controller->clear();
}
int customComboBox::currentIndex(){
    return ui->controller->currentIndex();
}
QString customComboBox::currentText(){
    return ui->controller->currentText();
}
void customComboBox::setCurrentIndex(int index){
    ui->controller->setCurrentIndex(index);
}
void customComboBox::setCurrentText(const QString& text){
    ui->controller->setCurrentText(text);
}
void customComboBox::setEnable(bool enable){
    ui->controller->setEnabled(enable);
}
void customComboBox::setEditable(bool editable){
    ui->controller->setEditable(editable);
}
bool customComboBox::isEnable(){
    return ui->controller->isEnabled();
}
AbstractCustomField* customComboBox::clone(){
    AbstractCustomField* copy=new customComboBox(fieldName,isRequired,dataType,parent);
    return copy;
}
void customComboBox::setCompleter(QCompleter* completer){
    ui->controller->setCompleter(completer);
}
