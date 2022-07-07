#include "titleBar.h"
TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    if(parent!=NULL)
        setFixedWidth(parent->width());
    setFixedHeight(60);
    setWindowFlags(Qt::FramelessWindowHint);
    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(25, 25);
    m_iconLabel->setScaledContents(true);

    m_titleLabel = new QLabel(this);
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(13);
    font.setBold(true);
    m_titleLabel->setStyleSheet("color:#06ad56");
    m_titleLabel->setFont(font);
    m_titleLabel->setFixedHeight(30);
    m_titleLabel->setScaledContents(true);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_minimizeButton = new QPushButton(this);
    m_minimizeButton->setFixedSize(30, 30);
    m_minimizeButton->setObjectName("minimizeButton");
    m_minimizeButton->setIcon(QIcon(":application/qrc/minimize.png"));

    m_maximizeButton = new QPushButton(this);
    m_maximizeButton->setFixedSize(30, 30);
    m_maximizeButton->setObjectName("maximizeButton");
    m_maximizeButton->setIcon(QIcon(":application/qrc/maximize.png"));

    m_closeButton = new QPushButton(this);
    m_closeButton->setFixedSize(30, 30);
    m_closeButton->setObjectName("closeButton");
    m_closeButton->setIcon(QIcon(":application/qrc/close.png"));

    m_optionButton = new QPushButton(this);
    m_optionButton->setFixedSize(30, 30);
    m_optionButton->setObjectName("optionButton");
    m_optionButton->setIcon(QIcon(":application/qrc/setting.png"));

    m_userButton = new QPushButton(this);
    m_userButton->setFixedSize(30, 30);
    m_userButton->setObjectName("userButton");
    m_userButton->setIcon(QIcon(":application/qrc/unlogged.png"));

    m_optionButton->setStyleSheet("border:0px;background-color:transparent");
    m_userButton->setStyleSheet("border:0px;background-color:transparent");
    m_minimizeButton->setStyleSheet("border:0px;background-color:transparent");
    m_maximizeButton->setStyleSheet("border:0px;background-color:transparent");
    m_closeButton->setStyleSheet("border:0px;background-color:transparent");

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_iconLabel);
    layout->addWidget(m_titleLabel);
    layout->addStretch(1);
    layout->addWidget(m_userButton);
    layout->addWidget(m_optionButton);
    layout->addWidget(m_minimizeButton);
    layout->addWidget(m_maximizeButton);
    layout->addWidget(m_closeButton);
    setLayout(layout);

    setProperty("titleBar", true);
    setObjectName("titleBar");

    connect(m_minimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_maximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_closeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}
void TitleBar::forbiddenMaxmizeButton()
{
    m_maximizeButton->hide();
    m_maximizeForbidden=true;
}
void TitleBar::forbiddenUserButton()
{
    m_userButton->hide();
    m_optionButton->hide();
}
void TitleBar::setWindowTitle(const QString &title)
{
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setText(title);
}

void TitleBar::setTitleBarIcon(const QString &iconPath)
{
    QPixmap map(iconPath);
    m_iconLabel->setPixmap(map);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->accept();
    if(m_maximizeForbidden==false)
        m_maximizeButton->click();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftButtonPressed = true;
        m_start = event->globalPos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(m_leftButtonPressed)
    {
        parentWidget()->move(parentWidget()->geometry().topLeft() +
                             event->globalPos() - m_start);
        m_start = event->globalPos();
    }

}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftButtonPressed = false;
    }
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    QWidget *pWidget = qobject_cast<QWidget *>(obj);
    switch(event->type())
    {
    case QEvent::WindowTitleChange:

        if (pWidget)
        {
            m_titleLabel->setText(pWidget->windowTitle());
            return true;
        }
        break;
    case QEvent::WindowIconChange:
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_iconLabel->setPixmap(icon.pixmap(m_iconLabel->size()));
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

void TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_maximizeButton->setToolTip(tr("Restore"));
            m_maximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_maximizeButton->setProperty("maximizeProperty", "maximize");
            m_maximizeButton->setToolTip(tr("Maximize"));
        }

        m_maximizeButton->setStyle(QApplication::style());
    }
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_minimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_maximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_closeButton)
        {
            pWindow->close();
        }
    }
}
