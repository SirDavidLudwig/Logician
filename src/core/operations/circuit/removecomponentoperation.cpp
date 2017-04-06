#include "removecomponentoperation.h"

RemoveComponentOperation::RemoveComponentOperation(CircuitComponent *component) :
    Operation()
{
    components_.append(component);
}

RemoveComponentOperation::RemoveComponentOperation(QList<CircuitComponent*> componentList) :
    Operation()
{
    components_ = componentList;
}

void RemoveComponentOperation::revert(Circuit *circuit)
{
    foreach (CircuitComponent *component, components_) {
        circuit->addComponent(component, false);
        if (component->isSelected())
            circuit->selectComponent(component, false);
    }
}

void RemoveComponentOperation::execute(Circuit *circuit)
{
    foreach (CircuitComponent *component, components_) {
        circuit->removeComponent(component, false);
    }
}
