#include "include/mainwindow.h"
#include "ui_mainwindow.h"
int Library::times=0;
Library::Library(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Library)
{
    ui->setupUi(this);
    this->setWindowTitle("谜题库");
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet+= QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
    windowstate=0;
    insertDialog=new Insert(this);
    insertDialog->ui->tableinlibBox->setCurrentIndex(-1);
    insertDialog->ui->tableinlibtypeBox->setCurrentIndex(-1);
    insertDialog->ui->puzzleinlibBox->setCurrentIndex(-1);
    insertDialog->ui->puzzleinlibtypeBox->setCurrentIndex(-1);
    insertDialog->ui->puzzleintableBox->setCurrentIndex(-1);
    IniFrame();
    IniTableWidget();
    IniLibraryWidget();
    IniLibrariesWidget();
    main->setCurrentIndex(0);
    loadUserFile();
}

Library::~Library()
{
    delete ui;
}
void Library::IniFrame()//初始化界面框架
{
    MainWindow *p= (MainWindow *)parentWidget();
    windowLayout = new QVBoxLayout;
    setLayout(windowLayout);
    //Selection of the puzzle library
    mainLabel=new QLabel("视图");
    QStringList mainList;
    mainList<<"所有谜题库"<<"单个谜题库"<<"单个谜题表";
    main=new QComboBox();
    main->addItems(mainList);
    main->setCurrentIndex(-1);

    fieldLabel=new QLabel("类型");
    QStringList fieldList;
    for(int i=0;i<6;i++)
        fieldList<<p->Menus[0].sub[0]->acts[i]->text();
    field=new QComboBox();
    field->addItems(fieldList);
    insertDialog->ui->puzzleinlibtypeBox->addItems(fieldList);
    insertDialog->ui->tableinlibtypeBox->addItems(fieldList);

    libLabel=new QLabel("谜题库");
    QStringList libList;
    lib=new QComboBox();
    lib->addItems(libList);

    contentLabel=new QLabel("选择");
    content=new QComboBox();

    lib->setCurrentIndex(0);
    field->setCurrentIndex(0);
    content->setCurrentIndex(0);

    function=new QPushButton();
    function->setHidden(true);
    newButton=new QPushButton();
    newButton->setText("新建");
    findEdit=new QLineEdit();
    findEdit->setPlaceholderText("输入表名，备注或谜题编号以查找");
    find=new QPushButton();
    find->setText("查找");
    aboutLibrary = new QHBoxLayout();
    aboutLibrary->addWidget(mainLabel);
    aboutLibrary->addWidget(main);
    aboutLibrary->addWidget(fieldLabel);
    aboutLibrary->addWidget(field);
    aboutLibrary->addWidget(libLabel);
    aboutLibrary->addWidget(lib);
    aboutLibrary->addWidget(contentLabel);
    aboutLibrary->addWidget(content);
    aboutLibrary->addWidget(function);
    aboutLibrary->addWidget(newButton);
    aboutLibrary->addWidget(findEdit);
    aboutLibrary->addWidget(find);
    windowLayout->addLayout(aboutLibrary);
}
void Library::IniTableWidget()//初始化单个谜题表的widget
{
    tableWidget=new QTableWidget(this);
    windowLayout->addWidget(tableWidget);
    tableWidget->setHidden(true);
    tableWidget->setAlternatingRowColors(true);
    tableWidget->verticalHeader()->setDefaultSectionSize(45);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setContextMenuPolicy(Qt::NoContextMenu);
    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ContextMenuRequested(QPoint)));
    connect(tableWidget->horizontalHeader(),SIGNAL(sectionClicked(int)),this, SLOT(onHeaderClicked(int)));
    QStringList TableHeader;
    TableHeader<<"谜题编号"<<"来源"<<"难度等级"<<"当前状态"<<"收藏状态"<<"谜题格局";
    tableWidget->setColumnCount(TableHeader.size());
    tableWidget->setHorizontalHeaderLabels(TableHeader);
    for(int i=0;i<tableWidget->columnCount();i++)
        tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}
void Library::IniLibraryWidget()//初始化单个谜题库的widget
{
    LibraryWidget=new QTableWidget(this);
    windowLayout->addWidget(LibraryWidget);
    LibraryWidget->setHidden(true);
    LibraryWidget->setAlternatingRowColors(true);
    LibraryWidget->verticalHeader()->setDefaultSectionSize(45);
    LibraryWidget->horizontalHeader()->setStretchLastSection(true);
    LibraryWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    LibraryWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    LibraryWidget->setContextMenuPolicy(Qt::NoContextMenu);
    LibraryWidget->verticalHeader()->hide();
    connect(LibraryWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ContextMenuRequested(QPoint)));
    connect(LibraryWidget->horizontalHeader(),SIGNAL(sectionClicked(int)),this, SLOT(onHeaderClicked(int)));
    QStringList LibraryHeader;
    LibraryHeader<<"表名"<<"备注"<<"类型"<<"平均难度"<<"完成率"<<"谜题数目"<<"创建时间";
    LibraryWidget->setColumnCount(LibraryHeader.size());
    LibraryWidget->setHorizontalHeaderLabels(LibraryHeader);
}
void Library::IniLibrariesWidget()//初始化所有谜题库的widget
{
    LibrariesWidget=new QTableWidget(this);
    windowLayout->addWidget(LibrariesWidget);
    LibrariesWidget->setAlternatingRowColors(true);
    LibrariesWidget->verticalHeader()->setDefaultSectionSize(45);
    LibrariesWidget->horizontalHeader()->setStretchLastSection(true);
    LibrariesWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    LibrariesWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    LibrariesWidget->setContextMenuPolicy(Qt::NoContextMenu);
    LibrariesWidget->verticalHeader()->hide();
    LibrariesWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(LibrariesWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ContextMenuRequested(QPoint)));
    connect(LibrariesWidget->horizontalHeader(),SIGNAL(sectionClicked(int)),this, SLOT(onHeaderClicked(int)));
    connect(main,SIGNAL(currentIndexChanged(int)),this,SLOT(mainView(int)));
    connect(field,SIGNAL(currentIndexChanged(int)),this,SLOT(fieldView(int)));
    connect(insertDialog->ui->tableinlibtypeBox,SIGNAL(currentIndexChanged(int)),this,SLOT(fieldView(int)));
    connect(insertDialog->ui->puzzleinlibtypeBox,SIGNAL(currentIndexChanged(int)),this,SLOT(fieldView(int)));
    connect(lib,SIGNAL(currentIndexChanged(int)),this,SLOT(libView(int)));
    connect(insertDialog->ui->tableinlibBox,SIGNAL(currentIndexChanged(int)),this,SLOT(libView(int)));
    connect(insertDialog->ui->puzzleinlibBox,SIGNAL(currentIndexChanged(int)),this,SLOT(libView(int)));
    connect(content,SIGNAL(currentIndexChanged(int)),this,SLOT(contentView(int)));
    connect(insertDialog->ui->puzzleintableBox,SIGNAL(currentIndexChanged(int)),this,SLOT(contentView(int)));
    QStringList LibrariesHeader;
    LibrariesHeader<<"库名"<<"备注"<<"类型"<<"平均难度"<<"完成率"<<"子表数目"<<"谜题数目"<<"创建时间"<<"文件地址";
    LibrariesWidget->setColumnCount(LibrariesHeader.size());
    LibrariesWidget->setHorizontalHeaderLabels(LibrariesHeader);
    for(int i=0;i<LibrariesWidget->columnCount();i++)
        LibrariesWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}
