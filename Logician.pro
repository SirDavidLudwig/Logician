QT += core gui widgets

TARGET = Logician
TEMPLATE = app

HEADERS += \
    src/core/application.h \
    src/gui/mainwindow.h \
    src/widgets/viewport.h \
    src/widgets/mainwindowui.h \
    src/widgets/mainwindowmenubar.h

SOURCES += \
    src/core/application.cpp \
    src/main.cpp \
    src/gui/mainwindow.cpp \
    src/widgets/viewport.cpp \
    src/widgets/mainwindowui.cpp \
    src/widgets/mainwindowmenubar.cpp

RESOURCES += \
    resources/resources.qrc
