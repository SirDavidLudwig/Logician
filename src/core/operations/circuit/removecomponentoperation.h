#ifndef REMOVECOMPONENTOPERATION_H
#define REMOVECOMPONENTOPERATION_H


#include <QPointF>
#include <QList>
#include <QVector2D>

#include "../operation.h"
#include "../../../circuits/circuit.h"
#include "../../../circuits/circuitcomponent.h"

class RemoveComponentOperation : public Operation
{
public:
    RemoveComponentOperation(CircuitComponent *component);
    RemoveComponentOperation(QList<CircuitComponent*> componentList);

    void revert(Circuit *circuit);
    void execute(Circuit *circuit);

private:
    QList<CircuitComponent*> components_;

};

#endif // REMOVECOMPONENTOPERATION_H
