#include "circuit.h"

Circuit::Circuit() :
    QObject()
{
//    addComponent(new InputPin());
    addComponent(new AndGate(QPointF(0, 0), CircuitComponent::East));
}

QList<CircuitComponent*> Circuit::components() { return components_; }
QList<CircuitComponent*> Circuit::selectedComponents() { return selectedComponents_; }

bool Circuit::addComponent(CircuitComponent *component)
{
    if (!components_.contains(component)) {
        components_.append(component);
        connect(component, SIGNAL(updated()), this, SLOT(update()));
        update();
        return true;
    }
    return false;
}

bool Circuit::removeComponent(CircuitComponent *component)
{
    if (components_.removeOne(component)) {
        disconnect(component, SIGNAL(updated()), this, SLOT(update()));
        update();
        return true;
    }
    return false;
}

void Circuit::selectAll(bool repaint)
{
    foreach (CircuitComponent *component, components_) {
        selectComponent(component);
    }

    if (repaint)
        emit updated();
}

void Circuit::deselectAll(bool repaint)
{
    foreach (CircuitComponent *component, selectedComponents())
        component->setSelected(false);
    selectedComponents_.clear();

    if (repaint)
        emit updated();
}

void Circuit::selectComponent(CircuitComponent *component, bool repaint)
{
    if (!selectedComponents_.contains(component)) {
        component->setSelected(true);
        selectedComponents_.append(component);
    }

    if (repaint)
        emit updated();
}

void Circuit::deselectComponent(CircuitComponent *component, bool repaint)
{
    if (selectedComponents_.contains(component)) {
        component->setSelected(false);
        selectedComponents_.removeOne(component);
    }

    if (repaint)
        emit updated();
}

void Circuit::toggleSelectComponent(CircuitComponent *component, bool repaint)
{
    if (component->isSelected())
        deselectComponent(component, false);
    else
        selectComponent(component, false);

    if (repaint)
        emit updated();
}

void Circuit::update()
{
    emit updated();
}
