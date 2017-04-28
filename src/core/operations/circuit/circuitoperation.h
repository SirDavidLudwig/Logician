#ifndef CIRCUITOPERATION_H
#define CIRCUITOPERATION_H

#include <QList>

#include "../operation.h"
#include "../../../circuits/circuitcomponent.h"

class Circuit;

class CircuitOperation: public Operation
{
public:
    CircuitOperation();

    virtual void execute(Circuit *circuit);
    virtual void revert(Circuit *circuit);

private:
    QList<CircuitComponent*> selectedComponents_;
};

#endif // CIRCUITOPERATION_H
