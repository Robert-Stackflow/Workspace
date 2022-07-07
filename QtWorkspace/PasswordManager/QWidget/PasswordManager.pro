QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QT += sql
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additemdialog.cpp \
    function/itemFunction.cpp \
    function/saveFunction.cpp \
    function/tableFunction.cpp \
    function/viewFunction.cpp \
    logindialog.cpp \
    main.cpp \
    optiondialog.cpp \
    titleBar.cpp \
    widget.cpp

HEADERS += \
    additemdialog.h \
    logindialog.h \
    optiondialog.h \
    titleBar.h \
    widget.h

FORMS += \
    additemdialog.ui \
    logindialog.ui \
    optiondialog.ui \
    widget.ui

QXLSX_PARENTPATH=./
QXLSX_HEADERPATH=./QXlxsHeader/
QXLSX_SOURCEPATH=./QXlxsSource/
include(./QXlsx.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc \
    qrc/dark/dark.qrc
