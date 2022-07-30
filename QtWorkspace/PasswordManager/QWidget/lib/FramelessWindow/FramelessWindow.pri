INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
include(./common.pri)

    HEADERS += \
        $$PWD/MuFramelessHelper.h \
        $$PWD/MuFramelessHelperPrivate.h \
        $$PWD/MuCursorPosCalculator.h \
        $$PWD/MuTitleBar.h \
        $$PWD/MuWidgetData.h \
        $$PWD/MuShadowWidget.h \
        $$PWD/MuShadowWindow.h \
        $$PWD/MuCustomWindow.h \
        $$PWD/FramelessWindow_Global.h

    SOURCES += \
        $$PWD/MuFramelessHelper.cpp \
        $$PWD/MuWidgetData.cpp\
        $$PWD/MuCursorPosCalculator.cpp \
        $$PWD/MuTitleBar.cpp \
        $$PWD/MuShadowWidget.cpp \
        $$PWD/MuCustomWindow.cpp

    RESOURCES += \
        $$PWD/images.qrc

    QT += widgets




