#include "include/mainwindow.h"
#include "ui_mainwindow.h"
int music_times=999;
musicdialog::musicdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::musicdialog)
{
    ui->setupUi(this);
    this->setWindowTitle("音乐");
    QFile file(":/qss/dark.qss");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet+= QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
    InitView();
    musicCount=0;
    loadedCount=0;
    connect(this,SIGNAL(MetaDataLoaded(QString)),this,SLOT(fillData()));
    curPlayer=new QMediaPlayer;
    connect(curPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(onPositionChanged(qint64)));
    connect(curPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(onDurationChanged(qint64)));
}

musicdialog::~musicdialog()
{
    delete ui;
}
void musicdialog::InitTableWidget(QTableWidget *tableWidget)
{
    tableWidget->setAlternatingRowColors(true);
    tableWidget->verticalHeader()->setDefaultSectionSize(45);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setContextMenuPolicy(Qt::NoContextMenu);
    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //    connect(tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ContextMenuRequested(QPoint)));
    //    connect(tableWidget->horizontalHeader(),SIGNAL(sectionClicked(int)),this, SLOT(onHeaderClicked(int)));
    QStringList TableHeader;
    TableHeader<<"标题"<<"歌手"<<"专辑"<<"时长"<<"歌词文件"<<"文件路径";
    tableWidget->setColumnCount(TableHeader.size());
    tableWidget->setHorizontalHeaderLabels(TableHeader);
    for(int i=0;i<tableWidget->columnCount();i++)
        tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}
