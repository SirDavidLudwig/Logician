#include "movecomponentoperation.h"

MoveComponentOperation::MoveComponentOperation(CircuitComponent *component, QPointF destination) :
    CircuitOperation(), offset_(QVector2D(destination - component->position()))
{
    components_.append(component);
}

MoveComponentOperation::MoveComponentOperation(CircuitComponent *component, QVector2D offset) :
    CircuitOperation(), offset_(offset)
{
    components_.append(component);
}

MoveComponentOperation::MoveComponentOperation(QList<CircuitComponent *> componentList, QVector2D offset) :
    CircuitOperation(), offset_(offset)
{
    components_ = componentList;
}

void MoveComponentOperation::execute(Circuit *circuit)
{
    CircuitOperation::execute(circuit);

    foreach (CircuitComponent *component, components_) {
        component->setPosition(component->position() + offset_.toPointF(), false);
    }

}

void MoveComponentOperation::revert(Circuit *circuit)
{
    CircuitOperation::revert(circuit);

    foreach (CircuitComponent *component, components_) {
        component->setPosition(component->position() - offset_.toPointF(), false);
    }
}

