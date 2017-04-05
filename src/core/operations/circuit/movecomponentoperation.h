#ifndef MOVECOMPONENTOPERATION_H
#define MOVECOMPONENTOPERATION_H

#include <QPointF>
#include <QList>
#include <QVector2D>

#include "../operation.h"
#include "../../../circuits/circuit.h"
#include "../../../circuits/circuitcomponent.h"

class MoveComponentOperation : public Operation
{
public:
    MoveComponentOperation(CircuitComponent *component, QPointF destination);
    MoveComponentOperation(CircuitComponent *component, QVector2D offset);
    MoveComponentOperation(QList<CircuitComponent*> componentList, QVector2D offset);

    void revert(Circuit *circuit);
    void execute(Circuit *circuit);

private:
    QList<CircuitComponent*> components_;
    const QVector2D offset_;
	
};

#endif // MOVECOMPONENTOPERATION_H