void musicdialog::InitView()
{
    //    MainWindow *p= (MainWindow *)parentWidget();
    mainWidget=new QStackedWidget(this);
    windowLayout=new QVBoxLayout();
    headerLayout=new QHBoxLayout();
    //Side Bar
    sideLayout=new QVBoxLayout;
    localMusic=new QPushButton();
    localMusic->setText("本地音乐");
    playList=new QPushButton();
    playList->setText("播放列表");
    curList=new QPushButton();
    curList->setText("当前播放");
    connect(localMusic,SIGNAL(clicked()),this,SLOT(stackedWidgetView()));
    connect(playList,SIGNAL(clicked()),this,SLOT(stackedWidgetView()));
    connect(curList,SIGNAL(clicked()),this,SLOT(stackedWidgetView()));
    sideLayout->addWidget(localMusic);
    sideLayout->addSpacing(50);
    sideLayout->addWidget(playList);
    sideLayout->addSpacing(50);
    sideLayout->addWidget(curList);
    sideLayout->addSpacing(300);
    headerLayout->addLayout(sideLayout);
    //My Music
    myMusicWidget=new QWidget;
    myMusicTableWidget=new QTableWidget;
    InitTableWidget(myMusicTableWidget);
    addMusicLayout=new QHBoxLayout();
    scanFolder=new QPushButton();
    scanFolder->setText("扫描文件夹");
    connect(scanFolder,SIGNAL(clicked()),this,SLOT(scanFolderSlot()));
    playAll=new QPushButton();
    playAll->setText("播放全部");
    connect(playAll,SIGNAL(clicked()),this,SLOT(playAllSlot()));
    myMusicLayout=new QVBoxLayout;
    addMusicLayout->addWidget(scanFolder);
    addMusicLayout->addWidget(playAll);
    addMusicLayout->addStretch();
    myMusicLayout->addLayout(addMusicLayout);
    myMusicLayout->addWidget(myMusicTableWidget);
    myMusicWidget->setLayout(myMusicLayout);
    mainWidget->addWidget(myMusicWidget);
    //Play List
    myListWidget=new QWidget;
    myListLayout=new QVBoxLayout;
    listTableWidget=new QTableWidget;
    InitTableWidget(listTableWidget);
    listEditLayout=new QHBoxLayout;
    listLabel=new QLabel("播放列表");
    lists=new QComboBox();
    lists->setCurrentIndex(-1);
    connect(lists,SIGNAL(currentIndexChanged(int)),this,SLOT(listView(int)));
    insertList=new QPushButton;
    insertList->setText("新建播放列表");
    connect(insertList,SIGNAL(clicked()),this,SLOT(insertListSlot()));
    loadList=new QPushButton;
    loadList->setText("载入播放列表");
    connect(loadList,SIGNAL(clicked()),this,SLOT(loadListSlot()));
    playCurrentList=new QPushButton;
    playCurrentList->setText("播放当前列表");
    connect(playCurrentList,SIGNAL(clicked()),this,SLOT(playCurrentListSlot()));
    removeList=new QPushButton;
    removeList->setText("删除当前列表");
    connect(removeList,SIGNAL(clicked()),this,SLOT(removeListSlot()));
    listEditLayout->addWidget(listLabel);
    listEditLayout->addWidget(lists);
    listEditLayout->addWidget(insertList);
    listEditLayout->addWidget(loadList);
    listEditLayout->addWidget(playCurrentList);
    listEditLayout->addWidget(removeList);
    listEditLayout->addStretch();
    myListLayout->addLayout(listEditLayout);
    myListLayout->addWidget(listTableWidget);
    myListWidget->setLayout(myListLayout);
    mainWidget->addWidget(myListWidget);
    //Current List
    curListWidget=new QWidget;
    curListLayout=new QVBoxLayout;
    curListTableWidget=new QTableWidget;
    InitTableWidget(curListTableWidget);
    curListEditLayout=new QHBoxLayout;
    clearCurList=new QPushButton;
    clearCurList->setText("清除列表");
    connect(clearCurList,SIGNAL(clicked()),this,SLOT(clearCurListSlot()));
    saveCurList=new QPushButton;
    saveCurList->setText("保存列表");
    connect(saveCurList,SIGNAL(clicked()),this,SLOT(saveCurListSlot()));
    curListEditLayout->addWidget(clearCurList);
    curListEditLayout->addWidget(saveCurList);
    curListEditLayout->addStretch();
    curListLayout->addLayout(curListEditLayout);
    curListLayout->addWidget(curListTableWidget);
    curListWidget->setLayout(curListLayout);
    mainWidget->addWidget(curListWidget);
    headerLayout->addWidget(mainWidget);
    //Footer
    functionLayout=new QHBoxLayout;
    playLayout=new QHBoxLayout;
    footerLayout=new QVBoxLayout;
    nameLabel=new QLabel("");
    timeLabel=new QLabel("0:00/0:00");
    mode=new QPushButton;
    mode->setText("播放模式");
    connect(mode,SIGNAL(clicked()),this,SLOT(playMode()));
    pre=new QPushButton;
    pre->setToolTip("上一首");
    connect(pre,SIGNAL(clicked()),this,SLOT(playPre()));
    pre->setIcon(QIcon(":/icons/icons/music-pre.png"));
    next=new QPushButton;
    next->setToolTip("下一首");
    connect(next,SIGNAL(clicked()),this,SLOT(playNext()));
    next->setIcon(QIcon(":/icons/icons/music-next.png"));
    play=new QPushButton;
    play->setToolTip("播放");
    connect(play,SIGNAL(clicked()),this,SLOT(playButton()));
    play->setIcon(QIcon(":/icons/icons/music-play.png"));
    timeSlider=new QSlider;
    timeSlider->setOrientation(Qt::Horizontal);
    volume=new QPushButton;
    volume->setToolTip("音量");
    volume->setIcon(QIcon(":/icons/icons/sound-filling.png"));
    volumeSlider=new QSlider;
    volumeSlider->setOrientation(Qt::Horizontal);
    playLayout->addWidget(nameLabel);
    playLayout->addWidget(timeSlider);
    playLayout->addWidget(timeLabel);
    functionLayout->addWidget(mode);
    functionLayout->addWidget(pre);
    functionLayout->addWidget(play);
    functionLayout->addWidget(next);
    functionLayout->addWidget(volume);
    functionLayout->addWidget(volumeSlider);
    footerLayout->addLayout(playLayout);
    footerLayout->addLayout(functionLayout);
    windowLayout->addLayout(headerLayout);
    windowLayout->addLayout(footerLayout);
    setLayout(windowLayout);
    activeWidget=myMusicTableWidget;
}
void musicdialog::UpdateWidgetView()//更新列表视图，使内容居中，且根据内容选择显示的文字
{
    if(activeWidget==NULL)
        return;
    for(int i=0;i<activeWidget->rowCount();i++)
        for(int j=0;j<activeWidget->columnCount();j++)
            if(activeWidget->item(i,j)!=NULL)
                activeWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}