void Library::mainView(int index)//选择视图模式的槽函数，信号为main下拉选择框的index改变，参数为main下拉选择框的index
{
    //    if(activeWidget!=NULL)
    //        for (int i = 0;i<activeWidget->rowCount(); i++)
    //            activeWidget->setRowHidden(i,false);
    if(index==0)
    {
        //set Active Widget
        activeWidget=LibrariesWidget;
        activeWidget->viewport()->installEventFilter(this);
        //set layout
        fieldLabel->setHidden(true);
        field->setHidden(true);
        libLabel->setHidden(true);
        lib->setHidden(true);
        lib->setObjectName("lib");
        contentLabel->setHidden(true);
        content->setHidden(true);
        content->setObjectName("content");
        function->setHidden(false);
        function->setText("加载谜题库");
        connect(function,SIGNAL(clicked()),this,SLOT(LoadLibraries()));
        newButton->setText("新建谜题库");
        disconnect(newButton,SIGNAL(clicked()),this,SLOT(insertPuzzle()));
        disconnect(newButton,SIGNAL(clicked()),this,SLOT(insertTable()));
        connect(newButton,SIGNAL(clicked()),this,SLOT(insertLibrary()));
        tableWidget->setHidden(true);
        LibraryWidget->setHidden(true);
        LibrariesWidget->setHidden(false);
        //set widget
        TWMenu= new QMenu(LibrariesWidget);
        QList<QAction*> menuLibraries;
        QAction *openLibrary=new QAction("打开库");
        QAction *deleteLibrary=new QAction("删除库");
        QAction *openFolder=new QAction("打开文件夹");
        QAction *insertLibrary=new QAction("新建库");
        connect(insertLibrary,SIGNAL(triggered()),this,SLOT(insertLibrary()));
        connect(openLibrary,SIGNAL(triggered()),this,SLOT(openLibrary()));
        connect(deleteLibrary,SIGNAL(triggered()),this,SLOT(deleteLibrary()));
        connect(openFolder,SIGNAL(triggered()),this,SLOT(openFolder()));
        menuLibraries<<openLibrary<<insertLibrary<<deleteLibrary<<openFolder;
        TWMenu->addActions(menuLibraries);
        LibrariesWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        UpdateWidgetView();
    }
    else if(index==1)
    {
        //set Active Widget
        activeWidget=LibraryWidget;
        activeWidget->viewport()->installEventFilter(this);
        //set layout
        fieldLabel->setHidden(false);
        field->setHidden(false);
        libLabel->setHidden(false);
        lib->setHidden(false);
        contentLabel->setHidden(true);
        content->setHidden(true);
        function->setHidden(true);
        tableWidget->setHidden(true);
        LibraryWidget->setHidden(false);
        LibrariesWidget->setHidden(true);
        newButton->setText("新建谜题表");
        disconnect(newButton,SIGNAL(clicked()),this,SLOT(insertPuzzle()));
        connect(newButton,SIGNAL(clicked()),this,SLOT(insertTable()));
        disconnect(newButton,SIGNAL(clicked()),this,SLOT(insertLibrary()));
        TWMenu= new QMenu(LibraryWidget);
        QList<QAction*> menuLibrary;
        QAction *openTable=new QAction("打开表");
        QAction *deleteTable=new QAction("删除表");
        QAction *insertTable=new QAction("新建表");
        connect(insertTable,SIGNAL(triggered()),this,SLOT(insertTable()));
        connect(openTable,SIGNAL(triggered()),this,SLOT(openTable()));
        connect(deleteTable,SIGNAL(triggered()),this,SLOT(deleteTable()));
        menuLibrary<<openTable<<insertTable<<deleteTable;
        TWMenu->addActions(menuLibrary);
        LibraryWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        fieldView(0);
        libView(0);
        contentView(0);
        UpdateWidgetView();
    }
    else if(index==2)
    {
        //set Active Widget
        activeWidget=tableWidget;
        activeWidget->viewport()->installEventFilter(this);
        //set layout
        fieldLabel->setHidden(false);
        field->setHidden(false);
        libLabel->setHidden(false);
        lib->setHidden(false);
        contentLabel->setHidden(false);
        content->setHidden(false);
        function->setHidden(true);
        tableWidget->setHidden(false);
        LibraryWidget->setHidden(true);
        LibrariesWidget->setHidden(true);
        newButton->setText("新建谜题");
        connect(newButton,SIGNAL(clicked()),this,SLOT(insertPuzzle()));
        disconnect(newButton,SIGNAL(clicked()),this,SLOT(insertTable()));
        disconnect(newButton,SIGNAL(clicked()),this,SLOT(insertLibrary()));
        TWMenu= new QMenu(tableWidget);
        QList<QAction*> menuTable;
        QAction *collectPuzzle=new QAction("收藏谜题");
        QAction *loadPuzzle=new QAction("载入谜题");
        QAction *copyPuzzle=new QAction("复制谜题");
        QAction *deletePuzzle=new QAction("删除谜题");
        QAction *insertPuzzle=new QAction("新建谜题");
        menuTable<<collectPuzzle<<loadPuzzle<<copyPuzzle<<insertPuzzle<<deletePuzzle;
        connect(loadPuzzle,SIGNAL(triggered()),this,SLOT(loadPuzzle()));
        connect(copyPuzzle,SIGNAL(triggered()),this,SLOT(copyPuzzle()));
        connect(deletePuzzle,SIGNAL(triggered()),this,SLOT(deletePuzzle()));
        connect(insertPuzzle,SIGNAL(triggered()),this,SLOT(insertPuzzle()));
        TWMenu->addActions(menuTable);
        tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        fieldView(0);
        libView(0);
        contentView(0);
        UpdateWidgetView();
    }
    initMap();
}
void Library::fieldView(int index)//根据谜题库类型改变谜题库combobox内容的槽函数
{
    QComboBox *send=(QComboBox *)sender();
    if(windowstate==3&&insertDialog->ui->puzzleinlibtypeBox!=NULL&&send==insertDialog->ui->puzzleinlibtypeBox)
    {
        field->setCurrentIndex(insertDialog->ui->puzzleinlibtypeBox->currentIndex());
        insertDialog->ui->tableinlibtypeBox->setCurrentIndex(insertDialog->ui->puzzleinlibtypeBox->currentIndex());
    }
    else if(windowstate==0&&field!=NULL&&send==field)
    {
        insertDialog->ui->puzzleinlibtypeBox->setCurrentIndex(field->currentIndex());
        insertDialog->ui->tableinlibtypeBox->setCurrentIndex(field->currentIndex());
    }
    else if(windowstate==2&&insertDialog->ui->tableinlibtypeBox!=NULL&&send==insertDialog->ui->tableinlibtypeBox)
    {
        field->setCurrentIndex(insertDialog->ui->tableinlibtypeBox->currentIndex());
        insertDialog->ui->puzzleinlibtypeBox->setCurrentIndex(insertDialog->ui->tableinlibtypeBox->currentIndex());
    }
    if(lib)
        lib->clear();
    if(insertDialog->ui->tableinlibBox)
        insertDialog->ui->tableinlibBox->clear();
    if(insertDialog->ui->puzzleinlibBox)
        insertDialog->ui->puzzleinlibBox->clear();
    if(content)
        content->clear();
    if(insertDialog->ui->puzzleintableBox)
        insertDialog->ui->puzzleintableBox->clear();
    for(int i=0;i<file.size();i++)
    {
        if(index==0||index==file[i]->type)
        {
            lib->addItem(file[i]->fileInfo.fileName());
            insertDialog->ui->tableinlibBox->addItem(file[i]->fileInfo.fileName());
            insertDialog->ui->puzzleinlibBox->addItem(file[i]->fileInfo.fileName());
        }
    }
    lib->setCurrentIndex(-1);
    lib->setCurrentIndex(0);
}
void Library::libView(int index)//根据谜题库改变谜题表combobox内容的槽函数，并使用LoadLibrary加载librarywidget视图
{
    QComboBox *send=(QComboBox *)sender();
    if(index==-1) return;
    if(windowstate==3&&insertDialog->ui->puzzleinlibBox!=NULL&&send==insertDialog->ui->puzzleinlibBox)
    {
        dbName=insertDialog->ui->puzzleinlibBox->currentText();
        insertDialog->ui->tableinlibBox->setCurrentIndex(insertDialog->ui->puzzleinlibBox->currentIndex());
        lib->setCurrentIndex(insertDialog->ui->puzzleinlibBox->currentIndex());
        //        content->setCurrentIndex(insertDialog->ui->puzzleintableBox->currentIndex());
    }
    else if(windowstate==0&&lib!=NULL&&send==lib)
    {
        dbName=lib->currentText();
        //        insertDialog->ui->puzzleintableBox->setCurrentIndex(content->currentIndex());
        insertDialog->ui->puzzleinlibBox->setCurrentIndex(lib->currentIndex());
        insertDialog->ui->tableinlibBox->setCurrentIndex(lib->currentIndex());
    }
    else if(windowstate==2&&insertDialog->ui->tableinlibBox!=NULL&&send==insertDialog->ui->tableinlibBox)
    {
        dbName=insertDialog->ui->tableinlibBox->currentText();
        lib->setCurrentIndex(insertDialog->ui->tableinlibBox->currentIndex());
        insertDialog->ui->puzzleinlibBox->setCurrentIndex(insertDialog->ui->tableinlibBox->currentIndex());
    }
    disconnect(insertDialog->ui->puzzleintableBox,SIGNAL(currentIndexChanged(int)),this,SLOT(contentView(int)));
    disconnect(content,SIGNAL(currentIndexChanged(int)),this,SLOT(contentView(int)));
    QFileInfo info;
    content->clear();
    insertDialog->ui->puzzleintableBox->clear();
    for(int i=0;i<file.size();i++)
        if(file[i]->fileInfo.fileName()==dbName)
        {
            info=file[i]->fileInfo;
            for(int j=0;j<file[i]->tables.size();j++)
            {
                content->addItem(file[i]->tables[j]->tableName);
                insertDialog->ui->puzzleintableBox->addItem(file[i]->tables[j]->tableName);
            }
            connect(insertDialog->ui->puzzleintableBox,SIGNAL(currentIndexChanged(int)),this,SLOT(contentView(int)));
            connect(content,SIGNAL(currentIndexChanged(int)),this,SLOT(contentView(int)));
            content->setCurrentIndex(-1);
            insertDialog->ui->puzzleintableBox->setCurrentIndex(-1);
            content->setCurrentIndex(0);
            insertDialog->ui->puzzleintableBox->setCurrentIndex(0);
        }
    LoadLibrary(info);
}
void Library::contentView(int index)//根据谜题表使用LoadTable加载tablewidget视图的槽函数
{
    QComboBox *send=(QComboBox *)sender();
    if(index==-1) return;
    if(windowstate==3&&insertDialog->ui->puzzleintableBox!=NULL&&send==insertDialog->ui->puzzleintableBox)
    {
        dbName=insertDialog->ui->puzzleinlibBox->currentText();
        tableName=insertDialog->ui->puzzleintableBox->currentText();
        content->setCurrentIndex(insertDialog->ui->puzzleintableBox->currentIndex());
    }
    else if(windowstate==0&&content!=NULL&&send==content)
    {
        dbName=lib->currentText();
        tableName=content->currentText();
        insertDialog->ui->puzzleintableBox->setCurrentIndex(content->currentIndex());
    }
    QFileInfo info;
    for(int i=0;i<file.size();i++)
    {
        if(file[i]->fileInfo.fileName()==dbName)
            info=file[i]->fileInfo;
    }
    LoadTable(info,tableName);
}
void Library::UpdateWidgetView()//更新列表视图，使内容居中，且根据内容选择显示的文字
{
    MainWindow *p= (MainWindow *)parentWidget();
    for(int i=0;i<activeWidget->rowCount();i++)
        for(int j=0;j<activeWidget->columnCount();j++)
            activeWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    for(int i=0;i<LibrariesWidget->rowCount();i++)
    {
        int index=file[i]->type;
        LibrariesWidget->item(i,2)->setText(p->Menus[0].sub[0]->acts[index]->text());
    }
    for(int i=0;i<file.size();i++)
    {
        if(file[i]->fileInfo.fileName()==lib->currentText())
        {
            for(int j=0;j<LibraryWidget->rowCount()&&j<file[i]->tables.size();j++)
            {
                int index=file[i]->tables[j]->type;
                LibraryWidget->item(j,2)->setText(p->Menus[0].sub[0]->acts[index]->text());
            }
            break;
        }
    }
    for(int i=0;i<file.size();i++)
    {
        if(file[i]->fileInfo.fileName()==lib->currentText())
        {
            for(int j=0;j<file[i]->tables.size();j++)
            {
                if(content->currentText()==file[i]->tables[j]->tableName)
                {
                    for(int i=0;i<tableWidget->rowCount();i++)
                    {
                        int index=tableWidget->item(i,1)->text().toInt();
                        tableWidget->item(i,1)->setText(p->Menus[0].sub[0]->acts[index]->text());
                        index=tableWidget->item(i,2)->text().toInt();
                        tableWidget->item(i,2)->setText(p->Menus[0].sub[1]->acts[index]->text());
                        QStringList stateList;
                        stateList<<"未尝试"<<"未完成"<<"已完成";
                        tableWidget->item(i,3)->setText(stateList[tableWidget->item(i,3)->text().toInt()]);
                        QStringList collectionList;
                        collectionList<<"未收藏"<<"未收藏";
                        tableWidget->item(i,4)->setText(collectionList[tableWidget->item(i,4)->text().toInt()]);
                    }
                }
            }
        }
    }
    if(main->currentIndex()==0)
    {
        QStringList LibrariesHeader;
        LibrariesHeader<<"库名"<<"备注"<<"类型"<<"平均难度"<<"完成率"<<"子表数目"<<"谜题数目"<<"创建时间"<<"文件地址";
        LibrariesWidget->setColumnCount(LibrariesHeader.size());
        LibrariesWidget->setHorizontalHeaderLabels(LibrariesHeader);
        for(int i=0;i<LibrariesWidget->columnCount();i++)
            LibrariesWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    else if(main->currentIndex()==1)
    {
        QStringList LibraryHeader;
        LibraryHeader<<"表名"<<"备注"<<"类型"<<"平均难度"<<"完成率"<<"谜题数目"<<"创建时间";
        LibraryWidget->setColumnCount(LibraryHeader.size());
        LibraryWidget->setHorizontalHeaderLabels(LibraryHeader);
    }
    else if(main->currentIndex()==2)
    {
        QStringList TableHeader;
        TableHeader<<"谜题编号"<<"来源"<<"难度等级"<<"当前状态"<<"收藏状态"<<"谜题格局";
        tableWidget->setColumnCount(TableHeader.size());
        tableWidget->setHorizontalHeaderLabels(TableHeader);
        for(int i=0;i<tableWidget->columnCount();i++)
            tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
}
void Library::updateUserFile(const QString& filePath,const QString& tableName,const QString& puzzleId)//将用户加载的数据库文件信息和数据表文件信息存储到user.db中
{
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
    data.setDatabaseName("user.db");
    QSqlQuery query(data);
    if(!data.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
        return;
    }
    else
    {
        QStringList tables=data.tables();
        if(!tables.contains("Alibraries"))//创建总表
        {
            query.exec("create table Alibraries (name varchar(255),remarkName varchar(255),type int,averageLevel double,successRate double,tableCount int,puzzleCount int,createTime varchar(225),filePath varchar(255))");
        }
        query.exec("select filePath from Alibraries");
        QStringList filePaths;
        while (query.next())
        {
            QString name = query.value(0).toString();
            filePaths<<name;
        }
        for(int i=0;i<file.size();i++)
        {
            if(!filePaths.contains(file[i]->fileInfo.filePath()))
            {//如果libraries中不包含谜题库名字，插入谜题库信息
                query.prepare("INSERT INTO Alibraries (name,remarkName,type,averageLevel,successRate,tableCount,puzzleCount,createTime,filePath)"
                              "VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9)");
                query.bindValue(":1",file.at(i)->fileInfo.fileName());
                query.bindValue(":2",file.at(i)->remarkName);
                query.bindValue(":3",file.at(i)->type);
                query.bindValue(":4",file.at(i)->averageLevel);
                query.bindValue(":5",file.at(i)->successRate);
                query.bindValue(":6",file.at(i)->tableCount);
                query.bindValue(":7",file.at(i)->puzzleCount);
                query.bindValue(":8",file.at(i)->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":9",file.at(i)->fileInfo.filePath());
                query.exec();
            }
            QString newLibraryName='B'+file.at(i)->fileInfo.fileName().split('.')[0];
            if(!tables.contains(newLibraryName))
            {//如果数据库中不存在对应表，新建谜题库数据表
                query.exec("create table "+newLibraryName+" (name varchar(255),remarkName varchar(255),type int,averageLevel double,successRate double,puzzleCount int,createTime varchar(255))");
                for(int j=0;j<file[i]->tableCount;j++)
                {//插入谜题库中的表信息
                    query.prepare("INSERT INTO "+newLibraryName+" (name,remarkName,type,averageLevel,successRate,puzzleCount,createTime)"
                                                                "VALUES (:1,:2,:3,:4,:5,:6,:7)");
                    query.bindValue(":1",file.at(i)->tables.at(j)->tableName);
                    query.bindValue(":2",file.at(i)->tables.at(j)->remarkName);
                    query.bindValue(":3",file.at(i)->tables.at(j)->type);
                    query.bindValue(":4",file.at(i)->tables.at(j)->averageLevel);
                    query.bindValue(":5",file.at(i)->tables.at(j)->successRate);
                    query.bindValue(":6",file.at(i)->tables.at(j)->puzzleCount);
                    query.bindValue(":7",file.at(i)->tables.at(j)->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                    query.exec();
                    QString newTableName='C'+file.at(i)->fileInfo.fileName().split('.')[0]+'_'+file.at(i)->tables.at(j)->tableName;
                    query.exec("attach database '" +file.at(i)->fileInfo.filePath()+ "' as "+newLibraryName);
                    QString process="create table "+newTableName+" as select * from "+newLibraryName+"."+file.at(i)->tables.at(j)->tableName;
                    query.exec(process);
                }
            }
        }
    }
}
void Library::loadUserFile()//加载user.db
{
    QList<QFileInfo*> delPaths;
    QStringList tables;
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
    data.setDatabaseName("user.db");
    QSqlQuery query(data);
    if(!data.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
        return;
    }
    else
    {
        tables=data.tables();
        query.exec("select * from Alibraries");
        for(int i = 0;query.next(); i++)
        {
            LIBRARYINFO *fileInfo=new LIBRARYINFO;
            fileInfo->remarkName=query.value(1).toString();
            fileInfo->type=query.value(2).toInt();
            fileInfo->averageLevel=query.value(3).toDouble();
            fileInfo->successRate=query.value(4).toDouble();
            fileInfo->tableCount=query.value(5).toInt();
            fileInfo->puzzleCount=query.value(6).toInt();
            fileInfo->createTime=query.value(7).toDateTime();
            fileInfo->fileInfo=QFileInfo(query.value(8).toString());
            int choose=QMessageBox::Yes;
            if(!fileInfo->fileInfo.isFile())
                choose = QMessageBox::question(this, "提示","    数据库文件"+fileInfo->fileInfo.filePath()+"不存在\n    是否在用户数据中保留?",QMessageBox::Yes|QMessageBox::No);
            if(choose==QMessageBox::No)
            {
                delPaths<<&fileInfo->fileInfo;
                continue;
            }
            file<<fileInfo;
            LibrariesWidget->insertRow(LibrariesWidget->rowCount());
            LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,0,new QTableWidgetItem(fileInfo->fileInfo.fileName()));
            LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,1,new QTableWidgetItem(fileInfo->remarkName));
            LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(fileInfo->type)));
            LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,3,new QTableWidgetItem(QString::number(fileInfo->averageLevel)));
            LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(fileInfo->successRate)));
            LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,5,new QTableWidgetItem(QString::number(fileInfo->tableCount)));
            LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,6,new QTableWidgetItem(QString::number(fileInfo->puzzleCount)));
            LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,7,new QTableWidgetItem(fileInfo->createTime.toString("yyyy-MM-dd hh:mm:ss")));
            LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,8,new QTableWidgetItem(fileInfo->fileInfo.filePath()));
            QSqlQuery _query(data);
            QString curLibraryName='B'+fileInfo->fileInfo.fileName().split('.')[0];
            _query.exec("select * from "+curLibraryName);
            for(int j = 0;_query.next()&&j<file[file.size()-1]->tableCount; j++)
            {
                TABLEINFO *tableInfo=new TABLEINFO;
                tableInfo->tableName=_query.value(0).toString();
                tableInfo->remarkName=_query.value(1).toString();
                tableInfo->type=_query.value(2).toInt();
                tableInfo->averageLevel=_query.value(3).toDouble();
                tableInfo->successRate=_query.value(4).toDouble();
                tableInfo->puzzleCount=_query.value(5).toInt();
                tableInfo->createTime=_query.value(6).toDateTime();
                file[file.size()-1]->tables<<tableInfo;
                QSqlQuery __query(data);
                QString curTableName='C'+fileInfo->fileInfo.fileName().split('.')[0]+'_'+tableInfo->tableName;
                __query.exec("select * from "+curTableName);
                for(int k = 0;__query.next()&&k<file[file.size()-1]->tables[file[file.size()-1]->tables.size()-1]->puzzleCount; k++)
                {
                    PUZZLEINFO *puzzleInfo=new PUZZLEINFO;
                    puzzleInfo->id=__query.value(0).toString();
                    puzzleInfo->type=__query.value(1).toInt();
                    puzzleInfo->level=__query.value(2).toInt();
                    puzzleInfo->state=__query.value(3).toInt();
                    puzzleInfo->collection=__query.value(4).toInt();
                    puzzleInfo->puzzle=__query.value(5).toString();
                    file[file.size()-1]->tables[file[file.size()-1]->tables.size()-1]->puzzles<<puzzleInfo;
                }
            }
        }
        for(int i=0;i<delPaths.size();i++)
        {
            QSqlQuery editQuery(data);
            QString delLibraryName='B'+delPaths[i]->fileName().split('.')[0];
            QString cmd=QString("delete from Alibraries where filePath = '%1' ").arg(delPaths[i]->filePath());
            query.exec(cmd);
            editQuery.exec("drop table "+delLibraryName);
            for(int j=0;j<tables.size();j++)
                if(tables[j].contains('C'+delPaths[i]->fileName().split('.')[0],Qt::CaseSensitive))
                    editQuery.exec("drop table "+tables[j]);
        }
    }
    data.close();
    UpdateWidgetView();
    map.clear();
    initMap();
}
void Library::LoadLibraries()//添加新的数据库文件，是控件"加载谜题库"的槽函数
{
    QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("open database file"),"./", tr("DataBase files(*.db)"));
    if(filePaths.size()==0)
        return;
    QString NewDataBase="添加的数据库文件:\n";
    QString ErrorList="因文件名重复而无法导入的数据库文件:\n";
    for(int i=0;i<filePaths.size();i++)
    {
        int flag=1;
        for(int j=0;j<file.size();j++)
        {
            if(file[j]->fileInfo.filePath()==QFileInfo(filePaths[i]).filePath())
                flag=0;
            else if(file[j]->fileInfo.filePath()!=QFileInfo(filePaths[i]).filePath()&&file[j]->fileInfo.fileName()==QFileInfo(filePaths[i]).fileName())
                ErrorList+=file[j]->fileInfo.filePath(),ErrorList+="\n",flag=0;//文件名重复列表
        }
        if(flag)
        {
            QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
            data.setDatabaseName(filePaths[i]);
            QSqlQuery query(data);
            if(!data.open())
            {
                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
                continue;
            }
            else
            {
                LIBRARYINFO *fileInfo=new LIBRARYINFO;
                fileInfo->type=1;
                fileInfo->tableCount=0;
                fileInfo->puzzleCount=0;
                fileInfo->fileInfo=filePaths[i];
                fileInfo->createTime=QFileInfo(filePaths[i]).birthTime();
                int sumofFileLevel=0;
                int sumofFileSuccess=0;
                int size=data.tables().size();
                for(int i=0;i<size;i++)
                {
                    TABLEINFO *tableInfo=new TABLEINFO;
                    tableInfo->tableName=data.tables().at(i);
                    tableInfo->type=1;
                    tableInfo->puzzleCount=0;
                    tableInfo->remarkName="dafault";
                    tableInfo->createTime=QDateTime::currentDateTime();
                    QString sql = QString("select * from "+data.tables().at(i));
                    query.exec(sql);
                    int sumofTableLevel=0;
                    int sumofTableSuccess=0;
                    for(int i = 0;query.next(); i++)
                    {
                        PUZZLEINFO *puzzleInfo=new PUZZLEINFO;
                        puzzleInfo->id=query.value(0).toString();
                        puzzleInfo->type=query.value(1).toInt();
                        puzzleInfo->level=query.value(2).toInt();
                        puzzleInfo->state=query.value(3).toInt();
                        puzzleInfo->collection=query.value(4).toInt();
                        puzzleInfo->puzzle=query.value(5).toString();
                        sumofTableLevel+=puzzleInfo->level;
                        if(puzzleInfo->state==2)
                            sumofTableSuccess++;
                        tableInfo->puzzleCount++;
                        tableInfo->puzzles<<puzzleInfo;
                    }
                    fileInfo->puzzleCount+=tableInfo->puzzleCount;
                    if(tableInfo->puzzleCount)
                    {
                        tableInfo->averageLevel=sumofTableLevel*1.0/tableInfo->puzzleCount;
                        tableInfo->successRate=sumofTableSuccess*1.0/tableInfo->puzzleCount;
                    }
                    else
                    {
                        tableInfo->averageLevel=0;
                        tableInfo->successRate=1;
                    }
                    sumofFileLevel+=sumofTableLevel;
                    sumofFileSuccess+=sumofTableSuccess;
                    fileInfo->tables<<tableInfo;
                    fileInfo->tableCount++;
                }
                if(fileInfo->puzzleCount)
                {
                    fileInfo->averageLevel=sumofFileLevel*1.0/fileInfo->puzzleCount;
                    fileInfo->successRate=sumofFileSuccess*1.0/fileInfo->puzzleCount;
                }
                else
                {
                    fileInfo->averageLevel=0;
                    fileInfo->successRate=1;
                }
                //                bool flag = false;
                //                QString text = QInputDialog::getText(this,"输入提示",QString::asprintf("请为数据库%s输入备注名",filePaths[i].toLatin1().data()),QLineEdit::Normal,"", &flag);
                //                if (flag)
                //                    fileInfo.remarkName=text;
                //                else
                fileInfo->remarkName="text";
                file<<fileInfo;
                NewDataBase+=fileInfo->fileInfo.filePath();
                NewDataBase+="\n";
                LibrariesWidget->insertRow(LibrariesWidget->rowCount());
                LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,0,new QTableWidgetItem(fileInfo->fileInfo.fileName()));
                LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,1,new QTableWidgetItem(fileInfo->remarkName));
                LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(fileInfo->type)));
                LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,3,new QTableWidgetItem(QString::number(fileInfo->averageLevel)));
                LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(fileInfo->successRate)));
                LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,5,new QTableWidgetItem(QString::number(fileInfo->tableCount)));
                LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,6,new QTableWidgetItem(QString::number(fileInfo->puzzleCount)));
                LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,7,new QTableWidgetItem(fileInfo->createTime.toString("yyyy-MM-dd hh:mm:ss")));
                LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,8,new QTableWidgetItem(fileInfo->fileInfo.filePath()));
            }
        }
    }
    UpdateWidgetView();
    map.clear();
    initMap();
    if(NewDataBase!="添加的数据库文件:\n")
        QMessageBox::information(this,"导入完成",NewDataBase);
    if(ErrorList!="因文件名重复而无法导入的数据库文件:\n")
        QMessageBox::information(this,"错误提示",ErrorList);
    updateUserFile();
}
void Library::LoadLibrary(QFileInfo info)//加载所选择的谜题库对应的library界面
{
    LibraryWidget->clear();
    LibraryWidget->setRowCount(0);
    for(int i=0;i<file.size();i++)
    {
        if(file[i]->fileInfo.filePath()==info.filePath())
        {
            for(int j=0;j<file[i]->tables.size();j++)
            {
                LibraryWidget->insertRow(LibraryWidget->rowCount());
                LibraryWidget->setItem(LibraryWidget->rowCount()-1,0,new QTableWidgetItem(file[i]->tables[j]->tableName));
                LibraryWidget->setItem(LibraryWidget->rowCount()-1,1,new QTableWidgetItem(file[i]->tables[j]->remarkName));
                LibraryWidget->setItem(LibraryWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(file[i]->tables[j]->type)));
                LibraryWidget->setItem(LibraryWidget->rowCount()-1,3,new QTableWidgetItem(QString::number(file[i]->tables[j]->averageLevel)));
                LibraryWidget->setItem(LibraryWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(file[i]->tables[j]->successRate)));
                LibraryWidget->setItem(LibraryWidget->rowCount()-1,5,new QTableWidgetItem(QString::number(file[i]->tables[j]->puzzleCount)));
                LibraryWidget->setItem(LibraryWidget->rowCount()-1,6,new QTableWidgetItem(file[i]->tables[j]->createTime.toString("yyyy-MM-dd hh:mm:ss")));
            }
        }
    }
    UpdateWidgetView();
    initMap();
}
void Library::LoadTable(QFileInfo info,QString& tableName)//加载所选择的谜题表对应的puzzles界面
{
    tableWidget->clear();
    tableWidget->setRowCount(0);
    for(int i=0;i<file.size();i++)
    {
        if(file[i]->fileInfo.filePath()==info.filePath())
        {
            for(int j=0;j<file[i]->tables.size();j++)
            {
                if(tableName==file[i]->tables[j]->tableName)
                {
                    for(int k=0;k<file[i]->tables[j]->puzzles.size();k++)
                    {
                        tableWidget->insertRow(tableWidget->rowCount());
                        tableWidget->setItem(tableWidget->rowCount()-1,0,new QTableWidgetItem(file[i]->tables[j]->puzzles[k]->id));
                        tableWidget->setItem(tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(file[i]->tables[j]->puzzles[k]->type)));
                        tableWidget->setItem(tableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(file[i]->tables[j]->puzzles[k]->level)));
                        tableWidget->setItem(tableWidget->rowCount()-1,3,new QTableWidgetItem(QString::number(file[i]->tables[j]->puzzles[k]->state)));
                        tableWidget->setItem(tableWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(file[i]->tables[j]->puzzles[k]->collection)));
                        tableWidget->setItem(tableWidget->rowCount()-1,5,new QTableWidgetItem(file[i]->tables[j]->puzzles[k]->puzzle));
                    }
                    break;
                }
            }
            break;
        }
    }
    UpdateWidgetView();
    initMap();
}
void Library::ContextMenuRequested(QPoint pos)//右键菜单请求槽函数
{
    cursorPos=new QPoint;
    *cursorPos=pos;
    TWMenu->exec(QCursor::pos());
}
void Library::openFolder()//打开谜题库文件所在的文件夹
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = LibrariesWidget->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    QString str=LibrariesWidget->item(row,LibrariesWidget->columnCount()-1)->text().toLatin1().data();
    QProcess proc(this);
    proc.start("explorer /select," + str.replace("/", "\\"));
    proc.waitForFinished();
}
void Library::openLibrary()//打开所选的谜题库
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = LibrariesWidget->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    int fieldIndex=file[row]->type;
    QString libText=file[row]->fileInfo.fileName();
    main->setCurrentIndex(1);
    field->setCurrentIndex(fieldIndex);
    for(int i=0;i<lib->count();i++)
    {
        if(lib->itemText(i)==libText)
            lib->setCurrentIndex(i);
    }
}
void Library::insertLibrary()//新建谜题库
{
    insertDialog->recSignal();
    windowstate=1;
    insertDialog->setWindowModality(Qt::WindowModal);
    insertDialog->exec();
    windowstate=0;
    if(newLibraryInfo!=NULL&&newLibraryInfo->flag==1)
    {
        file<<newLibraryInfo;
        LibrariesWidget->insertRow(LibrariesWidget->rowCount());
        LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,0,new QTableWidgetItem(newLibraryInfo->fileInfo.fileName()));
        LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,1,new QTableWidgetItem(newLibraryInfo->remarkName));
        LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(newLibraryInfo->type)));
        LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,3,new QTableWidgetItem(QString::number(newLibraryInfo->averageLevel)));
        LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(newLibraryInfo->successRate)));
        LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,5,new QTableWidgetItem(QString::number(newLibraryInfo->tableCount)));
        LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,6,new QTableWidgetItem(QString::number(newLibraryInfo->puzzleCount)));
        LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,7,new QTableWidgetItem(newLibraryInfo->createTime.toString("yyyy-MM-dd hh:mm:ss")));
        LibrariesWidget->setItem(LibrariesWidget->rowCount()-1,8,new QTableWidgetItem(newLibraryInfo->fileInfo.filePath()));
        UpdateWidgetView();
        QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
        data.setDatabaseName("user.db");
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            QStringList tables=data.tables();
            QString newLibraryName='B'+newLibraryInfo->fileInfo.fileName().split('.')[0];
            if(!tables.contains(newLibraryName))
            {
                query.prepare("INSERT INTO Alibraries (name,remarkName,type,averageLevel,successRate,tableCount,puzzleCount,createTime,filePath)"
                              "VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9)");
                query.bindValue(":1",newLibraryInfo->fileInfo.fileName());
                query.bindValue(":2",newLibraryInfo->remarkName);
                query.bindValue(":3",newLibraryInfo->type);
                query.bindValue(":4",newLibraryInfo->averageLevel);
                query.bindValue(":5",newLibraryInfo->successRate);
                query.bindValue(":6",newLibraryInfo->tableCount);
                query.bindValue(":7",newLibraryInfo->puzzleCount);
                query.bindValue(":8",newLibraryInfo->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(":9",newLibraryInfo->fileInfo.filePath());
                query.exec();
                //如果数据库中不存在对应表，新建谜题库数据表
                query.exec("create table "+newLibraryName+" (name varchar(255),remarkName varchar(255),type int,averageLevel double,successRate double,puzzleCount int,createTime varchar(255))");
            }
        }
    }
}
void Library::deleteLibrary()//删除所选谜题库
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = LibrariesWidget->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    int choose = QMessageBox::question(this, "提示",QString::asprintf("是否删除路径为%s的谜题表",LibrariesWidget->item(row,8)->text().toLatin1().data()),QMessageBox::Yes|QMessageBox::No);
    if(choose == QMessageBox::Yes)
    {
        QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
        data.setDatabaseName("user.db");
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            for(int i=0;i<file.size();i++)
            {
                if(file[i]->fileInfo.filePath()==LibrariesWidget->item(row,8)->text())
                {
                    file.removeOne(file[i]);
                    break;
                }
            }
            QStringList tables=data.tables();
            query.exec(QString("delete from Alibraries where name='%1'").arg(LibrariesWidget->item(row,0)->text()));
            QString delLibraryName='B'+LibrariesWidget->item(row,0)->text().split('.')[0];
            QString cmd=QString("delete from Alibraries where filePath = '%1' ").arg(LibrariesWidget->item(row,8)->text());
            query.exec(cmd);
            query.exec("drop table "+delLibraryName);
            for(int j=0;j<tables.size();j++)
                if(tables[j].contains('C'+LibrariesWidget->item(row,0)->text().split('.')[0],Qt::CaseSensitive))
                    query.exec("drop table "+tables[j]);
        }
        data.close();
        LibrariesWidget->removeRow(row);
    }
}
void Library::openTable()//打开所选谜题表
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = LibraryWidget->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    int curFieldIndex=field->currentIndex();
    int curLibIndex=lib->currentIndex();
    QString curContentText=LibraryWidget->item(row,0)->text();
    main->setCurrentIndex(2);
    field->setCurrentIndex(curFieldIndex);
    lib->setCurrentIndex(curLibIndex);
    for(int i=0;i<content->count();i++)
    {
        if(curContentText==content->itemText(i))
            content->setCurrentIndex(i);
    }
}
void Library::insertTable()//在当前谜题库下新建谜题表
{
    QFileInfo fileinfo;
    for(int i=0;i<file.size();i++)
    {
        if(file[i]->fileInfo.fileName()==lib->currentText())
            fileinfo=file[i]->fileInfo;
    }
    insertDialog->recSignal();
    windowstate=2;
    insertDialog->setWindowModality(Qt::WindowModal);
    insertDialog->exec();
    windowstate=0;
    if(newTableInfo!=NULL&&newTableInfo->flag==1)
    {
        QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
        data.setDatabaseName(fileinfo.filePath());
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            query.exec("create table "+newTableInfo->tableName+" (id varchar(40),type int,level int,state int,collection int,puzzle varchar(200))");
            for(int i=0;i<file.size();i++)
            {
                if(file[i]->fileInfo.fileName()==lib->currentText())
                {
                    file[i]->tables<<newTableInfo;
                    file[i]->tableCount++;
                    LoadLibrary(fileinfo);
                    UpdateWidgetView();
                    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
                    data.setDatabaseName("user.db");
                    QSqlQuery _query(data);
                    if(!data.open())
                    {
                        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
                        return;
                    }
                    else
                    {
                        QString newLibraryName='B'+file[i]->fileInfo.fileName().split('.')[0];
                        QString newTableName='C'+file[i]->fileInfo.fileName().split('.')[0]+'_'+newTableInfo->tableName;
                        _query.exec("attach database '" +file[i]->fileInfo.filePath()+ "' as "+newLibraryName);
                        QString process="create table "+newTableName+" as select * from "+newLibraryName+"."+newTableInfo->tableName;
                        _query.exec(process);
                        _query.prepare("INSERT INTO "+newLibraryName+" (name,remarkName,type,averageLevel,successRate,puzzleCount,createTime)"
                                                                     "VALUES (:1,:2,:3,:4,:5,:6,:7)");
                        _query.bindValue(":1",newTableInfo->tableName);
                        _query.bindValue(":2",newTableInfo->remarkName);
                        _query.bindValue(":3",newTableInfo->type);
                        _query.bindValue(":4",newTableInfo->averageLevel);
                        _query.bindValue(":5",newTableInfo->successRate);
                        _query.bindValue(":6",newTableInfo->puzzleCount);
                        _query.bindValue(":7",newTableInfo->createTime.toString("yyyy-MM-dd hh:mm:ss"));
                        _query.exec();
                        _query.exec(QString("update Alibraries set tableCount='%1' where name = '%2';").arg(file[i]->tableCount).arg(file[i]->fileInfo.fileName()));
                        LibrariesWidget->item(i,5)->setText(QString::number(file[i]->tableCount));
                    }
                }
            }
        }
        data.close();
    }
}
void Library::deleteTable()//删除所选数据表
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = LibraryWidget->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    int choose = QMessageBox::question(this, "提示",QString::asprintf("是否删除表名为%s的谜题表",LibraryWidget->item(row,0)->text().toLatin1().data()),QMessageBox::Yes|QMessageBox::No);
    if(choose == QMessageBox::Yes)
    {
        QString dataBasePath;
        for(int i=0;i<file.size();i++)
            if(file[i]->fileInfo.fileName()==lib->currentText())
                dataBasePath=file[i]->fileInfo.filePath();
        QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
        data.setDatabaseName(dataBasePath);
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            QString sql = QString("drop table %1").arg(LibraryWidget->item(row,0)->text());
            query.exec(sql);
            for(int i=0;i<file.size();i++)
            {
                if(file[i]->fileInfo.fileName()==lib->currentText())
                {
                    for(int j=0;j<file[i]->tables.size();j++)
                    {
                        if(file[i]->tables[j]->tableName==LibraryWidget->item(row,0)->text())
                        {
                            if(file[i]->puzzleCount==0)
                            {
                                file[i]->averageLevel=0;
                                file[i]->successRate=-1;
                            }
                            else
                            {
                                file[i]->averageLevel=(file[i]->averageLevel*file[i]->puzzleCount-file[i]->tables[j]->averageLevel*file[i]->tables[j]->puzzleCount)/(file[i]->puzzleCount-file[i]->tables[j]->puzzleCount);
                                file[i]->successRate=(file[i]->successRate*file[i]->puzzleCount-file[i]->tables[j]->successRate*file[i]->tables[j]->puzzleCount)/(file[i]->puzzleCount-file[i]->tables[j]->puzzleCount);
                            }
                            file[i]->puzzleCount-=file[i]->tables[j]->puzzleCount;
                            file[i]->tables.removeOne(file[i]->tables[j]);
                            file[i]->tableCount--;
                            UpdateWidgetView();
                            QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
                            data.setDatabaseName("user.db");
                            QSqlQuery _query(data);
                            if(!data.open())
                            {
                                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
                                return;
                            }
                            else
                            {
                                QStringList tables=data.tables();
                                QString delLibraryName='B'+file[i]->fileInfo.fileName().split('.')[0];
                                QString delTableName='C'+file[i]->fileInfo.fileName().split('.')[0]+'_'+LibraryWidget->item(row,0)->text();
                                _query.exec("drop table "+delTableName);
                                QString process=QString("delete from %1 where name='%2'").arg(delLibraryName).arg(LibraryWidget->item(row,0)->text());
                                _query.exec(process);
                                _query.exec(QString("update Alibraries set tableCount=%1,puzzleCount=%2,averageLevel=%3,successRate=%4 where name = '%5';").arg(file[i]->tableCount).arg(file[i]->puzzleCount).arg(file[i]->averageLevel).arg(file[i]->successRate).arg(file[i]->fileInfo.fileName()));
                                LibrariesWidget->item(i,3)->setText(QString::number(file[i]->averageLevel));
                                LibrariesWidget->item(i,4)->setText(QString::number(file[i]->successRate));
                                LibrariesWidget->item(i,5)->setText(QString::number(file[i]->tableCount));
                                LibrariesWidget->item(i,6)->setText(QString::number(file[i]->puzzleCount));
                            }
                        }
                    }
                }
            }
        }
        data.close();
        LibraryWidget->removeRow(row);
    }
}
void Library::loadPuzzle()//载入谜题
{
    MainWindow *p=(MainWindow*)parentWidget();
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    QString qcontext=tableWidget->item(row,5)->text();
    char *context=qcontext.toLatin1().data();
    MAT temp;
    for(int i=0;i<qcontext.length();i++)
    {
        if(!(context[i]=='.'||(context[i]<='9'&&context[i]>='1')))
            return;
        else if(context[i]=='.')
            temp.m[i/9][i%9]=0;
        else
            temp.m[i/9][i%9]=context[i]-'0';
    }
    delete p->sudoku;
    p->sudoku=new SUDOKU(temp);
    p->sudoku->PROB().print();
    p->sudoku->RES().print();
    p->LoadPuzzle();
    p->sudoku->AddHistory();
    p->timerreset();
    if(p->sync->game.auto_timing)
        p->Menus[2].acts[3]->setChecked(true);
}
void Library::copyPuzzle()//复制谜题
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    QClipboard *clip = QApplication::clipboard();
    clip->setText(tableWidget->item(row,5)->text());
}
void Library::insertPuzzle()//在当前谜题表中添加谜题
{
    QFileInfo fileinfo;
    for(int i=0;i<file.size();i++)
    {
        if(file[i]->fileInfo.fileName()==lib->currentText())
            fileinfo=file[i]->fileInfo;
    }
    insertDialog->recSignal();
    windowstate=3;
    insertDialog->setWindowModality(Qt::WindowModal);
    insertDialog->exec();
    windowstate=0;
    if(newPuzzleInfo!=NULL&&newPuzzleInfo->flag==1)
    {
        QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
        data.setDatabaseName(fileinfo.filePath());
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            query.prepare("INSERT INTO "+content->currentText()+"(id,type,level,state,collection,puzzle)"
                                                                "VALUES (:1,:2,:3,:4,:5,:6)");
            query.bindValue(":1",newPuzzleInfo->id);
            query.bindValue(":2",newPuzzleInfo->type);
            query.bindValue(":3",newPuzzleInfo->level);
            query.bindValue(":4",newPuzzleInfo->state);
            query.bindValue(":5",newPuzzleInfo->collection);
            query.bindValue(":6",newPuzzleInfo->puzzle);
            query.exec();
            for(int i=0;i<file.size();i++)
            {
                if(file[i]->fileInfo.fileName()==lib->currentText())
                {
                    for(int j=0;j<file[i]->tables.size();j++)
                    {
                        if(file[i]->tables[j]->tableName==content->currentText())
                        {
                            file[i]->tables[j]->puzzles<<newPuzzleInfo;
                            file[i]->tables[j]->puzzleCount++;
                            file[i]->puzzleCount++;
                            file[i]->tables[j]->averageLevel=(file[i]->tables[j]->averageLevel*(file[i]->tables[j]->puzzleCount-1)+newPuzzleInfo->level)/file[i]->tables[j]->puzzleCount;
                            file[i]->tables[j]->successRate=file[i]->tables[j]->successRate*(file[i]->tables[j]->puzzleCount-1)/file[i]->tables[j]->puzzleCount;
                            file[i]->averageLevel=(file[i]->averageLevel*(file[i]->puzzleCount-1)+newPuzzleInfo->level)/file[i]->puzzleCount;
                            file[i]->successRate=file[i]->successRate*(file[i]->puzzleCount-1)/file[i]->puzzleCount;
                            LoadTable(file[i]->fileInfo,file[i]->tables[j]->tableName);
                            UpdateWidgetView();
                            QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
                            data.setDatabaseName("user.db");
                            QSqlQuery _query(data);
                            if(!data.open())
                            {
                                QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
                                return;
                            }
                            else
                            {
                                QString newLibraryName='B'+file[i]->fileInfo.fileName().split('.')[0];
                                QString newTableName='C'+file[i]->fileInfo.fileName().split('.')[0]+'_'+file[i]->tables[j]->tableName;
                                _query.exec("drop table "+newTableName);
                                _query.exec("attach database '" +file[i]->fileInfo.filePath()+ "' as "+newLibraryName);
                                QString process="create table "+newTableName+" as select * from "+newLibraryName+"."+file[i]->tables[j]->tableName;
                                _query.exec(process);
                                _query.exec(QString("update Alibraries set puzzleCount=%1,averageLevel=%2,successRate=%3 where name = '%4';").arg(file[i]->puzzleCount).arg(file[i]->averageLevel).arg(file[i]->successRate).arg(file[i]->fileInfo.fileName()));
                                _query.exec(QString("update "+newLibraryName+" set puzzleCount=%1,averageLevel=%2,successRate=%3 where name = '%4';").arg(file[i]->tables[j]->puzzleCount).arg(file[i]->tables[j]->averageLevel).arg(file[i]->tables[j]->successRate).arg(file[i]->tables[j]->tableName));
                                LibrariesWidget->item(i,3)->setText(QString::number(file[i]->averageLevel));
                                LibrariesWidget->item(i,4)->setText(QString::number(file[i]->successRate));
                                LibrariesWidget->item(i,6)->setText(QString::number(file[i]->puzzleCount));
                            }
                        }
                    }
                }
            }
        }
        data.close();
    }
}
void Library::deletePuzzle()//删除所选择的谜题
{
    int x=cursorPos->x();
    int y=cursorPos->y();
    QModelIndex index = tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    if(row==-1)
        return;
    int choose = QMessageBox::question(this, "提示",QString::asprintf("是否删除编号为%s的谜题",tableWidget->item(row,0)->text().toLatin1().data()),QMessageBox::Yes|QMessageBox::No);
    if(choose == QMessageBox::Yes)
    {
        QString dataBasePath;
        for(int i=0;i<file.size();i++)
            if(file[i]->fileInfo.fileName()==lib->currentText())
                dataBasePath=file[i]->fileInfo.filePath();
        QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
        data.setDatabaseName(dataBasePath);
        QSqlQuery query(data);
        if(!data.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
            return;
        }
        else
        {
            QString delTableName='C'+QFileInfo(dataBasePath).fileName().split('.')[0]+content->currentText();
            QString sql = QString("delete from %1 where id = '%2' ").arg(delTableName).arg(tableWidget->item(row,0)->text().toLatin1().data());
            query.exec(sql);
            for(int i=0;i<file.size();i++)
            {
                if(file[i]->fileInfo.fileName()==lib->currentText())
                {
                    for(int j=0;j<file[i]->tables.size();j++)
                    {
                        if(file[i]->tables[j]->tableName==content->currentText())
                        {
                            for(int k=0;k<file[i]->tables[j]->puzzles.size();k++)
                            {
                                if(file[i]->tables[j]->puzzles[k]->id==tableWidget->item(row,0)->text().toLatin1().data())
                                {
                                    file[i]->tables[j]->puzzles.removeOne(file[i]->tables[j]->puzzles[k]);
                                    file[i]->tables[j]->puzzleCount--;
                                    file[i]->puzzleCount--;
                                    if(file[i]->tables[j]->puzzleCount==0)
                                    {
                                        file[i]->tables[j]->averageLevel=0;
                                        file[i]->tables[j]->successRate=-1;
                                    }
                                    else
                                    {
                                        file[i]->tables[j]->averageLevel=(file[i]->tables[j]->averageLevel*(file[i]->tables[j]->puzzleCount+1)-file[i]->tables[j]->puzzles[k]->level)/file[i]->tables[j]->puzzleCount;
                                        file[i]->tables[j]->successRate=(file[i]->tables[j]->successRate*(file[i]->tables[j]->puzzleCount+1)-(file[i]->tables[j]->puzzles[k]->state==2))/file[i]->tables[j]->puzzleCount;
                                    }
                                    if(file[i]->puzzleCount==0)
                                    {
                                        file[i]->averageLevel=0;
                                        file[i]->successRate=-1;
                                    }
                                    else
                                    {
                                        file[i]->averageLevel=(file[i]->averageLevel*(file[i]->puzzleCount+1)-file[i]->tables[j]->averageLevel)/file[i]->puzzleCount;
                                        file[i]->successRate=(file[i]->successRate*(file[i]->puzzleCount+1)-(file[i]->tables[j]->puzzles[k]->state==2))/file[i]->puzzleCount;
                                    }
                                    LoadTable(file[i]->fileInfo,file[i]->tables[j]->tableName);
                                    UpdateWidgetView();
                                    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++times));
                                    data.setDatabaseName("user.db");
                                    QSqlQuery _query(data);
                                    if(!data.open())
                                    {
                                        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
                                        return;
                                    }
                                    else
                                    {
                                        QString newLibraryName='B'+file[i]->fileInfo.fileName().split('.')[0];
                                        QString newTableName='C'+file[i]->fileInfo.fileName().split('.')[0]+'_'+file[i]->tables[j]->tableName;
                                        _query.exec("drop table "+newTableName);
                                        _query.exec("attach database '" +file[i]->fileInfo.filePath()+ "' as "+newLibraryName);
                                        QString process="create table "+newTableName+" as select * from "+newLibraryName+"."+file[i]->tables[j]->tableName;
                                        _query.exec(process);
                                        _query.exec(QString("update Alibraries set puzzleCount=%1,averageLevel=%2,successRate=%3 where name = '%4';").arg(file[i]->puzzleCount).arg(file[i]->averageLevel).arg(file[i]->successRate).arg(file[i]->fileInfo.fileName()));
                                        _query.exec(QString("update "+newLibraryName+" set puzzleCount=%1,averageLevel=%2,successRate=%3 where name = '%4';").arg(file[i]->tables[j]->puzzleCount).arg(file[i]->tables[j]->averageLevel).arg(file[i]->tables[j]->successRate).arg(file[i]->tables[j]->tableName));
                                        LibrariesWidget->item(i,3)->setText(QString::number(file[i]->averageLevel));
                                        LibrariesWidget->item(i,4)->setText(QString::number(file[i]->successRate));
                                        LibrariesWidget->item(i,6)->setText(QString::number(file[i]->puzzleCount));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        data.close();
        tableWidget->removeRow(row);
    }
}
