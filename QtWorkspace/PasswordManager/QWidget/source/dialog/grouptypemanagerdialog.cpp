#include "dialog/grouptypemanagerdialog.h"
#include "customField/customComboBox.h"
#include "widget.h"
#include "ui_grouptypemanagerdialog.h"
#pragma warning (disable:4100)
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
groupTypeManagerDialog::groupTypeManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::groupTypeManagerDialog)
{
    ui->setupUi(this);
    //删除标题栏
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义标题栏
    m_titleBar=new TitleBar(this);
    m_titleBar->setWindowTitle("类型管理");
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
    //设置名称框
    typeName=new customLineEdit("类型名称",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
    ui->typeNameLayout->addWidget(typeName);
    addFieldName=new customLineEdit("字段名称",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
    ui->addFieldNameLayout->addWidget(addFieldName);
    addFieldTip=new customLineEdit("填写提示",AbstractCustomField::OPTIONAL,AbstractCustomField::NORMAL,this);
    ui->addFieldTipLayout->addWidget(addFieldTip);
    addFieldName->setMaxLength(10);
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);
    //设置添加字段的下拉选择框
    Widget* tempParent=(Widget*)this->parent();
    FieldTypes* itemTypes=&tempParent->fieldTypes;
    ui->addFieldComboBox->addItems(itemTypes->getNames());
    editFieldsTableWidgetHeader<<"是否必填"<<"字段名称"<<"字段类型"<<"填写提示";
    ui->editFieldsTableWidget->setColumnCount(editFieldsTableWidgetHeader.size());
    ui->editFieldsTableWidget->setHorizontalHeaderLabels(editFieldsTableWidgetHeader);
    ui->editFieldsTableWidget->setAlternatingRowColors(true);
    ui->editFieldsTableWidget->verticalHeader()->setDefaultSectionSize(45);
    ui->editFieldsTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->editFieldsTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->editFieldsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->editFieldsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->editFieldsTableWidget->verticalHeader()->hide();
    ui->editFieldsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置表头
    typeManagerTableWidgetHeader<<"类型名称"<<"字段数目"<<"创建时间"<<"修改时间"<<"描述";
    ui->typeManagerTableWidget->viewport()->installEventFilter(this);
    ui->typeManagerTableWidget->setColumnCount(typeManagerTableWidgetHeader.size());
    ui->typeManagerTableWidget->setHorizontalHeaderLabels(typeManagerTableWidgetHeader);
    ui->typeManagerTableWidget->setAlternatingRowColors(true);
    ui->typeManagerTableWidget->verticalHeader()->setDefaultSectionSize(45);
    ui->typeManagerTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->typeManagerTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->typeManagerTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->typeManagerTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->typeManagerTableWidget->verticalHeader()->hide();
    ui->typeManagerTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //绑定槽函数
    connect(this,SIGNAL(typeManagerTableWidgetClicked()),this,SLOT(onTypeManagerTableWidgetClicked()));
    connect(ui->editTypeButton,SIGNAL(clicked()),this,SLOT(onEditTypeClicked()));
    connect(ui->deleteTypeButton,SIGNAL(clicked()),this,SLOT(onDeleteTypeClicked()));
    connect(ui->copyTypeButton,SIGNAL(clicked()),this,SLOT(onCopyTypeClicked()));
    connect(ui->newTypeButton,SIGNAL(clicked()),this,SLOT(onNewTypeClicked()));
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(onConfirmClicked()));
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(onCancelClicked()));
    connect(ui->addFieldButton,SIGNAL(clicked()),this,SLOT(onAddFieldClicked()));
    connect(this,SIGNAL(groupTypeCountChanged()),parent,SLOT(onGroupTypeCountChanged()));
}

