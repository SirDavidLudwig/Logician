#include "removecomponentoperation.h"

RemoveComponentOperation::RemoveComponentOperation(CircuitComponent *component) :
    CircuitOperation()
{
    components_.append(component);
}

RemoveComponentOperation::RemoveComponentOperation(QList<CircuitComponent*> componentList) :
    CircuitOperation()
{
    components_ = componentList;
}

void RemoveComponentOperation::execute(Circuit *circuit)
{
    CircuitOperation::execute(circuit);

    foreach (CircuitComponent *component, components_) {
        circuit->removeComponent(component, false);
    }
}

void RemoveComponentOperation::revert(Circuit *circuit)
{
    CircuitOperation::revert(circuit);

    foreach (CircuitComponent *component, components_) {
        circuit->addComponent(component, false);
        if (component->isSelected())
            circuit->selectComponent(component, false);
    }
}
