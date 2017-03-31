QT += core gui opengl svg widgets

TARGET = Logician
TEMPLATE = app

HEADERS += \
    src/circuits/circuit.h \
    src/circuits/circuitcomponent.h \
    src/circutis/circuitsignal.h \
    src/circuits/circuitsocket.h \
    src/circuits/gates/andgate.h \
    src/circuits/gates/logicgate.h \
    src/circuits/inputs/inputpin.h \
    src/circuits/outputs/outputpin.h \
    src/circuits/wiring/wire.h \
    src/core/application.h \
    src/gui/mainwindow.h \
    src/utils/iconloader.h \
    src/utils/math.h \
    src/widgets/assetbrowser.h \
    src/widgets/circuitview.h \
    src/widgets/mainwindowmenubar.h \
    src/widgets/mainwindowtoolbar.h \
    src/widgets/mainwindowui.h

SOURCES += \
    src/main.cpp \
    src/circuits/circuit.cpp \
    src/circuits/circuitcomponent.cpp \
    src/circuits/circuitsignal.cpp \
    src/circuits/circuitsocket.cpp \
    src/circuits/gates/andgate.cpp \
    src/circuits/gates/logicgate.cpp \
    src/circuits/inputs/inputpin.cpp \
    src/circuits/outputs/outputpin.cpp \
    src/circuits/wiring/wire.cpp \
    src/core/application.cpp \
    src/gui/mainwindow.cpp \
    src/utils/iconloader.cpp \
    src/utils/math.cpp \
    src/widgets/assetbrowser.cpp \
    src/widgets/circuitview.cpp \
    src/widgets/mainwindowmenubar.cpp \
    src/widgets/mainwindowtoolbar.cpp \
    src/widgets/mainwindowui.cpp

RESOURCES += \
    resources/resources.qrc
