QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG += precompile_header
#PRECOMPILED_HEADER = $$PWD/header/precompile.h

DESTDIR = bin
UI_DIR = temp/ui
MOC_DIR = temp/moc
RCC_DIR = temp/rcc
OBJECTS_DIR = temp/obj
INCLUDEPATH = header

SOURCES += \
    source/structure/accounts.cpp \
    source/util/data.cpp \
    source/util/datapathgetter.cpp \
    source/structure/account.cpp \
    source/dialog/newgrouptypedialog.cpp \
    source/main.cpp \
    source/util/databasetablenamegetter.cpp \
    source/util/shareddata.cpp \
    source/widget.cpp \
    source/structure/group.cpp \
    source/structure/groups.cpp \
    source/structure/keyItem.cpp \
    source/structure/groupType.cpp \
    source/structure/groupTypes.cpp \
    source/structure/fieldType.cpp \
    source/structure/fieldTypes.cpp \
    source/structure/autofillInfo.cpp \
    source/dialog/logindialog.cpp \
    source/dialog/optiondialog.cpp \
    source/dialog/newitemdialog.cpp \
    source/dialog/newgroupdialog.cpp \
    source/controller/titleBar.cpp \
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
    header/dialog/newgrouptypedialog.h \
    header/structure/account.h \
    header/structure/accounts.h \
    header/structure/autofillInfo.h \
    header/util/data.h \
    header/util/databasetablenamegetter.h \
    header/util/datapathgetter.h \
    header/structure/fieldTypes.h \
    header/structure/groupTypes.h \
    header/structure/groups.h \
    header/structure/keyItem.h \
    header/widget.h \
    header/controller/titleBar.h \
    header/controller/draggabletablewidget.h \
    header/customField/customTextEdit.h \
    header/customField/customComboBox.h \
    header/customField/customLineEdit.h \
    header/customField/abstractCustomField.h \
    header/dialog/logindialog.h \
    header/dialog/optiondialog.h \
    header/dialog/newitemdialog.h \
    header/dialog/newgroupdialog.h \
    header/structure/group.h \
    header/structure/groupType.h \
    header/structure/fieldType.h \
    header/util/shareddata.h

FORMS += \
    ui/dialog/logindialog.ui \
    ui/dialog/newgrouptypedialog.ui \
    ui/dialog/optiondialog.ui \
    ui/dialog/newitemdialog.ui \
    ui/dialog/newgroupdialog.ui \
    ui/customField/customTextEdit.ui \
    ui/customField/customLineEdit.ui \
    ui/customField/customComboBox.ui \
    ui/widget.ui

RESOURCES += \
    qrc/dark/dark.qrc \
    qrc/custom/custom.qrc

QXLSX_PARENTPATH=./lib/QXlxs
QXLSX_HEADERPATH=./lib/QXlxs/QXlxsHeader/
QXLSX_SOURCEPATH=./lib/QXlxs/QXlxsSource/
include(./lib/QXlxs/QXlsx.pri)

QSLOG_PARENTPATH=./lib/QsLog
QSLOG_HEADERPATH=./lib/QsLog/
QSLOG_SOURCEPATH=./lib/QsLog/
include(./lib/QsLog/QsLog.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
