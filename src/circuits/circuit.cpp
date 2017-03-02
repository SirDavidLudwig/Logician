#include "circuit.h"

Circuit::Circuit() :
    QObject()
{
    addComponent(new InputPin());
    addComponent(new AndGate(QPointF(0, -5), CircuitComponent::East));
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
    qDebug() << components_.length() << "component(s) in the circuit";
    emit updated();
}
