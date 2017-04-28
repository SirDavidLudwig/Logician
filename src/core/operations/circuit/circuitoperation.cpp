#include "circuitoperation.h"
#include "../../../circuits/circuit.h"

CircuitOperation::CircuitOperation() :
    Operation()
{

}

void CircuitOperation::execute(Circuit *circuit)
{
    if (selectedComponents_.length() > 0)
        circuit->setSelectedComponents(selectedComponents_);
    else
        selectedComponents_ = circuit->selectedComponents();
}

void CircuitOperation::revert(Circuit *circuit)
{
    circuit->setSelectedComponents(selectedComponents_);
}
