QT  += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += texttospeech
QT += multimedia
QT += sql

CONFIG += c++11

SOURCES += \
    src/bar/Trayicon.cpp \
    src/bar/menubar.cpp \
    src/bar/toolbar.cpp \
    src/dialog/aboutdialog.cpp \
    src/dialog/background.cpp \
    src/dialog/helpdialog.cpp \
    src/dialog/history.cpp \
    src/dialog/musicdialog.cpp \
    src/dialog/option.cpp \
    src/dialog/theme.cpp \
    src/game/game.cpp \
    src/game/solver.cpp \
    src/game/sudoku.cpp \
    src/library/filter.cpp \
    src/library/insert.cpp \
    src/library/library.cpp \
    src/library/tableFilter.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/settings.cpp \
    src/bar/slots.cpp

HEADERS += \
    include/dialog/aboutdialog.h \
    include/dialog/background.h \
    include/dialog/helpdialog.h \
    include/dialog/history.h \
    include/dialog/musicdialog.h \
    include/dialog/option.h \
    include/dialog/theme.h \
    include/include.h \
    include/library/filter.h \
    include/library/insert.h \
    include/library/library.h \
    include/mainwindow.h \
    include/solver.h \
    include/sudoku.h \


FORMS += \
    ui/aboutdialog.ui \
    ui/background.ui \
    ui/helpdialog.ui \
    ui/history.ui \
    ui/insert.ui \
    ui/library.ui \
    ui/mainwindow.ui \
    ui/musicdialog.ui \
    ui/option.ui \
    ui/theme.ui

RESOURCES += \
    qrc/dark/dark.qrc \
    qrc/icons.qrc

RC_ICONS = sudoku.ico

UI_DIR = tmp/ui

MOC_DIR = tmp/moc

RCC_DIR = tmp/rcc

OBJECTS_DIR = tmp/obj

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QMAKE_CXXFLAGS +=  -Wno-unused-parameter
QMAKE_CXXFLAGS +=  -Wno-deprecated-declarations
