QT += core gui opengl svg widgets

TARGET = Logician
TEMPLATE = app

HEADERS += \
    src/circuits/circuit.h \
    src/circuits/circuitcomponent.h \
	src/circuits/circuitsignal.h \
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
    src/widgets/mainwindowui.h \
    src/controllers/circuitviewcontroller.h \
	src/controllers/circuit_tools/circuittool.h \
    src/controllers/circuit_tools/circuitselecttool.h \
    src/controllers/circuit_tools/circuitaddcomponenttool.h \
    src/controllers/circuit_tools/circuitwiringtool.h \
    src/controllers/circuit_tools/circuitpantool.h \
    src/circuits/gates/orgate.h \
    src/circuits/gates/notgate.h \
    src/circuits/gates/nandgate.h \
    src/circuits/gates/norgate.h \
    src/circuits/gates/xorgate.h \
    src/circuits/gates/xnorgate.h

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
    src/widgets/mainwindowui.cpp \
    src/controllers/circuitviewcontroller.cpp \
	src/controllers/circuit_tools/circuittool.cpp \
    src/controllers/circuit_tools/circuitselecttool.cpp \
    src/controllers/circuit_tools/circuitaddcomponenttool.cpp \
    src/controllers/circuit_tools/circuitwiringtool.cpp \
    src/controllers/circuit_tools/circuitpantool.cpp \
    src/circuits/gates/orgate.cpp \
    src/circuits/gates/notgate.cpp \
    src/circuits/gates/nandgate.cpp \
    src/circuits/gates/norgate.cpp \
    src/circuits/gates/xorgate.cpp \
    src/circuits/gates/xnorgate.cpp

RESOURCES += \
    resources/resources.qrc
