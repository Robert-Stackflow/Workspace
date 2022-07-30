#include "controller/customTitleBar.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
CustomTitleBar::CustomTitleBar(QWidget *parent) : QWidget(parent)
{
    if(parent!=NULL)
        setFixedWidth(parent->width());
    setFixedHeight(60);
    setWindowFlags(Qt::FramelessWindowHint);
    iconLabel = new QLabel(this);
    iconLabel->setFixedSize(25, 25);
    iconLabel->setScaledContents(true);

    titleLabel = new QLabel(this);
    QFont font;
    font.setBold(true);
    font.setFamily("黑体");
    font.setPointSize(13);
    titleLabel->setStyleSheet("color:#06ad56");
    titleLabel->setFont(font);
    titleLabel->setFixedHeight(30);
    titleLabel->setScaledContents(true);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    minimizeButton = new QPushButton(this);
    minimizeButton->setFixedSize(30, 30);
    minimizeButton->setObjectName("minimizeButton");
    minimizeButton->setIcon(QIcon(":custom/icons/minimize.png"));

    maximizeButton = new QPushButton(this);
    maximizeButton->setFixedSize(30, 30);
    maximizeButton->setObjectName("maximizeButton");
    maximizeButton->setIcon(QIcon(":custom/icons/maximize.png"));

    closeButton = new QPushButton(this);
    closeButton->setFixedSize(30, 30);
    closeButton->setObjectName("closeButton");
    closeButton->setIcon(QIcon(":custom/icons/close.png"));

    minimizeButton->setStyleSheet("QPushButton{border:0px;background-color:transparent} QPushButton:hover{background:gray}");
    maximizeButton->setStyleSheet("QPushButton{border:0px;background-color:transparent} QPushButton:hover{background:gray}");
    closeButton->setStyleSheet("QPushButton{border:0px;background-color:transparent} QPushButton:hover{background:red}");


    QFrame* bottomFrame = new QFrame(this);
    bottomFrame->setFrameShape(QFrame::HLine);
    bottomFrame->setStyleSheet("QFrame{background:#346792;max-height:1px}");

    topLayout = new QHBoxLayout;
    leftLayout = new QHBoxLayout;
    customLayout = new QHBoxLayout;
    rightLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    leftLayout->addWidget(iconLabel);
    leftLayout->addWidget(titleLabel);
    topLayout->addLayout(leftLayout);
    topLayout->addStretch(1);
    topLayout->addLayout(customLayout);
    rightLayout->addWidget(minimizeButton);
    rightLayout->addWidget(maximizeButton);
    rightLayout->addWidget(closeButton);
    topLayout->addLayout(rightLayout);
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(1);
    bottomFrame->setGeometry(geometry().x()+5,50,geometry().width()+2,1);
    setLayout(mainLayout);

    setProperty("customTitleBar", true);
    setObjectName("customTitleBar");

    connect(minimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(maximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}
void CustomTitleBar::addCustomButton(QPushButton* newButton){
    if(newButton==nullptr)
        return;
    else{
        newButton->setFixedSize(30, 30);
        newButton->setStyleSheet("QPushButton{border:0px;background-color:transparent} QPushButton:hover{background:gray}");
        customLayout->addWidget(newButton);
    }
}
void CustomTitleBar::setMaximizeVisible(bool visible)
{
    if(!visible)
        maximizeButton->hide();
    else
        maximizeButton->show();
    maximizeVisible=visible;
}
void CustomTitleBar::setMinimizeVisible(bool visible)
{
    if(!visible)
        minimizeButton->hide();
    else
        minimizeButton->show();
    maximizeVisible=visible;
}
void CustomTitleBar::setWindowTitle(const QString &title)
{
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setText(title);
}

void CustomTitleBar::setWindowIcon(const QString &iconPath)
{
    QPixmap pixmap(iconPath);
    iconLabel->setPixmap(pixmap);
}

void CustomTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->accept();
    if(maximizeVisible==false)
        maximizeButton->click();
}

void CustomTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftButtonPressed = true;
        start = event->globalPos();
    }
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(leftButtonPressed)
    {
        parentWidget()->move(parentWidget()->geometry().topLeft() +
                             event->globalPos() - start);
        start = event->globalPos();
    }

}

void CustomTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftButtonPressed = false;
    }
}

bool CustomTitleBar::eventFilter(QObject *obj, QEvent *event)
{
    QWidget *pWidget = qobject_cast<QWidget *>(obj);
    switch(event->type())
    {
    case QEvent::WindowTitleChange:

        if (pWidget)
        {
            titleLabel->setText(pWidget->windowTitle());
            return true;
        }
        break;
    case QEvent::WindowIconChange:
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            iconLabel->setPixmap(icon.pixmap(iconLabel->size()));
            return true;
        }
        break;
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    default:
        break;
    }
    return QWidget::eventFilter(obj, event);
}

void CustomTitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            maximizeButton->setToolTip(tr("Restore"));
            maximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            maximizeButton->setProperty("maximizeProperty", "maximize");
            maximizeButton->setToolTip(tr("Maximize"));
        }
        maximizeButton->setStyle(QApplication::style());
    }
}

void CustomTitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == minimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == maximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == closeButton)
        {
            pWindow->close();
        }
    }
}
