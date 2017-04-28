#ifndef REMOVECOMPONENTOPERATION_H
#define REMOVECOMPONENTOPERATION_H


#include <QPointF>
#include <QList>
#include <QVector2D>

#include "circuitoperation.h"
#include "../../../circuits/circuit.h"
#include "../../../circuits/circuitcomponent.h"

class RemoveComponentOperation : public CircuitOperation
{
public:
    RemoveComponentOperation(CircuitComponent *component);
    RemoveComponentOperation(QList<CircuitComponent*> componentList);

    void execute(Circuit *circuit);
    void revert(Circuit *circuit);

private:
    QList<CircuitComponent*> components_;

};

#endif // REMOVECOMPONENTOPERATION_H
