#include "mainwindowui.h"

MainWindowUi::MainWindowUi(QWidget *parent) :
    QTabWidget(parent)
{
    lastTab_ = -1;
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onTabChange(int)));

    addTab(new CircuitView(this, 0), "Untitled");
    addTab(new CircuitView(this, 1), "Untitled");
    addTab(new CircuitView(this, 2), "Untitled");
    addTab(new CircuitView(this, 3), "Untitled");
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
