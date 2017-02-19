QT += core gui svg widgets

TARGET = Logician
TEMPLATE = app

HEADERS += \
    src/core/application.h \
    src/gui/mainwindow.h \
    src/widgets/mainwindowui.h \
    src/widgets/mainwindowmenubar.h \
    src/utils/iconloader.h \
    src/widgets/mainwindowtoolbar.h \
    src/widgets/circuitview.h

SOURCES += \
    src/core/application.cpp \
    src/main.cpp \
    src/gui/mainwindow.cpp \
    src/widgets/mainwindowui.cpp \
    src/widgets/mainwindowmenubar.cpp \
    src/utils/iconloader.cpp \
    src/widgets/mainwindowtoolbar.cpp \
    src/widgets/circuitview.cpp

RESOURCES += \
    resources/resources.qrc
