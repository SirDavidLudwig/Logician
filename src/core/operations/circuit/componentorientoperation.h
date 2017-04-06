#ifndef COMPONENTORIENTOPERATION_H
#define COMPONENTORIENTOPERATION_H

#include <QPointF>
#include <QList>
#include <QVector2D>

#include "../operation.h"
#include "../../../circuits/circuit.h"
#include "../../../circuits/circuitcomponent.h"

class ComponentOrientOperation : public Operation
{
public:
    ComponentOrientOperation(CircuitComponent *component, CircuitComponent::Orientation orientation);
    ComponentOrientOperation(QList<CircuitComponent*> componentList, CircuitComponent::Orientation orientation);

    void revert(Circuit *circuit);
    void execute(Circuit *circuit);

private:
    QList<CircuitComponent*> components_;
    QList<CircuitComponent::Orientation> orientations_;
    CircuitComponent::Orientation orientation_;
};

#endif // COMPONENTORIENTOPERATION_H
