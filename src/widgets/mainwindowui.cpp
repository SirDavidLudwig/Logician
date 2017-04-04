#include "mainwindowui.h"
#include "../gui/mainwindow.h"

MainWindowUi::MainWindowUi(QWidget *parent) :
    QTabWidget(parent)
{
    lastTab_ = -1;
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onTabChange(int)));

    addCircuit(new Circuit("My circuit"));
}

void MainWindowUi::addCircuit(Circuit *circuit)
{
    Controller *controller = ControllerManager::controller(window());

    CircuitView *view = new CircuitView(this, circuit);
    view->setController((CircuitViewController*) controller);

    addTab(view, circuit->name());
}

void MainWindowUi::onTabChange(int index)
{
    if (lastTab_ != -1) {
        ((CircuitView*) widget(lastTab_))->setActive(false);
    }

    ((CircuitView*) widget(index))->setActive(true);
    lastTab_ = index;
}

void MainWindowUi::tabInserted(int index)
{
    setCurrentIndex(index);
}
