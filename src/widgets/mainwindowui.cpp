#include "mainwindowui.h"

MainWindowUi::MainWindowUi(QWidget *parent) :
    QTabWidget(parent)
{
    addTab(new CircuitView(), "Untitled");
    addTab(new CircuitView(), "Untitled");
    addTab(new CircuitView(), "Untitled");
    addTab(new CircuitView(), "Untitled");
}
