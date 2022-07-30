#SET LIBRARIES
QT += core gui sql svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#SET CONFIG
CONFIG += c++11
CONFIG -= debug_and_release
#CONFIG += precompile_header
#PRECOMPILED_HEADER = $$PWD/header/precompile.h
#SET ICON
RC_ICONS = logo.ico
#SET DESTDIR
DESTDIR = bin
INCLUDEPATH = header
#SET TEMP_DIR
UI_DIR = temp/ui
MOC_DIR = temp/moc
RCC_DIR = temp/rcc
OBJECTS_DIR = temp/obj

SOURCES += \
    source/controller/customdialog.cpp \
    source/controller/customTitleBar.cpp \
    source/main.cpp \
    source/widget.cpp \
    source/util/shareddata.cpp \
    source/util/datapathgetter.cpp \
    source/util/databasetablenamegetter.cpp \
    source/structure/group.cpp \
    source/structure/groups.cpp \
    source/structure/keyItem.cpp \
    source/structure/account.cpp \
    source/structure/accounts.cpp \
    source/structure/groupType.cpp \
    source/structure/groupTypes.cpp \
    source/structure/fieldType.cpp \
    source/structure/fieldTypes.cpp \
    source/structure/autofillInfo.cpp \
    source/dialog/logindialog.cpp \
    source/dialog/optiondialog.cpp \
    source/dialog/newitemdialog.cpp \
    source/dialog/newgroupdialog.cpp \
    source/dialog/newgrouptypedialog.cpp \
    source/controller/draggabletablewidget.cpp \
    source/function/viewFunction.cpp \
    source/function/saveFunction.cpp \
    source/function/groupFunction.cpp \
    source/function/keyItemFunction.cpp \
    source/function/tableWidgetFunction.cpp \
    source/customField/customComboBox.cpp \
    source/customField/customLineEdit.cpp \
    source/customField/customTextEdit.cpp \
    source/customField/abstractCustomField.cpp

HEADERS += \
#    header/precompile.h \
    header/controller/customTitleBar.h \
    header/controller/customdialog.h \
    header/widget.h \
    header/util/shareddata.h \
    header/util/datapathgetter.h \
    header/util/databasetablenamegetter.h \
    header/structure/group.h \
    header/structure/groups.h \
    header/structure/keyItem.h \
    header/structure/account.h \
    header/structure/accounts.h \
    header/structure/groupType.h \
    header/structure/groupTypes.h \
    header/structure/fieldType.h \
    header/structure/fieldTypes.h \
    header/structure/autofillInfo.h \
    header/controller/draggabletablewidget.h \
    header/customField/customTextEdit.h \
    header/customField/customComboBox.h \
    header/customField/customLineEdit.h \
    header/customField/abstractCustomField.h \
    header/dialog/logindialog.h \
    header/dialog/optiondialog.h \
    header/dialog/newitemdialog.h \
    header/dialog/newgroupdialog.h \
    header/dialog/newgrouptypedialog.h

FORMS += \
    ui/controller/customdialog.ui \
    ui/widget.ui \
    ui/dialog/logindialog.ui \
    ui/dialog/newgrouptypedialog.ui \
    ui/dialog/optiondialog.ui \
    ui/dialog/newitemdialog.ui \
    ui/dialog/newgroupdialog.ui \
    ui/customField/customTextEdit.ui \
    ui/customField/customLineEdit.ui \
    ui/customField/customComboBox.ui

RESOURCES += \
    qrc/dark/dark.qrc \
    qrc/custom/custom.qrc \
    qrc/win11_dark/win11_dark.qrc \
    qrc/win11_light/win11_light.qrc

QXLSX_PARENTPATH=./lib/QXlxs
QXLSX_HEADERPATH=./lib/QXlxs/QXlxsHeader/
QXLSX_SOURCEPATH=./lib/QXlxs/QXlxsSource/
include(./lib/QXlxs/QXlsx.pri)

QSLOG_PARENTPATH=./lib/QsLog
QSLOG_HEADERPATH=./lib/QsLog/
QSLOG_SOURCEPATH=./lib/QsLog/
include(./lib/QsLog/QsLog.pri)

FRAMELESSWINDOW_PARENTPATH=./lib/FramelessWindow
FRAMELESSWINDOW_HEADERPATH=./lib/FramelessWindow/
FRAMELESSWINDOW_SOURCEPATH=./lib/FramelessWindow/
include(./lib/FramelessWindow/FramelessWindow.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
