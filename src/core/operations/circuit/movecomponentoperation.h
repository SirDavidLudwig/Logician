#ifndef MOVECOMPONENTOPERATION_H
#define MOVECOMPONENTOPERATION_H

#include <QPointF>
#include <QList>
#include <QVector2D>

#include "circuitoperation.h"
#include "../../../circuits/circuit.h"
#include "../../../circuits/circuitcomponent.h"

class MoveComponentOperation : public CircuitOperation
{
public:
    MoveComponentOperation(CircuitComponent *component, QPointF destination);
    MoveComponentOperation(CircuitComponent *component, QVector2D offset);
    MoveComponentOperation(QList<CircuitComponent*> componentList, QVector2D offset);

    void execute(Circuit *circuit);
    void revert(Circuit *circuit);

private:
    QList<CircuitComponent*> components_;
    const QVector2D offset_;
	
};

#endif // MOVECOMPONENTOPERATION_H
