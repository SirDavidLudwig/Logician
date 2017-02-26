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
    src/widgets/circuitview.h \
    src/widgets/assetbrowser.h \
    src/circuits/gates/logicgate.h \
    src/circuits/circuit.h \
    src/circuits/circuitentity.h

SOURCES += \
    src/core/application.cpp \
    src/main.cpp \
    src/gui/mainwindow.cpp \
    src/widgets/mainwindowui.cpp \
    src/widgets/mainwindowmenubar.cpp \
    src/utils/iconloader.cpp \
    src/widgets/mainwindowtoolbar.cpp \
    src/widgets/circuitview.cpp \
    src/widgets/assetbrowser.cpp \
    src/circuits/gates/logicgate.cpp \
    src/circuits/circuit.cpp \
    src/circuits/circuitentity.cpp

RESOURCES += \
    resources/resources.qrc
