#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <QDebug>
#include <QObject>

#include "circuitcomponent.h"

#include "inputs/inputpin.h"
#include "gates/andgate.h"

class Circuit : public QObject
{
    Q_OBJECT
public:

    Circuit();

    QList<CircuitComponent*> components();
    QList<CircuitComponent*> selectedComponents();

private:
    QList<CircuitComponent*> components_;
    QList<CircuitComponent*> selectedComponents_;

signals:
    void updated();

public slots:
    bool addComponent(CircuitComponent *component);
    bool removeComponent(CircuitComponent *component);

    void selectAll(bool repaint = true);
    void deselectAll(bool repaint = true);
    void selectComponent(CircuitComponent *component, bool repaint = true);
    void deselectComponent(CircuitComponent *component, bool repaint = true);
    void toggleSelectComponent(CircuitComponent *component, bool repaint = true);

    void update();
};

#endif // CIRCUIT_H
