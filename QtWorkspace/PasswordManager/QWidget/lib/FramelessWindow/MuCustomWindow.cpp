/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuCustomWindow.cpp
 * 自定义无边框窗体、对话框和提示框的实现文件，主要API实现文件
 *
 */

#include <QDialogButtonBox>
#include <QLabel>
#include <QCheckBox>
#include <QLabel>
#include "MuCustomWindow.h"

#ifdef Q_CC_MSVC
#pragma comment(lib, "user32.lib")
#endif

MuCustomWindow::MuCustomWindow(QWidget *parent)
    : MuShadowWindow<QWidget>(true, 20, parent)
{
    if (parent != nullptr) {
        setWindowTitle(parent->windowTitle());
        setWindowIcon(parent->windowIcon());
    } else {
        this->setWindowTitle("Custom Window");
        this->setWindowIcon(QIcon(":/images/logo.jpg"));
    }
    resize(800, 600);
}

MuCustomDialog::MuCustomDialog(QWidget *parent)
    : MuShadowWindow<QDialog>(false, 10, parent)
{
    if (parent != nullptr) {
        setWindowIcon(parent->windowIcon());
    } else {
        this->setWindowIcon(QIcon(":/images/logo.jpg"));
    }
    this->setWindowTitle("Custom Dialog");
    resize(400, 300);
    setResizable(false);
    titleBar()->setMinimumVisible(false);
    titleBar()->setMaximumVisible(false);
    setModal(false);
}

QString MuCustomMessageBox::m_titleStyleSheet;
QHash<QDialogButtonBox::StandardButton, QString> MuCustomMessageBox::m_buttonsStyleSheet;
MuCustomMessageBox::MuCustomMessageBox(QWidget *parent,
                                       const QString &title,
                                       const QString &text,
                                       QMessageBox::StandardButtons buttons,
                                       QMessageBox::StandardButton defaultButton)
    : MuShadowWindow<QDialog>(false, 10, parent)
{
    if (parent != nullptr) {
        setWindowIcon(parent->windowIcon());
    } else {
        this->setWindowIcon(QIcon(":/images/logo.jpg"));
    }
    this->setWindowTitle(title);

    setResizable(false);
    titleBar()->setMinimumVisible(false);
    titleBar()->setMaximumVisible(false);

    m_pButtonBox = new QDialogButtonBox(this);
    m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
    setDefaultButton(defaultButton);

    m_pIconLabel = new QLabel(this);
    m_pLabel = new QLabel(this);
    initStyle();

    QPixmap pixmap(":/Images/information");
    m_pIconLabel->setPixmap(pixmap);
    m_pIconLabel->setFixedSize(35, 35);
    m_pIconLabel->setScaledContents(true);

    m_pLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pLabel->setObjectName("messageTextLabel");
    m_pLabel->setOpenExternalLinks(true);
    m_pLabel->setText(text);

    QWidget *pClientWidget = new QWidget(this);
    m_pGridLayout = new QGridLayout(pClientWidget);
    m_pGridLayout->addWidget(m_pIconLabel, 0, 0, 2, 1, Qt::AlignTop);
    m_pGridLayout->addWidget(m_pLabel, 0, 1, 2, 1);
    m_pGridLayout->addWidget(m_pButtonBox, m_pGridLayout->rowCount(), 0, 1, m_pGridLayout->columnCount());
    m_pGridLayout->setSizeConstraint(QLayout::SetNoConstraint);
    m_pGridLayout->setHorizontalSpacing(10);
    m_pGridLayout->setVerticalSpacing(10);
    m_pGridLayout->setContentsMargins(10, 10, 10, 10);
    clientLayout()->addWidget(pClientWidget);

    translateUI();


    connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}

QAbstractButton *MuCustomMessageBox::clickedButton() const
{
    return m_pClickedButton;
}

QMessageBox::StandardButton MuCustomMessageBox::standardButton(QAbstractButton *button) const
{
    return (QMessageBox::StandardButton)m_pButtonBox->standardButton(button);
}

void MuCustomMessageBox::setDefaultButton(QPushButton *button)
{
    if (!m_pButtonBox->buttons().contains(button))
        return;

    m_pDefaultButton = button;
    button->setDefault(true);
    button->setFocus();
}

void MuCustomMessageBox::setDefaultButton(QMessageBox::StandardButton button)
{
    setDefaultButton(m_pButtonBox->button(QDialogButtonBox::StandardButton(button)));
}

void MuCustomMessageBox::setTitle(const QString &title)
{
    setWindowTitle(title);
}

void MuCustomMessageBox::setText(const QString &text)
{
    m_pLabel->setText(text);
}

void MuCustomMessageBox::setIcon(const QString &icon)
{
    m_pIconLabel->setPixmap(QPixmap(icon));
}

