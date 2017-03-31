#ifndef OUTPUTPIN_H
#define OUTPUTPIN_H

#include <QObject>

#include "../circuitcomponent.h"

class OutputPin : public CircuitComponent
{
    Q_OBJECT
public:
    OutputPin(QPointF position, Orientation orientation);

signals:

public slots:
};

#endif // OUTPUTPIN_H
