#ifndef COMPONENTORIENTOPERATION_H
#define COMPONENTORIENTOPERATION_H

#include <QPointF>
#include <QList>
#include <QVector2D>

#include "circuitoperation.h"
#include "../../../circuits/circuit.h"
#include "../../../circuits/circuitcomponent.h"

class ComponentOrientOperation : public CircuitOperation
{
public:
    ComponentOrientOperation(CircuitComponent *component, CircuitComponent::Orientation orientation);
    ComponentOrientOperation(QList<CircuitComponent*> componentList, CircuitComponent::Orientation orientation);

    void execute(Circuit *circuit);
    void revert(Circuit *circuit);

private:
    QList<CircuitComponent*> components_;
    QList<CircuitComponent::Orientation> orientations_;
    CircuitComponent::Orientation orientation_;
};

#endif // COMPONENTORIENTOPERATION_H