void MuCustomMessageBox::addWidget(QWidget *pWidget)
{
    m_pLabel->hide();
    m_pGridLayout->addWidget(pWidget, 0, 1, 2, 1);
}

QLabel *MuCustomMessageBox::titleLabel() const
{
    return m_pLabel;
}

QDialogButtonBox *MuCustomMessageBox::buttonBox() const
{
    return m_pButtonBox;
}

QMessageBox::StandardButton MuCustomMessageBox::showInformation(QWidget *parent,
                                                                const QString &title,
                                                                const QString &text,
                                                                QMessageBox::StandardButton buttons)
{
    MuCustomMessageBox msgBox(parent, title, text, buttons);
    msgBox.setIcon(":/images/informationBlue_48.png");
    if (msgBox.exec() == -1)
            qDebug("1");
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton MuCustomMessageBox::showError(QWidget *parent,
                                                          const QString &title,
                                                          const QString &text,
                                                          QMessageBox::StandardButtons buttons,
                                                          QMessageBox::StandardButton defaultButton)
{
    MuCustomMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/errorRed_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton MuCustomMessageBox::showSuccess(QWidget *parent,
                                                            const QString &title,
                                                            const QString &text,
                                                            QMessageBox::StandardButtons buttons,
                                                            QMessageBox::StandardButton defaultButton)
{
    MuCustomMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/successGreen_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton MuCustomMessageBox::showQuestion(QWidget *parent,
                                                             const QString &title,
                                                             const QString &text,
                                                             QMessageBox::StandardButtons buttons,
                                                             QMessageBox::StandardButton defaultButton)
{
    MuCustomMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/questionBlue_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton MuCustomMessageBox::showWarning(QWidget *parent,
                                                            const QString &title,
                                                            const QString &text,
                                                            QMessageBox::StandardButtons buttons,
                                                            QMessageBox::StandardButton defaultButton)
{
    MuCustomMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/warningYellow_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton MuCustomMessageBox::showCritical(QWidget *parent,
                                                             const QString &title,
                                                             const QString &text,
                                                             QMessageBox::StandardButtons buttons,
                                                             QMessageBox::StandardButton defaultButton)
{
    MuCustomMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/warningYellow_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton MuCustomMessageBox::showCheckBoxQuestion(QWidget *parent,
                                                                     const QString &title,
                                                                     const QString &text,
                                                                     QMessageBox::StandardButtons buttons,
                                                                     QMessageBox::StandardButton defaultButton)
{
    MuCustomMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/questionBlue_48.png");

    QCheckBox *pCheckBox = new QCheckBox(&msgBox);
    pCheckBox->setText(text);
    msgBox.addWidget(pCheckBox);
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;

    QMessageBox::StandardButton standardButton = msgBox.standardButton(msgBox.clickedButton());
    if (standardButton == QMessageBox::Yes) {
        return pCheckBox->isChecked() ? QMessageBox::Yes : QMessageBox::No;
    }
    return QMessageBox::Cancel;
}

void MuCustomMessageBox::setButtonStyleSheet(QDialogButtonBox::StandardButton button, const QString &styleSheet)
{
    m_buttonsStyleSheet[button] = styleSheet;
}

void MuCustomMessageBox::setTitleStyleSheet(const QString &styleSheet)
{
    m_titleStyleSheet = styleSheet;
}

void MuCustomMessageBox::onButtonClicked(QAbstractButton *button)
{
    m_pClickedButton = button;
    done(execReturnCode(button));
}

int MuCustomMessageBox::execReturnCode(QAbstractButton *button)
{
    int nResult = m_pButtonBox->standardButton(button);
    return nResult;
}

void MuCustomMessageBox::translateUI()
{
    QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Yes);
    if (pYesButton != nullptr)
        pYesButton->setText(tr("Yes"));

    QPushButton *pNoButton = m_pButtonBox->button(QDialogButtonBox::No);
    if (pNoButton != nullptr)
        pNoButton->setText(tr("No"));

    QPushButton *pOkButton = m_pButtonBox->button(QDialogButtonBox::Ok);
    if (pOkButton != nullptr)
        pOkButton->setText(tr("Ok"));

    QPushButton *pCancelButton = m_pButtonBox->button(QDialogButtonBox::Cancel);
    if (pCancelButton != nullptr)
        pCancelButton->setText(tr("Cancel"));
}

void MuCustomMessageBox::initStyle()
{
    QPushButton *pButton = nullptr;
    for (auto key : m_buttonsStyleSheet.keys()) {
        pButton = m_pButtonBox->button(key);
        if (pButton != nullptr)
            pButton->setStyleSheet(m_buttonsStyleSheet.value(key));
    }

    titleBar()->titleLabel()->setStyleSheet(m_titleStyleSheet);
}

