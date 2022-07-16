QT += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH = "./header"

SOURCES += \
    source/dialog/main.cpp \
    source/dialog/widget.cpp \
    source/dialog/logindialog.cpp \
    source/dialog/optiondialog.cpp \
    source/dialog/additemdialog.cpp \
    source/controller/titleBar.cpp \
    source/function/viewFunction.cpp \
    source/function/itemFunction.cpp \
    source/function/saveFunction.cpp \
    source/function/tableFunction.cpp

HEADERS += \
    header/customItem/customLineEdit.h \
    header/dialog/widget.h \
    header/dialog/logindialog.h \
    header/dialog/optiondialog.h \
    header/dialog/additemdialog.h \
    header/controller/titleBar.h \
    header/passwordType/passwordType.h \
    header/customItem/abstractCustomItem.h

FORMS += \
    ui/widget.ui \
    ui/logindialog.ui \
    ui/optiondialog.ui \
    ui/additemdialog.ui

RESOURCES += \
    qrc/custom/custom.qrc \
    qrc/dark/dark.qrc

QXLSX_PARENTPATH=./lib/QXlxs
QXLSX_HEADERPATH=./lib/QXlxs/QXlxsHeader/
QXLSX_SOURCEPATH=./lib/QXlxs/QXlxsSource/
include(./lib/QXlxs/QXlsx.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
