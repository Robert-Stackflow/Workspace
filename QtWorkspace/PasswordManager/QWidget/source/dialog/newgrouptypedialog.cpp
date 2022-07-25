#include "dialog/newgrouptypedialog.h"
#include "customField/customComboBox.h"
#include "customField/customTextEdit.h"
#include "widget.h"
#include "util/data.h"
#include "ui_newgrouptypedialog.h"
#pragma warning (disable:4100)
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
using namespace Data;
newGroupTypeDialog::newGroupTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGroupTypeDialog)
{
    ui->setupUi(this);
    initDialog();
    //添加自定义Field控件
    typeName=new customLineEdit("类型名称",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
    ui->typeNameLayout->addWidget(typeName);
    addFieldName=new customLineEdit("字段名称",AbstractCustomField::REQUIRED,AbstractCustomField::NORMAL,this);
    addFieldName->setMaxLength(10);
    ui->addFieldNameLayout->addWidget(addFieldName);
    addFieldTip=new customLineEdit("填写提示",AbstractCustomField::OPTIONAL,AbstractCustomField::NORMAL,this);
    addFieldTip->setPlaceholderText("输入填写字段时的提示");
    ui->addFieldTipLayout->addWidget(addFieldTip);
    //设置tabWidget
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);
    //设置添加字段的下拉选择框
    ui->addFieldComboBox->addItems(sharedData.fieldTypeList.getNames());
    //设置typeManagerTableWidget
    typeManagerTableWidgetHeader<<"类型名称"<<"字段数目"<<"创建时间"<<"修改时间"<<"描述";
    ui->typeManagerTableWidget->setAlternatingRowColors(true);//设置行色交替
    ui->typeManagerTableWidget->viewport()->installEventFilter(this);//事件过滤器
    ui->typeManagerTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->typeManagerTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选择整行
    ui->typeManagerTableWidget->setColumnCount(typeManagerTableWidgetHeader.size());//设置列数
    ui->typeManagerTableWidget->setHorizontalHeaderLabels(typeManagerTableWidgetHeader);//设置列表头
    ui->typeManagerTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->typeManagerTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->typeManagerTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置列表头居中对齐
    ui->typeManagerTableWidget->verticalHeader()->hide();//隐藏行表头
    ui->typeManagerTableWidget->verticalHeader()->setDefaultSectionSize(45);//设置行高
    //设置editFieldsTableWidget
    editFieldsTableWidgetHeader<<"是否必填"<<"字段名称"<<"字段类型"<<"填写提示";
    ui->editFieldsTableWidget->setAlternatingRowColors(true);//设置行色交替
    ui->editFieldsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->editFieldsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选择整行
    ui->editFieldsTableWidget->setColumnCount(editFieldsTableWidgetHeader.size());//设置列数
    ui->editFieldsTableWidget->setHorizontalHeaderLabels(editFieldsTableWidgetHeader);//设置列表头
    ui->editFieldsTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->editFieldsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->editFieldsTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//设置列表头居中对齐
    ui->editFieldsTableWidget->verticalHeader()->hide();//隐藏行表头
    ui->editFieldsTableWidget->verticalHeader()->setDefaultSectionSize(45);//设置行高
    //绑定槽函数
    //自定义信号槽
    connect(this,SIGNAL(groupTypeCountChanged()),parent,SLOT(onGroupTypeCountChanged()));
    connect(this,SIGNAL(typeManagerTableWidgetClicked()),this,SLOT(onTypeManagerTableWidgetClicked()));
    //分组管理各按钮
    connect(ui->editTypeButton,SIGNAL(clicked()),this,SLOT(onEditTypeClicked()));
    connect(ui->deleteTypeButton,SIGNAL(clicked()),this,SLOT(onDeleteTypeClicked()));
    connect(ui->copyTypeButton,SIGNAL(clicked()),this,SLOT(onCopyTypeClicked()));
    connect(ui->newTypeButton,SIGNAL(clicked()),this,SLOT(onNewTypeClicked()));
    //确认与取消
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(onCancelClicked()));
    connect(ui->confirm,SIGNAL(clicked()),this,SLOT(onConfirmClicked()));
    //添加字段按钮
    connect(ui->addFieldButton,SIGNAL(clicked()),this,SLOT(onAddFieldClicked()));
}

