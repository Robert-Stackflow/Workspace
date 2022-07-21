#include "customItem/customTextEdit.h"
#include "ui_customTextEdit.h"

customTextEdit::customTextEdit(const QString& name,isRequiredChoices isRequired,dataTypeChoices dataType,QWidget* parent):
    abstractCustomItem(name,TEXTEDIT,isRequired,dataType,parent),
    ui(new Ui::customTextEdit)
{
    ui->setupUi(this);
}
void customTextEdit::clear(){

}
void customTextEdit::setPlaceholderText(const QString& placeholderText){

}
QString customTextEdit::toPlainText(){

}
void customTextEdit::setText(const QString &text){

}
QString customTextEdit::getPlaceholderText(){

}
bool customTextEdit::isValid(){

}

customTextEdit::~customTextEdit(){
    delete ui;
}