void musicdialog::stackedWidgetView()
{
    QPushButton *send=(QPushButton* )sender();
    if(send==localMusic)
        mainWidget->setCurrentIndex(0),activeWidget=myMusicTableWidget;
    if(send==playList)
        mainWidget->setCurrentIndex(1),activeWidget=listTableWidget;
    if(send==curList)
        mainWidget->setCurrentIndex(2),activeWidget=curListTableWidget;
    UpdateWidgetView();
}
void musicdialog::scanFolderSlot()
{
    QString folderPath=QFileDialog::getExistingDirectory(this,"打开文件夹","./");
    findFile(folderPath);
    folderList<<folderPath;
    for(int i=0;i<music.size();i++)
    {
        connect(music[i]->player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(LoadMetaData(QMediaPlayer::MediaStatus)));
        music[i]->player->setMedia(QUrl::fromLocalFile(music[i]->filePath));
        music[i]->player->play();
        music[i]->player->stop();
    }
}
void musicdialog::findFile(const QString & folderPath)
{
    QDir dir(folderPath);
    if (!dir.exists())
        return;
    dir.setFilter(QDir::Dirs|QDir::Files);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list=dir.entryInfoList();
    int i = 0;
    bool IsDir;
    do{
        QFileInfo *fileInfo =new QFileInfo;
        *fileInfo=list.at(i);
        if(fileInfo->fileName()=="."||fileInfo->fileName()=="..")
        {
            i++;
            continue;
        }
        IsDir = fileInfo->isDir();
        if (IsDir) {
            findFile(fileInfo->filePath());
        }
        else
        {
            if(fileInfo->filePath().endsWith(".txt")||fileInfo->filePath().endsWith(".lrc"))
                lrcList<<fileInfo->filePath();
            if(fileInfo->filePath().endsWith(".m3u")&&!playListList.contains(fileInfo->filePath()))
            {
                playListList<<fileInfo->filePath();
                QFile file(fileInfo->filePath());
                LISTINFO *tempList=new LISTINFO;
                tempList->songCount=0;
                tempList->filePath=fileInfo->filePath();
                if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    while (!file.atEnd())
                    {
                        QByteArray line = file.readLine();
                        QString path=QString(line.data()).split('\n')[0];
                        if(musicPathList.contains(line.data())||!QFileInfo(path).isFile())
                            continue;
                        else
                        {
                            if(QFileInfo(path).filePath().endsWith(".flac")||QFileInfo(path).filePath().endsWith(".wma",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".wav",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".mp3",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".ape",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".aif",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".aiff",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".mid",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".aac",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".ac3",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".m4a",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".midi",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".cda",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".voc",Qt::CaseInsensitive))
                            {
                                tempList->songCount++;
                                if(!musicPathList.contains(path))
                                {
                                    musicCount++;
                                    MUSICINFO *temp=new MUSICINFO;
                                    temp->player=new QMediaPlayer;
                                    temp->player->setVolume(0);
                                    temp->filePath=QFileInfo(path).filePath();
                                    music<<temp;
                                    tempList->music<<temp;
                                    musicPathList<<QFileInfo(path).filePath();
                                }
                                else
                                {
                                    int index=musicPathList.indexOf(path);
                                    tempList->music<<music[index];
                                }
                            }
                        }
                    }
                    disconnect(lists,SIGNAL(currentIndexChanged(int)),this,SLOT(listView(int)));
                    if(tempList->songCount!=0)
                    {
                        musicList<<tempList;
                        lists->addItem(QFileInfo(tempList->filePath).completeBaseName());
                    }
                    lists->setCurrentIndex(-1);
                    connect(lists,SIGNAL(currentIndexChanged(int)),this,SLOT(listView(int)));
                    file.close();
                }
            }
            if(fileInfo->filePath().endsWith(".flac")||fileInfo->filePath().endsWith(".wma",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".wav",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".mp3",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".ape",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".aif",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".aiff",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".mid",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".aac",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".ac3",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".m4a",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".midi",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".cda",Qt::CaseInsensitive)||fileInfo->filePath().endsWith(".voc",Qt::CaseInsensitive))
            {

                if(!musicPathList.contains(fileInfo->filePath()))
                {
                    musicCount++;
                    MUSICINFO *temp=new MUSICINFO;
                    temp->player=new QMediaPlayer;
                    temp->player->setVolume(0);
                    temp->filePath=fileInfo->filePath();
                    musicPathList<<fileInfo->filePath();
                    music<<temp;
                }
            }
        }
        i++;
    }
    while(i<list.size());
}
void musicdialog::playCurrentListSlot()
{
    curMusicList.clear();
    int currentIndex=lists->currentIndex();
    if(currentIndex==-1)
        return;
    int count=curListTableWidget->rowCount();
    for(int i=count-1;i>=0;i--)
        curListTableWidget->removeRow(i);
    QMediaPlaylist *curPlayerList=new QMediaPlaylist;
    QStringList TableHeader;
    TableHeader<<"标题"<<"歌手"<<"专辑"<<"时长"<<"歌词文件"<<"文件路径";
    curListTableWidget->setColumnCount(TableHeader.size());
    curListTableWidget->setHorizontalHeaderLabels(TableHeader);
    for(int i=0;i<curListTableWidget->columnCount();i++)
        curListTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    for(int i=0;i<musicList[currentIndex]->songCount;i++)
    {
        curMusicList<<musicList[currentIndex]->music[i];
        curPlayerList->addMedia(QUrl(musicList[currentIndex]->music[i]->filePath));
        int mins=musicList[currentIndex]->music[i]->duration/60000;
        int secs=(musicList[currentIndex]->music[i]->duration/1000)%60;
        curListTableWidget->insertRow(curListTableWidget->rowCount());
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,0,new QTableWidgetItem(QFileInfo(musicList[currentIndex]->music[i]->filePath).completeBaseName()));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,1,new QTableWidgetItem(musicList[currentIndex]->music[i]->albumArtist));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,2,new QTableWidgetItem(musicList[currentIndex]->music[i]->albumTitle));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,3,new QTableWidgetItem(QString::asprintf("%02d:%02d",mins,secs)));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,4,new QTableWidgetItem(musicList[currentIndex]->music[i]->lyricsPath));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,5,new QTableWidgetItem(musicList[currentIndex]->music[i]->filePath));
    }
    curPlayerList->setCurrentIndex(0);
    curPlayer->setPlaylist(curPlayerList);
    curPlayer->play();
    curIndex=0;
    nameLabel->setText(QFileInfo(curMusicList[curIndex]->filePath).completeBaseName());
    timeLabel->setText(QString::asprintf("0:00/%02d:%02d",(int)curMusicList[curIndex]->duration/60000,(int)(curMusicList[curIndex]->duration/1000)%60));
    play->setToolTip("暂停");
    play->setIcon(QIcon(":/icons/icons/music-suspended.png"));
}
void musicdialog::insertListSlot()
{
    QString filePath=QFileDialog::getSaveFileName(this, "新建播放列表","./",tr("MusicList files(*.m3u)"));
    if(filePath=="")
        return;
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    file.close();
    playListList<<filePath;
    LISTINFO *tempList=new LISTINFO;
    tempList->songCount=0;
    tempList->filePath=filePath;
    disconnect(lists,SIGNAL(currentIndexChanged(int)),this,SLOT(listView(int)));
    musicList<<tempList;
    lists->addItem(QFileInfo(tempList->filePath).completeBaseName());
    lists->setCurrentIndex(-1);
    connect(lists,SIGNAL(currentIndexChanged(int)),this,SLOT(listView(int)));
}
void musicdialog::removeListSlot()
{
    int currentIndex=lists->currentIndex();
    int choose = QMessageBox::question(this, "提示","是否删除播放列表“"+lists->currentText()+"”",QMessageBox::Yes|QMessageBox::No);
    if(choose == QMessageBox::Yes)
    {
        for(int i=0;i<playListList.size();i++)
            if(QFileInfo(playListList[i]).completeBaseName()==lists->currentIndex())
                playListList.removeAt(i);
        lists->removeItem(currentIndex);
    }
}
void musicdialog::loadListSlot()
{
    QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("open musiclist file"),"./", tr("MusicList files(*.m3u)"));
    for(int i=0;i<filePaths.size();i++)
    {
        playListList<<filePaths[i];
        QFile file(filePaths[i]);
        LISTINFO *tempList=new LISTINFO;
        tempList->songCount=0;
        tempList->filePath=filePaths[i];
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while (!file.atEnd())
            {
                QByteArray line = file.readLine();
                QString path=QString(line.data()).split('\n')[0];
                if(musicPathList.contains(line.data())||!QFileInfo(path).isFile())
                    continue;
                else
                {
                    if(QFileInfo(path).filePath().endsWith(".flac")||QFileInfo(path).filePath().endsWith(".wma",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".wav",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".mp3",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".ape",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".aif",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".aiff",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".mid",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".aac",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".ac3",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".m4a",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".midi",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".cda",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".voc",Qt::CaseInsensitive))
                    {
                        tempList->songCount++;
                        if(!musicPathList.contains(path))
                        {
                            musicCount++;
                            MUSICINFO *temp=new MUSICINFO;
                            temp->player=new QMediaPlayer;
                            temp->player->setVolume(0);
                            temp->filePath=QFileInfo(path).filePath();
                            music<<temp;
                            tempList->music<<temp;
                            musicPathList<<QFileInfo(path).filePath();
                        }
                        else
                        {
                            int index=musicPathList.indexOf(path);
                            tempList->music<<music[index];
                        }
                    }
                }
            }
            disconnect(lists,SIGNAL(currentIndexChanged(int)),this,SLOT(listView(int)));
            if(tempList->songCount!=0)
            {
                musicList<<tempList;
                lists->addItem(QFileInfo(tempList->filePath).completeBaseName());
            }
            lists->setCurrentIndex(-1);
            connect(lists,SIGNAL(currentIndexChanged(int)),this,SLOT(listView(int)));
            file.close();
        }
    }
    for(int i=0;i<music.size();i++)
    {
        connect(music[i]->player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(LoadMetaData(QMediaPlayer::MediaStatus)));
        music[i]->player->setMedia(QUrl::fromLocalFile(music[i]->filePath));
        music[i]->player->play();
        music[i]->player->stop();
    }
}
void musicdialog::listView(int)
{
    int currentIndex=lists->currentIndex();
    int count=listTableWidget->rowCount();
    for(int i=count-1;i>=0;i--)
        listTableWidget->removeRow(i);
    QStringList TableHeader;
    TableHeader<<"标题"<<"歌手"<<"专辑"<<"时长"<<"歌词文件"<<"文件路径";
    listTableWidget->setColumnCount(TableHeader.size());
    listTableWidget->setHorizontalHeaderLabels(TableHeader);
    for(int i=0;i<listTableWidget->columnCount();i++)
        listTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    for(int i=0;i<musicList[currentIndex]->songCount;i++)
    {
        int mins=musicList[currentIndex]->music[i]->duration/60000;
        int secs=(musicList[currentIndex]->music[i]->duration/1000)%60;
        listTableWidget->insertRow(listTableWidget->rowCount());
        listTableWidget->setItem(listTableWidget->rowCount()-1,0,new QTableWidgetItem(QFileInfo(musicList[currentIndex]->music[i]->filePath).completeBaseName()));
        listTableWidget->setItem(listTableWidget->rowCount()-1,1,new QTableWidgetItem(musicList[currentIndex]->music[i]->albumArtist));
        listTableWidget->setItem(listTableWidget->rowCount()-1,2,new QTableWidgetItem(musicList[currentIndex]->music[i]->albumTitle));
        listTableWidget->setItem(listTableWidget->rowCount()-1,3,new QTableWidgetItem(QString::asprintf("%02d:%02d",mins,secs)));
        listTableWidget->setItem(listTableWidget->rowCount()-1,4,new QTableWidgetItem(musicList[currentIndex]->music[i]->lyricsPath));
        listTableWidget->setItem(listTableWidget->rowCount()-1,5,new QTableWidgetItem(musicList[currentIndex]->music[i]->filePath));
    }
    UpdateWidgetView();
}
void musicdialog::LoadMetaData(QMediaPlayer::MediaStatus status)
{
    QMediaPlayer *tempPlayer=(QMediaPlayer *)sender();
    if (status == QMediaPlayer::LoadedMedia)
    {
        for(int i=0;i<music.size();i++)
        {
            if(music[i]->player==tempPlayer)
            {
                music[i]->albumArtist=tempPlayer->metaData(QMediaMetaData::AlbumArtist).toString();
                music[i]->albumTitle=tempPlayer->metaData(QMediaMetaData::AlbumTitle).toString();
                music[i]->duration=tempPlayer->metaData(QMediaMetaData::Duration).toInt();
                loadedCount++;
                if(loadedCount==musicCount)
                    emit MetaDataLoaded("yes");
            }
        }
    }
}
void musicdialog::fillData()
{
    int count=myMusicTableWidget->rowCount();
    for(int i=count-1;i>=0;i--)
        myMusicTableWidget->removeRow(i);
    for(int i=0;i<music.size();i++)
    {
        for(int j=0;j<lrcList.size();j++)
        {
            if(QFileInfo(lrcList[j]).completeBaseName()==QFileInfo(music[i]->filePath).completeBaseName())
                music[i]->lyricsPath=lrcList[j];
        }
        int mins=music[i]->duration/60000;
        int secs=(music[i]->duration/1000)%60;
        myMusicTableWidget->insertRow(myMusicTableWidget->rowCount());
        myMusicTableWidget->setItem(myMusicTableWidget->rowCount()-1,0,new QTableWidgetItem(QFileInfo(music[i]->filePath).completeBaseName()));
        myMusicTableWidget->setItem(myMusicTableWidget->rowCount()-1,1,new QTableWidgetItem(music[i]->albumArtist));
        myMusicTableWidget->setItem(myMusicTableWidget->rowCount()-1,2,new QTableWidgetItem(music[i]->albumTitle));
        myMusicTableWidget->setItem(myMusicTableWidget->rowCount()-1,3,new QTableWidgetItem(QString::asprintf("%02d:%02d",mins,secs)));
        myMusicTableWidget->setItem(myMusicTableWidget->rowCount()-1,4,new QTableWidgetItem(music[i]->lyricsPath));
        myMusicTableWidget->setItem(myMusicTableWidget->rowCount()-1,5,new QTableWidgetItem(music[i]->filePath));
    }
    lists->setCurrentIndex(0);
    UpdateWidgetView();
}
void musicdialog::playNext()
{
    int index=(curPlayer->playlist()->currentIndex()+1)%curPlayer->playlist()->mediaCount();
    curPlayer->playlist()->setCurrentIndex(index);
    curIndex=(curIndex+1)%curMusicList.size();
    nameLabel->setText(QFileInfo(curMusicList[curIndex]->filePath).completeBaseName());
    timeLabel->setText(QString::asprintf("0:00/%02d:%02d",(int)curMusicList[curIndex]->duration/60000,(int)(curMusicList[curIndex]->duration/1000)%60));
}
void musicdialog::playPre()
{
    int index=(curPlayer->playlist()->currentIndex()-1+curPlayer->playlist()->mediaCount())%curPlayer->playlist()->mediaCount();
    curPlayer->playlist()->setCurrentIndex(index);
    curIndex=(curIndex-1+curMusicList.size())%curMusicList.size();
    nameLabel->setText(QFileInfo(curMusicList[curIndex]->filePath).completeBaseName());
    timeLabel->setText(QString::asprintf("0:00/%02d:%02d",(int)curMusicList[curIndex]->duration/60000,(int)(curMusicList[curIndex]->duration/1000)%60));
}
void musicdialog::playMode()
{

}
void musicdialog::playButton()
{
    if(curPlayer->state()==QMediaPlayer::PausedState||curPlayer->state()==QMediaPlayer::StoppedState)
    {
        curPlayer->play();
        play->setToolTip("暂停");
        play->setIcon(QIcon(":/icons/icons/music-suspended.png"));
    }
    else if(curPlayer->state()==QMediaPlayer::PlayingState)
    {
        curPlayer->pause();
        play->setToolTip("播放");
        play->setIcon(QIcon(":/icons/icons/music-play.png"));
    }
}
void musicdialog::playAllSlot()
{
    curMusicList.clear();
    int count=curListTableWidget->rowCount();
    for(int i=count-1;i>=0;i--)
        curListTableWidget->removeRow(i);
    QMediaPlaylist *curPlayerList=new QMediaPlaylist;
    QStringList TableHeader;
    TableHeader<<"标题"<<"歌手"<<"专辑"<<"时长"<<"歌词文件"<<"文件路径";
    curListTableWidget->setColumnCount(TableHeader.size());
    curListTableWidget->setHorizontalHeaderLabels(TableHeader);
    for(int i=0;i<curListTableWidget->columnCount();i++)
        curListTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    for(int i=0;i<music.size();i++)
    {
        curMusicList<<music[i];
        curPlayerList->addMedia(QUrl(music[i]->filePath));
        int mins=music[i]->duration/60000;
        int secs=(music[i]->duration/1000)%60;
        curListTableWidget->insertRow(curListTableWidget->rowCount());
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,0,new QTableWidgetItem(QFileInfo(music[i]->filePath).completeBaseName()));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,1,new QTableWidgetItem(music[i]->albumArtist));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,2,new QTableWidgetItem(music[i]->albumTitle));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,3,new QTableWidgetItem(QString::asprintf("%02d:%02d",mins,secs)));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,4,new QTableWidgetItem(music[i]->lyricsPath));
        curListTableWidget->setItem(curListTableWidget->rowCount()-1,5,new QTableWidgetItem(music[i]->filePath));
    }
    curPlayerList->setCurrentIndex(0);
    curPlayer->setPlaylist(curPlayerList);
    curPlayer->play();
    curIndex=0;
    nameLabel->setText(QFileInfo(curMusicList[curIndex]->filePath).completeBaseName());
    timeLabel->setText(QString::asprintf("0:00/%02d:%02d",(int)curMusicList[curIndex]->duration/60000,(int)(curMusicList[curIndex]->duration/1000)%60));
    play->setToolTip("暂停");
    play->setIcon(QIcon(":/icons/icons/music-suspended.png"));
}
void musicdialog::clearCurListSlot()
{
    int choose = QMessageBox::question(this, "提示","是否删除当前播放列表",QMessageBox::Yes|QMessageBox::No);
    if(choose == QMessageBox::Yes)
    {
        int count=curListTableWidget->rowCount();
        for(int i=count-1;i>=0;i--)
            curListTableWidget->removeRow(i);
        QMediaPlaylist *curPlayerList=new QMediaPlaylist;
        curPlayer->setPlaylist(curPlayerList);
        play->setToolTip("播放");
        play->setIcon(QIcon(":/icons/icons/music-play.png"));
    }
}
void musicdialog::saveCurListSlot()
{
    QString filePath=QFileDialog::getSaveFileName(this, "另存为播放列表","./",tr("MusicList files(*.m3u)"));
    if(filePath=="")
        return;
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly))
    {
        for(int i=0;i<curListTableWidget->rowCount();i++)
        {
            file.write(curListTableWidget->item(i,5)->text().replace("/","\\").toUtf8());
            if(i<curListTableWidget->rowCount()-1)
                file.write("\n");
        }
    }
    file.close();
    playListList<<filePath;
    LISTINFO *tempList=new LISTINFO;
    tempList->songCount=0;
    tempList->filePath=filePath;
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString path=QString(line.data()).split('\n')[0];
            if(musicPathList.contains(line.data())||!QFileInfo(path).isFile())
                continue;
            else
            {
                if(QFileInfo(path).filePath().endsWith(".flac")||QFileInfo(path).filePath().endsWith(".wma",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".wav",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".mp3",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".ape",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".aif",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".aiff",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".mid",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".aac",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".ac3",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".m4a",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".midi",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".cda",Qt::CaseInsensitive)||QFileInfo(path).filePath().endsWith(".voc",Qt::CaseInsensitive))
                {
                    tempList->songCount++;
                    if(!musicPathList.contains(QFileInfo(path).filePath()))
                    {
                        musicCount++;
                        MUSICINFO *temp=new MUSICINFO;
                        temp->player=new QMediaPlayer;
                        temp->player->setVolume(0);
                        temp->filePath=QFileInfo(path).filePath();
                        music<<temp;
                        tempList->music<<temp;
                        musicPathList<<QFileInfo(path).filePath();
                    }
                    else
                    {
                        int index=musicPathList.indexOf(QFileInfo(path).filePath());
                        tempList->music<<music[index];
                    }
                }
            }
        }
        disconnect(lists,SIGNAL(currentIndexChanged(int)),this,SLOT(listView(int)));
        if(tempList->songCount!=0)
        {
            musicList<<tempList;
            lists->addItem(QFileInfo(tempList->filePath).completeBaseName());
        }
        lists->setCurrentIndex(-1);
        connect(lists,SIGNAL(currentIndexChanged(int)),this,SLOT(listView(int)));
        file.close();
    }
    lists->setCurrentIndex(0);
}
void musicdialog::updateUserFile()//将用户加载的数据库文件信息和数据表文件信息存储到user.db中
{
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++music_times));
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
        query.exec("drop table Amusic");
        if(!tables.contains("Amusic"))
        {
            query.exec("create table Amusic (type int,filePath varchar(255))");
            for(int i=0;i<folderList.size();i++)
            {
                query.prepare("insert into Amusic (type,filePath)"
                              "VALUES (:1,:2)");
                query.bindValue(":1",0);
                query.bindValue(":2",folderList[i]);
                query.exec();
            }
            for(int i=0;i<playListList.size();i++)
            {
                query.prepare("insert into Amusic (type,filePath)"
                              "VALUES (:1,:2)");
                query.bindValue(":1",1);
                query.bindValue(":2",playListList[i]);
                query.exec();
            }
        }
        data.close();
    }
}
void musicdialog::loadUserFile()//加载user.db
{
    QStringList tables;
    QSqlDatabase data = QSqlDatabase::addDatabase("QSQLITE",QString::asprintf("%d",++music_times));
    data.setDatabaseName("user.db");
    QSqlQuery query(data);
    if(!data.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Connection Error!"), data.lastError().text());
        return;
    }
    else
    {
        QString cmd=QString("select filePath from Amusic where type = '%1' ").arg(0);
        query.exec(cmd);
        for(int i = 0;query.next(); i++)
        {
            QString folderPath=query.value(0).toString();
            qDebug()<<folderPath;
            findFile(folderPath);
            folderList<<folderPath;
            for(int i=0;i<music.size();i++)
            {
                connect(music[i]->player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(LoadMetaData(QMediaPlayer::MediaStatus)));
                music[i]->player->setMedia(QUrl::fromLocalFile(music[i]->filePath));
                music[i]->player->play();
                music[i]->player->stop();
            }
        }
    }
}
void musicdialog::onPositionChanged(qint64)
{
//    if(t->isSliderDown())
//        return;
//    ui->horizontalSlider->setSliderPosition(position);
//    int secs = position/1000;
//    int mins = secs/60;
//    secs = secs % 60;
//    positionTime = QString::asprintf("%d:%d",mins,secs);
//    ui->label->setText(positionTime+"/"+durationTime);
}
void musicdialog::onDurationChanged(qint64)
{
//    if(t->isSliderDown())
//        return;
//    ui->horizontalSlider->setSliderPosition(position);
//    int secs = position/1000;
//    int mins = secs/60;
//    secs = secs % 60;
//    positionTime = QString::asprintf("%d:%d",mins,secs);
//    ui->label->setText(positionTime+"/"+durationTime);
}
