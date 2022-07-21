QT += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH = "./header"

SOURCES += \
    source/customItem/customTextEdit.cpp \
    source/controller/draggabletablewidget.cpp \
    source/dialog/grouptypemanagerdialog.cpp \
    source/dialog/newitemdialog.cpp \
    source/customItem/customComboBox.cpp \
    source/customItem/abstractCustomItem.cpp \
    source/customItem/customLineEdit.cpp \
    source/util/groupType.cpp \
    source/dialog/main.cpp \
    source/dialog/widget.cpp \
    source/dialog/logindialog.cpp \
    source/dialog/optiondialog.cpp \
#    source/dialog/additemdialog.cpp \
    source/controller/titleBar.cpp \
    source/dialog/newgroupdialog.cpp \
    source/function/viewFunction.cpp \
    source/function/itemFunction.cpp \
    source/function/saveFunction.cpp \
    source/function/tableFunction.cpp \
    source/util/itemType.cpp

HEADERS += \
    header/controller/draggabletablewidget.h \
    header/customItem/customTextEdit.h \
    header/dialog/grouptypemanagerdialog.h \
    header/customItem/customComboBox.h \
    header/customItem/customLineEdit.h \
    header/dialog/newitemdialog.h \
    header/dialog/widget.h \
    header/dialog/logindialog.h \
    header/dialog/optiondialog.h \
#    header/dialog/additemdialog.h \
    header/controller/titleBar.h \
    header/customItem/abstractCustomItem.h \
    header/dialog/newgroupdialog.h \
    header/util/groupType.h \
    header/util/itemType.h \
    header/util/structures.h

FORMS += \
    ui/customTextEdit.ui \
    ui/grouptypemanagerdialog.ui \
    ui/newgroupdialog.ui \
    ui/newitemdialog.ui \
    ui/customLineEdit.ui \
    ui/customComboBox.ui \
    ui/widget.ui \
    ui/logindialog.ui \
#    ui/additemdialog.ui \
    ui/optiondialog.ui

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