groupTypeManagerDialog::~groupTypeManagerDialog()
{
    delete ui;
}
void groupTypeManagerDialog::loadGroupTypes(){
    Widget* parent=(Widget*)this->parent();
    GroupTypes* groupTypes=parent->groupTypes;
    for(int i=0;i<groupTypes->count();i++)
    {
        GroupType* groupType=groupTypes->at(i);
        ui->typeManagerTableWidget->insertRow(ui->typeManagerTableWidget->rowCount());
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,0,new QTableWidgetItem(groupType->getGroupTypeName()));
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(groupType->count())));
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,2,new QTableWidgetItem(groupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss")));
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,3,new QTableWidgetItem(groupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")));
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,4,new QTableWidgetItem(groupType->getDescribe()));
    }
}
bool groupTypeManagerDialog::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->typeManagerTableWidget->viewport())
    {
        if (e->type() == QEvent::MouseButtonPress){
            emit typeManagerTableWidgetClicked();
        }
    }
    return QWidget::eventFilter(obj,e);
}
void groupTypeManagerDialog::closeEvent(QCloseEvent* event)
{
    //关闭窗口时，重置为类型管理页，并给变量赋空值
    currentMode=-1;
    newGroupType=nullptr;
    chosenType=nullptr;
    tempFields.clear();
    ui->tabWidget->setCurrentIndex(0);
    m_titleBar->setWindowTitle("类型管理");
}
void groupTypeManagerDialog::onTypeManagerTableWidgetClicked(){
    QPoint point=QPoint(ui->typeManagerTableWidget->mapFromGlobal(QCursor::pos()).x(),ui->typeManagerTableWidget->mapFromGlobal(QCursor::pos()).y()-ui->typeManagerTableWidget->horizontalHeader()->height());
    QModelIndex index = ui->typeManagerTableWidget->indexAt(point);
    currentRow=index.row();
    if(index.row()!=-1){
        ui->chosen->setText(ui->typeManagerTableWidget->item(index.row(),0)->text());
    }else{
        ui->chosen->setText("未选中");
    }
}
void groupTypeManagerDialog::onEditTypeClicked(){
    if(currentRow==-1){
        QMessageBox::warning(this,"警告","未选中类型!");
    }else{
        Widget* parent=(Widget*)this->parent();
        GroupTypes* groupTypes=parent->groupTypes;
        chosenType=groupTypes->at(currentRow);
        typeName->setText(chosenType->getGroupTypeName());
        chosenOldName=chosenType->getGroupTypeName();
        ui->remark->setText(chosenType->getDescribe());
        addFieldName->clear();
        addFieldTip->clear();
        for(int row = 0;row <= ui->editFieldsTableWidget->rowCount();row++)
            ui->editFieldsTableWidget->removeRow(0);
        for(int i = 0;i<chosenType->count();i++)
        {
            ui->editFieldsTableWidget->insertRow(ui->editFieldsTableWidget->rowCount());
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,0,new QTableWidgetItem(""));
            ui->editFieldsTableWidget->setCellWidget(ui->editFieldsTableWidget->rowCount()-1,0,chosenType->at(i)->getIsRequiredCheckBox());
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,1,new QTableWidgetItem(chosenType->at(i)->getFieldName()));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,2,new QTableWidgetItem(chosenType->at(i)->getFieldTypeName()));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,3,new QTableWidgetItem(chosenType->at(i)->getPlaceholderText()));
            for (int j=0;j<ui->editFieldsTableWidget->columnCount();j++){
                ui->editFieldsTableWidget->item(ui->editFieldsTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->editFieldsTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
            }
        }
        currentMode=1;
        ui->tabWidget->setCurrentIndex(1);
        m_titleBar->setWindowTitle("编辑类型\""+typeName->text()+"\"");
    }
}
void groupTypeManagerDialog::onDeleteTypeClicked(){
    int choice=QMessageBox::question(this,"确认删除","确认删除类型\""+typeName->text()+"\"");
    if(choice==QMessageBox::Yes){
    }
}
void groupTypeManagerDialog::onCopyTypeClicked(){
    if(currentRow==-1){
        QMessageBox::warning(this,"警告","未选中类型!");
    }else{
        Widget* parent=(Widget*)this->parent();
        GroupTypes* groupTypes=parent->groupTypes;
        chosenType=groupTypes->at(currentRow);
        typeName->setText(chosenType->getGroupTypeName()+"_copy");
        ui->remark->setText(chosenType->getDescribe());
        addFieldName->clear();
        addFieldTip->clear();
        for(int row = 0;row <= ui->editFieldsTableWidget->rowCount();row++)
            ui->editFieldsTableWidget->removeRow(0);
        currentMode=0;
        ui->tabWidget->setCurrentIndex(1);
        m_titleBar->setWindowTitle("复制类型\""+typeName->text()+"\"至新建类型");
    }
}
void groupTypeManagerDialog::onNewTypeClicked(){
    typeName->clear();
    addFieldName->clear();
    addFieldTip->clear();
    ui->remark->clear();
    for(int row = 0;row <= ui->editFieldsTableWidget->rowCount();row++)
        ui->editFieldsTableWidget->removeRow(0);
    currentMode=0;
    ui->tabWidget->setCurrentIndex(1);
    m_titleBar->setWindowTitle("新建类型");
}
void groupTypeManagerDialog::onCancelClicked(){
    if(currentMode==0){
        int choice=QMessageBox::question(this,"取消新建","是否取消新建");
        if(choice==QMessageBox::Yes){
            ui->tabWidget->setCurrentIndex(0);
            m_titleBar->setWindowTitle("类型管理");
        }
    }else if(currentMode==1){
        int choice=QMessageBox::question(this,"放弃修改","是否放弃修改");
        if(choice==QMessageBox::Yes){
            ui->tabWidget->setCurrentIndex(0);
            m_titleBar->setWindowTitle("类型管理");
        }
    }
    currentMode=-1;
    newGroupType=nullptr;
    chosenType=nullptr;
    tempFields.clear();
}
void groupTypeManagerDialog::onConfirmClicked(){
    Widget* parent=(Widget*)this->parent();
    GroupTypes* groupTypes=parent->groupTypes;
    if(currentMode==0){
        if(typeName->isValid()&&!groupTypes->has(typeName->text())&&tempFields.count()>=2){
            int choice=QMessageBox::question(this,"确认新建","是否确认新建类型\""+typeName->text()+"\"");
            if(choice==QMessageBox::Yes){
                newGroupType=new GroupType(typeName->text(),ui->remark->toPlainText(),tempFields);
                groupTypes->append(newGroupType);
                QSqlQuery query(parent->data);
                if(!parent->data.open()){
                    QMessageBox::critical(0, QObject::tr("Database Connection Error!"), parent->data.lastError().text());
                    return;
                }else{
                    QString newGroupTypeTableName=parent->databaseTableNameGetter.getGroupTypeTableName(newGroupType->getGroupTypeName());
                    if(!parent->data.tables().contains(newGroupTypeTableName)){
                        //向groups表插入数据
                        query.prepare("insert into "+parent->databaseTableNameGetter.getGroupTypesTableName()+" (groupTypeName,fieldCount,createTime,lastEditTime,describe)"
                                                                                                              "VALUES (:1,:2,:3,:4,:5)");
                        query.bindValue(":1",newGroupType->getGroupTypeName());
                        query.bindValue(":2",newGroupType->count());
                        query.bindValue(":3",newGroupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
                        query.bindValue(":4",newGroupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"));
                        query.bindValue(":5",newGroupType->getDescribe());
                        query.exec();
                        //如果分组不存在，创建记录分组信息的表
                        query.exec("create table "+newGroupTypeTableName+" (fieldName int,isRequired int,fieldTypeName varchar(200),placeholderText varchar(200))");
                        for(int i=0;i<newGroupType->count();i++){
                            query.prepare("insert into "+newGroupTypeTableName+" (fieldName,isRequired,fieldTypeName,placeholderText)"
                                                                               "VALUES (:1,:2,:3,:4)");
                            query.bindValue(":1",newGroupType->at(i)->getFieldName());
                            query.bindValue(":2",newGroupType->at(i)->getIsRequired());
                            query.bindValue(":3",newGroupType->at(i)->getFieldTypeName());
                            query.bindValue(":4",newGroupType->at(i)->getPlaceholderText());
                            query.exec();
                        }
                        parent->data.close();
                    }
                }
                emit groupTypeCountChanged();
                ui->typeManagerTableWidget->insertRow(ui->typeManagerTableWidget->rowCount());
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,0,new QTableWidgetItem(newGroupType->getGroupTypeName()));
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(newGroupType->count())));
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,2,new QTableWidgetItem(newGroupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss")));
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,3,new QTableWidgetItem(newGroupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")));
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,4,new QTableWidgetItem(newGroupType->getDescribe()));
                for (int j=0;j<ui->typeManagerTableWidget->columnCount();j++){
                    ui->typeManagerTableWidget->item(ui->typeManagerTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->typeManagerTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
                }
                ui->tabWidget->setCurrentIndex(0);
                m_titleBar->setWindowTitle("类型管理");
                currentMode=-1;
                newGroupType=nullptr;
                chosenType=nullptr;
                tempFields.clear();
            }
        }else{
            QString message="";
            if(!typeName->isValid())
                message+="名称不合法!\n";
            if(groupTypes->has(typeName->text()))
                message+="类型名已存在!\n";
            if(tempFields.count()<2)
                message+="字段数目不得小于2!";
            QMessageBox::warning(this,"警告",message);
        }
    }else if(currentMode==1){
        if(typeName->isValid()&&!(typeName->text()!=chosenOldName&&groupTypes->has(typeName->text()))&&(chosenType!=nullptr&&chosenType->count()>=2)){
            int choice=QMessageBox::question(this,"确认修改","是否确认保存修改类型\""+typeName->text()+"\"");
            if(choice==QMessageBox::Yes){
                chosenType->setGroupTypeName(typeName->text());
                chosenType->setDescribe(ui->remark->toPlainText());
                chosenType->setLastEditTime();
                ui->tabWidget->setCurrentIndex(0);
                m_titleBar->setWindowTitle("类型管理");
                currentMode=-1;
                newGroupType=nullptr;
                chosenType=nullptr;
                tempFields.clear();
            }
        }else{
            QString message="";
            if(!typeName->isValid())
                message+="名称不合法!\n";
            if(typeName->text()!=chosenOldName&&groupTypes->has(typeName->text()))
                message+="类型名已存在!\n";
            if((chosenType!=nullptr&&chosenType->count()<2))
                message+="字段数目不得小于2!";
            QMessageBox::warning(this,"警告",message);
        }
    }
}
void groupTypeManagerDialog::onAddFieldClicked(){
    Widget* parent=(Widget*)this->parent();
    FieldTypes* fieldTypes=&(parent->fieldTypes);
    bool flag=false;
    for(int i=0;i<tempFields.count();i++)
        if(tempFields[i]->getFieldName()==addFieldName->text())
            flag=true;
    if(currentMode==0){
        if(addFieldName->isValid()&&!flag){
            //获取item信息
            QString itemName=addFieldName->text();
            QString placeholderText=addFieldTip->text();
            int index=ui->addFieldComboBox->currentIndex();
            AbstractCustomField::controllerTypeChoices controllerType=fieldTypes->at(index).getFieldControllerType();
            AbstractCustomField::dataTypeChoices dataType=fieldTypes->at(index).getFieldDataType();
            AbstractCustomField::isRequiredChoices isRequired=fieldTypes->at(index).getFieldIsRequired();
            AbstractCustomField* temp=nullptr;
            //新建abstractCustomField
            if(controllerType==AbstractCustomField::LINEEDIT)
                temp=new customLineEdit(itemName,isRequired,dataType,this);
            else if(controllerType==AbstractCustomField::COMBOBOX)
                temp=new customComboBox(itemName,isRequired,dataType,this);
            if(temp!=nullptr&&placeholderText!=""){
                temp->setPlaceholderText(placeholderText);
            }
            //新建复选框
            QCheckBox *checkItem = new QCheckBox("是否必填",this);
            if(temp!=nullptr)
                checkItem->setChecked(temp->getIsRequired());
            checkItem->setObjectName("isRequiredCheckBox"+QString::number(ui->editFieldsTableWidget->rowCount()));
            connect(checkItem,SIGNAL(toggled(bool)),this,SLOT(onIsReqiuredCheckBoxToggled(bool)));
            temp->setIsRequiredCheckBox(checkItem);
            temp->setFieldTypeName(fieldTypes->at(index).getFieldTypeName());
            //加入到tempFields中
            tempFields<<temp;
            //添加到tableWidget中
            ui->editFieldsTableWidget->insertRow(ui->editFieldsTableWidget->rowCount());
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,0,new QTableWidgetItem(""));
            ui->editFieldsTableWidget->setCellWidget(ui->editFieldsTableWidget->rowCount()-1,0,checkItem);
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,1,new QTableWidgetItem(itemName));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,2,new QTableWidgetItem(fieldTypes->at(index).getFieldTypeName()));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,3,new QTableWidgetItem(placeholderText));
            for (int j=0;j<ui->editFieldsTableWidget->columnCount();j++){
                ui->editFieldsTableWidget->item(ui->editFieldsTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->editFieldsTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
            }
        }else{
            QString message="";
            if(flag)
                message+="字段名已存在!";
            if(!addFieldName->isValid())
                message+="字段名不合法!";
            QMessageBox::warning(this,"警告",message);
        }
    }else if(currentMode==1){
        if(addFieldName->isValid()&&(chosenType!=nullptr&&!chosenType->has(addFieldName->text()))){
            //获取item信息
            QString itemName=addFieldName->text();
            QString placeholderText=addFieldTip->text();
            int index=ui->addFieldComboBox->currentIndex();
            AbstractCustomField::controllerTypeChoices controllerType=fieldTypes->at(index).getFieldControllerType();
            AbstractCustomField::dataTypeChoices dataType=fieldTypes->at(index).getFieldDataType();
            AbstractCustomField::isRequiredChoices isRequired=fieldTypes->at(index).getFieldIsRequired();
            AbstractCustomField* temp=nullptr;
            //新建abstractCustomField
            if(controllerType==AbstractCustomField::LINEEDIT)
                temp=new customLineEdit(itemName,isRequired,dataType,this);
            else if(controllerType==AbstractCustomField::COMBOBOX)
                temp=new customComboBox(itemName,isRequired,dataType,this);
            if(temp!=nullptr&&placeholderText!=""){
                temp->setPlaceholderText(placeholderText);
            }
            //新建复选框
            QCheckBox *checkItem = new QCheckBox("是否必填",this);
            checkItem->setChecked(temp->getIsRequired());
            checkItem->setObjectName("isReqiuredCheckBox"+QString::number(ui->editFieldsTableWidget->rowCount()-1));
            connect(checkItem,SIGNAL(toggled(bool)),this,SLOT(onIsReqiuredCheckBoxToggled(bool)));
            temp->setIsRequiredCheckBox(checkItem);
            temp->setFieldTypeName(fieldTypes->at(index).getFieldTypeName());
            //加入到chosenType中
            chosenType->append(temp);
            //添加到tableWidget中
            for(int row = 0;row <= ui->editFieldsTableWidget->rowCount();row++)
                ui->editFieldsTableWidget->removeRow(0);
            for(int i = 0;i<chosenType->count();i++)
            {
                ui->editFieldsTableWidget->insertRow(ui->editFieldsTableWidget->rowCount());
                ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,0,new QTableWidgetItem(""));
                ui->editFieldsTableWidget->setCellWidget(ui->editFieldsTableWidget->rowCount()-1,0,chosenType->at(i)->getIsRequiredCheckBox());
                ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,1,new QTableWidgetItem(chosenType->at(i)->getFieldName()));
                ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,2,new QTableWidgetItem(chosenType->at(i)->getFieldTypeName()));
                ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,3,new QTableWidgetItem(chosenType->at(i)->getPlaceholderText()));
                for (int j=0;j<ui->editFieldsTableWidget->columnCount();j++){
                    ui->editFieldsTableWidget->item(ui->editFieldsTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->editFieldsTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
                }
            }
            //            qDebug()<<ui->editFieldsTableWidget->rowCount();
            //            ui->editFieldsTableWidget->insertRow(ui->editFieldsTableWidget->rowCount());
            //            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,0,new QTableWidgetItem(""));
            //            ui->editFieldsTableWidget->setCellWidget(ui->editFieldsTableWidget->rowCount()-1,0,checkItem);
            //            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,1,new QTableWidgetItem(itemName));
            //            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,2,new QTableWidgetItem(itemTypes->at(index).getFieldTypeName()));
            //            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,3,new QTableWidgetItem(placeholderText));
            //            for (int j=0;j<ui->editFieldsTableWidget->columnCount();j++){
            //                ui->editFieldsTableWidget->item(ui->editFieldsTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            //                ui->editFieldsTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
            //            }
        }else{
            QString message="";
            if(chosenType!=nullptr&&chosenType->has(addFieldName->text()))
                message+="字段名已存在!";
            if(!addFieldName->isValid())
                message+="字段名不合法!";
            QMessageBox::warning(this,"警告",message);
        }
    }
}
QStringList groupTypeManagerDialog::getFieldTypeNameList() const{
    Widget* parent=(Widget*)this->parent();
    FieldTypes fieldTypes=parent->fieldTypes;
    QStringList list;
    for(int i=0;i<fieldTypes.count();i++)
        list<<fieldTypes[i].getFieldTypeName();
    return list;
}
void groupTypeManagerDialog::onIsReqiuredCheckBoxToggled(bool isRequired){
    QCheckBox* send=(QCheckBox*)sender();
    int index=send->objectName().midRef(18,10000).toInt();
    qDebug()<<index;
    tempFields[index]->setIsRequired((AbstractCustomField::isRequiredChoices)isRequired);
}
