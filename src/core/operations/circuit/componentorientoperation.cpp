#include "componentorientoperation.h"

ComponentOrientOperation::ComponentOrientOperation(CircuitComponent *component, CircuitComponent::Orientation orientation) :
    Operation()
{
    components_.append(component);
    orientations_.append(component->orientation());
    orientation_ = orientation;
}

ComponentOrientOperation::ComponentOrientOperation(QList<CircuitComponent *> componentList, CircuitComponent::Orientation orientation) :
    Operation()
{
    components_ = componentList;
    orientation_ = orientation;

    foreach (CircuitComponent *component, componentList) {
        orientations_.append(component->orientation());
    }
}

void ComponentOrientOperation::revert(Circuit *circuit)
{
    for (int i = 0; i < components_.length(); i++) {
        components_[i]->setOrientation(orientations_[i], false);
    }
}

void ComponentOrientOperation::execute(Circuit *circuit)
{
    foreach (CircuitComponent *component, components_) {
        component->setOrientation(orientation_, false);
    }
}
