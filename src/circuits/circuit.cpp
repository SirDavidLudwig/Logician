#include "circuit.h"

Circuit::Circuit() :
    QObject()
{
    addComponent(new InputPin());
    addComponent(new AndGate(QPointF(0, -20), CircuitComponent::North));
    addComponent(new AndGate(QPointF(0, -15), CircuitComponent::East));
    addComponent(new AndGate(QPointF(0, -10), CircuitComponent::West));
    addComponent(new AndGate(QPointF(0, -5), CircuitComponent::South));
}

QList<CircuitComponent*> Circuit::components() { return components_; }

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

void Circuit::update()
{
    emit updated();
}
