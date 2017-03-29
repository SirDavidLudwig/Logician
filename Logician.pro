QT += core gui opengl svg widgets

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
    src/circuits/inputs/inputpin.h \
    src/circuits/outputs/outputpin.h \
	src/circuits/circuitcomponent.h \
    src/circuits/gates/andgate.h \
    src/utils/vector.h \
    src/utils/point.h \
    src/utils/math.h \
	src/circuits/circuitsocket.h \
	src/circuits/wiring/wire.h \
    src/circuits/circuitsignal.h

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
    src/circuits/inputs/inputpin.cpp \
    src/circuits/outputs/outputpin.cpp \
	src/circuits/circuitcomponent.cpp \
    src/circuits/gates/andgate.cpp \
    src/utils/vector.cpp \
    src/utils/point.cpp \
    src/utils/math.cpp \
	src/circuits/circuitsocket.cpp \
	src/circuits/wiring/wire.cpp \
    src/circuits/circuitsignal.cpp

RESOURCES += \
    resources/resources.qrc
