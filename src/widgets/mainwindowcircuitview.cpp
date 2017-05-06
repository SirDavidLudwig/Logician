#include "mainwindowcircuitview.h"
#include "../gui/mainwindow.h"

MainWindowCircuitView::MainWindowCircuitView(QWidget *parent) :
    QTabWidget(parent)
{
    lastTab_ = -1;
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onTabChange(int)));
}

void MainWindowCircuitView::addCircuit(Circuit *circuit)
{
    CircuitView *view = new CircuitView(this, circuit);
    view->setController((CircuitViewController*) controller_);

    addTab(view, circuit->name());
}

void MainWindowCircuitView::onTabChange(int index)
{
    if (lastTab_ != -1) {
        ((CircuitView*) widget(lastTab_))->setActive(false);
    }

    ((CircuitView*) widget(index))->setActive(true);
    lastTab_ = index;
}

void MainWindowCircuitView::tabInserted(int index)
{
    setCurrentIndex(index);
}

void MainWindowCircuitView::setController(CircuitViewController *controller)
{
    controller_ = controller;
    for (int i = 0; i < count(); i++)
        ((CircuitView*) widget(i))->setController(controller);
}
