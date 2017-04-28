#include "circuit.h"

Circuit::Circuit(QString name) :
    QObject()
{
    name_ = name;
    undoRedoStack_ = new UndoRedoStack();

//    addComponent(new InputPin());
    addComponent(new XnorGate(QPointF(0, 15), CircuitComponent::East));
    addComponent(new AndGate(QPointF(0, 10), CircuitComponent::East));
    addComponent(new OrGate(QPointF(0, 5), CircuitComponent::East));
    addComponent(new NandGate(QPointF(0, 0), CircuitComponent::East));
    addComponent(new NorGate(QPointF(0, -5), CircuitComponent::East));
    addComponent(new NotGate(QPointF(0, -10), CircuitComponent::East));
    addComponent(new XorGate(QPointF(0, -15), CircuitComponent::East));
}

QString Circuit::name() { return name_; }
void Circuit::setName(QString name)
{
    name_ = name;
    emit nameChanged(name);
}

QList<CircuitComponent*> Circuit::components() { return components_; }
QList<CircuitComponent*> Circuit::selectedComponents() { return selectedComponents_; }

bool Circuit::addComponent(CircuitComponent *component, bool doUpdate)
{
    if (!components_.contains(component)) {
        components_.append(component);
        connect(component, SIGNAL(updated()), this, SLOT(update()));

        if (doUpdate)
            update();

        return true;
    }
    return false;
}

bool Circuit::removeComponent(CircuitComponent *component, bool doUpdate)
{
    if (components_.removeOne(component)) {
        disconnect(component, SIGNAL(updated()), this, SLOT(update()));

        if (doUpdate)
            update();

        return true;
    }
    return false;
}

void Circuit::selectAll(bool doUpdate)
{
    foreach (CircuitComponent *component, components_) {
        selectComponent(component);
    }

    if (doUpdate)
        emit updated();
}

void Circuit::deselectAll(bool doUpdate)
{
    foreach (CircuitComponent *component, selectedComponents())
        component->setSelected(false);
    selectedComponents_.clear();

    if (doUpdate)
        emit updated();
}

void Circuit::selectComponent(CircuitComponent *component, bool doUpdate)
{
    if (!selectedComponents_.contains(component)) {
        component->setSelected(true);
        selectedComponents_.append(component);
    }
    if (doUpdate)
        emit updated();
}

void Circuit::deselectComponent(CircuitComponent *component, bool doUpdate)
{
    component->setSelected(false);

    if (selectedComponents_.contains(component)) {
        selectedComponents_.removeOne(component);
    }

    if (doUpdate)
        emit updated();
}

void Circuit::toggleSelectComponent(CircuitComponent *component, bool doUpdate)
{
    if (component->isSelected())
        deselectComponent(component, false);
    else
        selectComponent(component, false);

    if (doUpdate)
        emit updated();
}

void Circuit::setSelectedComponents(QList<CircuitComponent*> components, bool doUpdate)
{
    CircuitComponent *component;

    foreach (component, selectedComponents_)
        component->setSelected(false);

    selectedComponents_ = components;

    foreach (component, selectedComponents_)
        component->setSelected(true);

    if (doUpdate)
        emit updated();
}

bool Circuit::undoOperation()
{
    CircuitOperation *operation = (CircuitOperation*) undoRedoStack_->undo();
    if (operation == nullptr)
        return false;

    operation->revert(this);
    update();
    return true;
}

bool Circuit::redoOperation()
{
    CircuitOperation *operation = (CircuitOperation*) undoRedoStack_->redo();
    if (operation == nullptr)
        return false;

    operation->execute(this);
    update();
    return true;
}

void Circuit::executeOperation(CircuitOperation *operation)
{
    operation->execute(this);
    undoRedoStack_->push(operation);
    update();
}

void Circuit::update()
{
    emit updated();
}
