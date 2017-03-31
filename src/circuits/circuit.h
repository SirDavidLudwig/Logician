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

private:
    QList<CircuitComponent*> components_;

signals:
    void updated();

public slots:
    bool addComponent(CircuitComponent *component);
    bool removeComponent(CircuitComponent *component);

    void update();
};

#endif // CIRCUIT_H
