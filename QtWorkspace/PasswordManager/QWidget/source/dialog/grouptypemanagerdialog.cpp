#include "dialog/grouptypemanagerdialog.h"
#include "ui_grouptypemanagerdialog.h"

groupTypeManagerDialog::groupTypeManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::groupTypeManagerDialog)
{
    ui->setupUi(this);
}

groupTypeManagerDialog::~groupTypeManagerDialog()
{
    delete ui;
}