newGroupTypeDialog::~newGroupTypeDialog()
{
    delete ui;
}
void newGroupTypeDialog::initDialog()
{
    //删除默认标题栏
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
    //设置标题栏位置与大小
    m_titleBar->setFixedWidth(ui->frame->width());
    m_titleBar->setGeometry(m_titleBar->geometry().x()+6,m_titleBar->geometry().y(),m_titleBar->width(),m_titleBar->height());
    //设定阴影效果
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setColor(QColor(128,128,128,255));
    shadowEffect->setBlurRadius(20);
    shadowEffect->setOffset(0, 0);
    ui->frame->setGraphicsEffect(shadowEffect);
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
void newGroupTypeDialog::loadGroupTypes(){
    for(int i=0;i<sharedData.groupTypeList.count();i++)
    {
        GroupType* groupType=sharedData.groupTypeList[i];
        ui->typeManagerTableWidget->insertRow(ui->typeManagerTableWidget->rowCount());
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,0,new QTableWidgetItem(groupType->getGroupTypeName()));
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(groupType->count())));
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,2,new QTableWidgetItem(groupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss")));
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,3,new QTableWidgetItem(groupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")));
        ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,4,new QTableWidgetItem(groupType->getDescribe()));
        for (int j=0;j<ui->typeManagerTableWidget->columnCount();j++){
            ui->typeManagerTableWidget->item(ui->typeManagerTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->typeManagerTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
        }
    }
    emit groupTypeCountChanged();
}
bool newGroupTypeDialog::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->typeManagerTableWidget->viewport())
    {
        if (e->type() == QEvent::MouseButtonPress){
            emit typeManagerTableWidgetClicked();
        }
    }
    return QWidget::eventFilter(obj,e);
}
void newGroupTypeDialog::closeEvent(QCloseEvent* event)
{
    //关闭窗口时，重置为类型管理页，并给变量赋空值
    currentMode=NORMAL;
    tempFields.clear();
    newGroupType=nullptr;
    currentGroupType=nullptr;
    ui->tabWidget->setCurrentIndex(0);
    m_titleBar->setWindowTitle("类型管理");
}
void newGroupTypeDialog::onTypeManagerTableWidgetClicked(){
    int x=ui->typeManagerTableWidget->mapFromGlobal(QCursor::pos()).x();
    int y=ui->typeManagerTableWidget->mapFromGlobal(QCursor::pos()).y()-ui->typeManagerTableWidget->horizontalHeader()->height();
    QPoint point=QPoint(x,y);
    currentRow=ui->typeManagerTableWidget->indexAt(point).row();
    if(currentRow!=-1)
        ui->chosen->setText(ui->typeManagerTableWidget->item(currentRow,0)->text());
    else
        ui->chosen->setText("未选中");
}
void newGroupTypeDialog::onEditTypeClicked(){
    if(currentRow==-1){
        QMessageBox::warning(this,"警告","未选中类型!");
    }else{
        //获取当前GroupType
        currentGroupType=sharedData.groupTypeList[currentRow];
        //加载currentGroupType信息
        tempFields.clear();
        addFieldTip->clear();
        addFieldName->clear();
        chosenOldName=currentGroupType->getGroupTypeName();
        typeName->setText(currentGroupType->getGroupTypeName());
        ui->describe->setText(currentGroupType->getDescribe());
        //加载currentGroupType中的字段
        //加载字段到tempFields
        for(int i=0;i<currentGroupType->count();i++)
            tempFields<<currentGroupType->at(i);
        //清除editFieldsTableWidget内容
        ui->editFieldsTableWidget->setRowCount(0);
        //循环加载字段
        for(int i = 0;i<currentGroupType->count();i++){
            ui->editFieldsTableWidget->insertRow(ui->editFieldsTableWidget->rowCount());
            //新建复选框
            QCheckBox *checkItem = new QCheckBox("是否必填",this);
            if(tempFields[i]!=nullptr)
                checkItem->setChecked(tempFields[i]->getIsRequired());
            checkItem->setObjectName("isRequiredCheckBox_"+QString::number(ui->editFieldsTableWidget->rowCount()-1));
            connect(checkItem,SIGNAL(toggled(bool)),this,SLOT(onIsReqiuredCheckBoxToggled(bool)));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,0,new QTableWidgetItem(""));
            ui->editFieldsTableWidget->setCellWidget(ui->editFieldsTableWidget->rowCount()-1,0,checkItem);
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,1,new QTableWidgetItem(tempFields[i]->getFieldName()));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,2,new QTableWidgetItem(tempFields[i]->getFieldTypeName()));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,3,new QTableWidgetItem(tempFields[i]->getPlaceholderText()));
            for (int j=0;j<ui->editFieldsTableWidget->columnCount();j++){
                ui->editFieldsTableWidget->item(ui->editFieldsTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->editFieldsTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
            }
        }
        //设置当前模式为编辑
        currentMode=EDITGROUPTYPE;
        ui->tabWidget->setCurrentIndex(1);
        m_titleBar->setWindowTitle("编辑类型\""+typeName->text()+"\"");
    }
}
void newGroupTypeDialog::onDeleteTypeClicked(){
    if(currentRow==-1){
        QMessageBox::warning(this,"警告","未选中类型!");
    }else{
        QMessageBox::warning(this,"类型删除警告","警告:删除该类型后,所有关联该类型的分组均将被删除,请提前进行备份，以免数据丢失!\n");
        int choice=QMessageBox::question(this,"确认删除","是否确认删除类型\""+typeName->text()+"\"");
        if(choice==QMessageBox::Yes){
        }
    }
}
void newGroupTypeDialog::onCopyTypeClicked(){
    if(currentRow==-1){
        QMessageBox::warning(this,"警告","未选中类型!");
    }else{
        //获取当前GroupType
        currentGroupType=sharedData.groupTypeList[currentRow];
        //加载currentGroupType信息
        addFieldTip->clear();
        addFieldName->clear();
        ui->describe->setText(currentGroupType->getDescribe());
        typeName->setText(currentGroupType->getGroupTypeName()+"_copy");
        //清除editFieldsTableWidget内容
        ui->editFieldsTableWidget->setRowCount(0);
        //循环加载字段
        //加载字段到tempFields
        for(int i=0;i<currentGroupType->count();i++)
            tempFields<<currentGroupType->at(i)->clone();
        for(int i = 0;i<currentGroupType->count();i++){
            ui->editFieldsTableWidget->insertRow(ui->editFieldsTableWidget->rowCount());
            //新建复选框
            QCheckBox *checkItem = new QCheckBox("是否必填",this);
            if(tempFields[i]!=nullptr)
                checkItem->setChecked(tempFields[i]->getIsRequired());
            checkItem->setObjectName("isRequiredCheckBox_"+QString::number(ui->editFieldsTableWidget->rowCount()-1));
            connect(checkItem,SIGNAL(toggled(bool)),this,SLOT(onIsReqiuredCheckBoxToggled(bool)));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,0,new QTableWidgetItem(""));
            ui->editFieldsTableWidget->setCellWidget(ui->editFieldsTableWidget->rowCount()-1,0,checkItem);
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,1,new QTableWidgetItem(tempFields[i]->getFieldName()));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,2,new QTableWidgetItem(tempFields[i]->getFieldTypeName()));
            ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,3,new QTableWidgetItem(tempFields[i]->getPlaceholderText()));
            for (int j=0;j<ui->editFieldsTableWidget->columnCount();j++){
                ui->editFieldsTableWidget->item(ui->editFieldsTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                ui->editFieldsTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
            }
        }
        //设置当前模式为新建
        currentMode=NEWGROUPTYPE;
        ui->tabWidget->setCurrentIndex(1);
        m_titleBar->setWindowTitle("复制类型\""+typeName->text()+"\"至新建类型");
    }
}
void newGroupTypeDialog::onNewTypeClicked(){
    //清除相关控件内容
    typeName->clear();
    addFieldName->clear();
    addFieldTip->clear();
    ui->describe->clear();
    //清除editFieldsTableWidget内容
    for(int row = 0;row <= ui->editFieldsTableWidget->rowCount();row++)
        ui->editFieldsTableWidget->removeRow(0);
    //设置当前模式为新建
    currentMode=NEWGROUPTYPE;
    ui->tabWidget->setCurrentIndex(1);
    m_titleBar->setWindowTitle("新建类型");
}
void newGroupTypeDialog::onCancelClicked(){
    if(currentMode==0){
        int choice=QMessageBox::question(this,"取消新建","是否确认取消新建");
        if(choice==QMessageBox::Yes){
            ui->tabWidget->setCurrentIndex(0);
            m_titleBar->setWindowTitle("类型管理");
        }
    }else if(currentMode==1){
        int choice=QMessageBox::question(this,"放弃修改","是否确认放弃修改");
        if(choice==QMessageBox::Yes){
            ui->tabWidget->setCurrentIndex(0);
            m_titleBar->setWindowTitle("类型管理");
        }
    }
    currentMode=NORMAL;
    tempFields.clear();
    newGroupType=nullptr;
    currentGroupType=nullptr;
}
void newGroupTypeDialog::onConfirmClicked(){
    if(currentMode==0){
        //仅当typeName合法、类型名称不重复、字段数不少于2时合法
        if(typeName->isValid()&&!sharedData.groupTypeList.has(typeName->text())&&tempFields.count()>=2){
            int choice=QMessageBox::question(this,"确认新建","是否确认新建类型\""+typeName->text()+"\"");
            if(choice==QMessageBox::Yes){
                //新建newGroupType并添加到sharedData.groupTypeList中
                newGroupType=new GroupType(typeName->text(),ui->describe->toPlainText(),tempFields);
                sharedData.groupTypeList<<newGroupType;
                //添加到数据库中
                sharedData.database.setDatabaseName(dataPathGetter.getCurrentAccountDataBasePath());
                QSqlQuery query(sharedData.database);
                if(!sharedData.database.open()){
                    QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
                    return;
                }else{
                    QString newGroupTypeTableName=dataBaseTableNameGetter.getGroupTypeTableName(newGroupType->getGroupTypeName());
                    if(!sharedData.database.tables().contains(newGroupTypeTableName)){
                        //向sharedData.groupTypeList表插入数据
                        query.prepare("insert into "+dataBaseTableNameGetter.getGroupTypesTableName()+" (groupTypeName,fieldCount,createTime,lastEditTime,describe)"
                                                                                                              "VALUES (:1,:2,:3,:4,:5)");
                        query.bindValue(":1",newGroupType->getGroupTypeName());
                        query.bindValue(":2",newGroupType->count());
                        query.bindValue(":3",newGroupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
                        query.bindValue(":4",newGroupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"));
                        query.bindValue(":5",newGroupType->getDescribe());
                        query.exec();
                        //创建记录类型中字段信息的表
                        query.exec("create table "+newGroupTypeTableName+" (fieldName int,isRequired int,fieldTypeName varchar(200),placeholderText varchar(200))");
                        //添加字段信息记录
                        for(int i=0;i<newGroupType->count();i++){
                            query.prepare("insert into "+newGroupTypeTableName+" (fieldName,isRequired,fieldTypeName,placeholderText)"
                                                                               "VALUES (:1,:2,:3,:4)");
                            query.bindValue(":1",newGroupType->at(i)->getFieldName());
                            query.bindValue(":2",newGroupType->at(i)->getIsRequired());
                            query.bindValue(":3",newGroupType->at(i)->getFieldTypeName());
                            query.bindValue(":4",newGroupType->at(i)->getPlaceholderText());
                            query.exec();
                        }
                        sharedData.database.close();
                    }
                }
                //发射类型数目改变的信号
                emit groupTypeCountChanged();
                //向typeManagerTableWidget中添加新行
                ui->typeManagerTableWidget->insertRow(ui->typeManagerTableWidget->rowCount());
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,0,new QTableWidgetItem(newGroupType->getGroupTypeName()));
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(newGroupType->count())));
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,2,new QTableWidgetItem(newGroupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss")));
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,3,new QTableWidgetItem(newGroupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")));
                ui->typeManagerTableWidget->setItem(ui->typeManagerTableWidget->rowCount()-1,4,new QTableWidgetItem(newGroupType->getDescribe()));
                //设置typeManagerTableWidget居中显示
                for (int j=0;j<ui->typeManagerTableWidget->columnCount();j++){
                    ui->typeManagerTableWidget->item(ui->typeManagerTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->typeManagerTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
                }
                //返回类型管理页
                currentMode=NORMAL;
                ui->tabWidget->setCurrentIndex(0);
                m_titleBar->setWindowTitle("类型管理");
                tempFields.clear();
                newGroupType=nullptr;
                currentGroupType=nullptr;
            }
        }else{
            QString message="无法创建类型:\n";
            if(!typeName->isValid())
                message+="名称不合法!\n";
            if(sharedData.groupTypeList.has(typeName->text()))
                message+="类型名已存在!\n";
            if(tempFields.count()<2)
                message+="字段数目不得小于2!";
            QMessageBox::warning(this,"警告",message);
        }
    }else if(currentMode==1){
        if(typeName->isValid()&&!(typeName->text()!=chosenOldName&&sharedData.groupTypeList.has(typeName->text()))&&(currentGroupType!=nullptr&&currentGroupType->count()>=2)){
            int choice=QMessageBox::question(this,"确认修改","是否确认保存修改类型\""+typeName->text()+"\"");
            if(choice==QMessageBox::Yes){
                //更新currentGroupType信息
                QString currentGroupOldName=currentGroupType->getGroupTypeName();
                currentGroupType->setLastEditTime();
                currentGroupType->setGroupTypeName(typeName->text());
                currentGroupType->setDescribe(ui->describe->toPlainText());
                currentGroupType->setCustomFieldList(tempFields);
                //更新数据库
                sharedData.database.setDatabaseName(dataPathGetter.getCurrentAccountDataBasePath());
                QSqlQuery query(sharedData.database);
                if(!sharedData.database.open()){
                    QMessageBox::critical(0, QObject::tr("Database Connection Error!"), sharedData.database.lastError().text());
                    return;
                }else{
                    QString editGroupTypeTableOldName=dataBaseTableNameGetter.getGroupTypeTableName(currentGroupOldName);
                    QString editGroupTypeTableName=dataBaseTableNameGetter.getGroupTypeTableName(currentGroupType->getGroupTypeName());
                    if(!sharedData.database.tables().contains(editGroupTypeTableOldName)){
                    }else{
                        //更新sharedData.groupTypeList
                        QString sql=QString("update "+dataBaseTableNameGetter.getGroupTypesTableName()+" set groupTypeName='%1',fieldCount='%2',lastEditTime='%3',describe='%4' where createTime='%5' ")
                                .arg(currentGroupType->getGroupTypeName())
                                .arg(QString::number(currentGroupType->count()))
                                .arg(currentGroupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss"))
                                .arg(currentGroupType->getDescribe())
                                .arg(currentGroupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss"));
                        query.exec(sql);
                        //更新记录类型中字段信息的表
                        query.exec("drop table "+editGroupTypeTableOldName);
                        query.exec("create table "+editGroupTypeTableName+" (fieldName int,isRequired int,fieldTypeName varchar(200),placeholderText varchar(200))");
                        //添加字段信息记录
                        for(int i=0;i<currentGroupType->count();i++){
                            query.prepare("insert into "+editGroupTypeTableName+" (fieldName,isRequired,fieldTypeName,placeholderText)"
                                                                                "VALUES (:1,:2,:3,:4)");
                            query.bindValue(":1",currentGroupType->at(i)->getFieldName());
                            query.bindValue(":2",currentGroupType->at(i)->getIsRequired());
                            query.bindValue(":3",currentGroupType->at(i)->getFieldTypeName());
                            query.bindValue(":4",currentGroupType->at(i)->getPlaceholderText());
                            query.exec();
                        }
                        sharedData.database.close();
                    }
                }
                //在typeManagerTableWidget中编辑信息
                ui->typeManagerTableWidget->setItem(currentRow,0,new QTableWidgetItem(currentGroupType->getGroupTypeName()));
                ui->typeManagerTableWidget->setItem(currentRow,1,new QTableWidgetItem(QString::number(currentGroupType->count())));
                ui->typeManagerTableWidget->setItem(currentRow,2,new QTableWidgetItem(currentGroupType->getCreateTime().toString("yyyy-MM-dd hh:mm:ss")));
                ui->typeManagerTableWidget->setItem(currentRow,3,new QTableWidgetItem(currentGroupType->getLastEditTime().toString("yyyy-MM-dd hh:mm:ss")));
                ui->typeManagerTableWidget->setItem(currentRow,4,new QTableWidgetItem(currentGroupType->getDescribe()));
                //设置typeManagerTableWidget居中显示
                for (int j=0;j<ui->typeManagerTableWidget->columnCount();j++){
                    ui->typeManagerTableWidget->item(currentRow,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->typeManagerTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
                }
                //返回类型管理页
                currentMode=NORMAL;
                ui->tabWidget->setCurrentIndex(0);
                m_titleBar->setWindowTitle("类型管理");
                tempFields.clear();
                newGroupType=nullptr;
                currentGroupType=nullptr;
            }
        }else{
            QString message="无法创建类型:\n";
            if(!typeName->isValid())
                message+="名称不合法!\n";
            if(typeName->text()!=chosenOldName&&sharedData.groupTypeList.has(typeName->text()))
                message+="类型名已存在!\n";
            if((currentGroupType!=nullptr&&currentGroupType->count()<2))
                message+="字段数目不得小于2!";
            QMessageBox::warning(this,"警告",message);
        }
    }
}
void newGroupTypeDialog::onAddFieldClicked(){
    //flag判断字段名是否重复
    bool IsRedundant=false;
    for(int i=0;i<tempFields.count();i++)
        if(tempFields[i]->getFieldName()==addFieldName->text())
            IsRedundant=true;
    bool flag=addFieldName->isValid()&&!IsRedundant;
    //当字段名合法且不重复时加入字段
    if(flag){
        //获取field信息
        QString newFieldName=addFieldName->text();
        QString newFieldPlaceholderText=addFieldTip->text();
        int index=ui->addFieldComboBox->currentIndex();
        AbstractCustomField::controllerTypeChoices controllerType=sharedData.fieldTypeList[index].getFieldControllerType();
        AbstractCustomField::dataTypeChoices dataType=sharedData.fieldTypeList[index].getFieldDataType();
        AbstractCustomField::isRequiredChoices isRequired=sharedData.fieldTypeList[index].getFieldIsRequired();
        AbstractCustomField* tempNewField=nullptr;
        //新建abstractCustomField
        if(controllerType==AbstractCustomField::LINEEDIT)
            tempNewField=new customLineEdit(newFieldName,isRequired,dataType,this);
        else if(controllerType==AbstractCustomField::COMBOBOX)
            tempNewField=new customComboBox(newFieldName,isRequired,dataType,this);
        else if(controllerType==AbstractCustomField::TEXTEDIT)
            tempNewField=new customTextEdit(newFieldName,isRequired,dataType,this);
        if(tempNewField!=nullptr&&newFieldPlaceholderText!=""){
            qDebug()<<"placeholder"<<newFieldPlaceholderText;
            tempNewField->setPlaceholderText(newFieldPlaceholderText);
        }
        //加入tempNewField到tempFields中
        tempFields<<tempNewField;
        //添加到tableWidget中
        ui->editFieldsTableWidget->insertRow(ui->editFieldsTableWidget->rowCount());
        //新建复选框
        QCheckBox *checkItem = new QCheckBox("是否必填",this);
        if(tempNewField!=nullptr)
            checkItem->setChecked(tempNewField->getIsRequired());
        checkItem->setObjectName("isRequiredCheckBox_"+QString::number(ui->editFieldsTableWidget->rowCount()-1));
        connect(checkItem,SIGNAL(toggled(bool)),this,SLOT(onIsReqiuredCheckBoxToggled(bool)));
        tempNewField->setFieldTypeName(sharedData.fieldTypeList[index].getFieldTypeName());
        ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,0,new QTableWidgetItem(""));
        ui->editFieldsTableWidget->setCellWidget(ui->editFieldsTableWidget->rowCount()-1,0,checkItem);
        ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,1,new QTableWidgetItem(tempNewField->getFieldName()));
        ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,2,new QTableWidgetItem(sharedData.fieldTypeList[index].getFieldTypeName()));
        ui->editFieldsTableWidget->setItem(ui->editFieldsTableWidget->rowCount()-1,3,new QTableWidgetItem(tempNewField->getPlaceholderText()));
        for (int j=0;j<ui->editFieldsTableWidget->columnCount();j++){
            ui->editFieldsTableWidget->item(ui->editFieldsTableWidget->rowCount()-1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->editFieldsTableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
        }
    }else{
        QString message="无法添加字段:\n";
        if(IsRedundant)
            message+="字段名已存在!";
        if(!addFieldName->isValid())
            message+="字段名不合法!";
        QMessageBox::warning(this,"警告",message);
    }
}
void newGroupTypeDialog::onIsReqiuredCheckBoxToggled(bool isRequired){
    QCheckBox* send=(QCheckBox*)sender();
    int index=send->objectName().split("_")[1].toInt();
    tempFields[index]->setIsRequired((AbstractCustomField::isRequiredChoices)isRequired);
    ui->editFieldsTableWidget->setItem(index,1,new QTableWidgetItem(tempFields[index]->getFieldName()));
    ui->editFieldsTableWidget->item(index,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}
