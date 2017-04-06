#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <QDebug>
#include <QObject>

#include "../core/operations/undoredostack.h"
#include "../core/operations/operation.h"

#include "circuitcomponent.h"

#include "inputs/inputpin.h"
#include "gates/andgate.h"
#include "gates/orgate.h"
#include "gates/nandgate.h"
#include "gates/norgate.h"
#include "gates/notgate.h"
#include "gates/xorgate.h"
#include "gates/xnorgate.h"


class Circuit : public QObject
{
    Q_OBJECT
public:

    Circuit(QString name = "Untitled");

    QString name();
    void setName(QString name);

    QList<CircuitComponent*> components();
    QList<CircuitComponent*> selectedComponents();

private:
    QString name_;

    QList<CircuitComponent*> components_;
    QList<CircuitComponent*> selectedComponents_;

    UndoRedoStack *undoRedoStack_;

signals:
    void nameChanged(QString);
    void updated();

public slots:
    bool addComponent(CircuitComponent *component, bool update = true);
    bool removeComponent(CircuitComponent *component, bool update = true);

    void selectAll(bool update = true);
    void deselectAll(bool update = true);

    void selectComponent(CircuitComponent *component, bool update = true);
    void deselectComponent(CircuitComponent *component, bool update = true);
    void toggleSelectComponent(CircuitComponent *component, bool update = true);

    bool redoOperation();
    bool undoOperation();
    void executeOperation(Operation *operation);

    void update();
};

#endif // CIRCUIT_H
