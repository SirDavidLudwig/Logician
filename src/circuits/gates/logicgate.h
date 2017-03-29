#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <QDebug>
#include <QObject>
#include <QPainter>
#include "../circuitcomponent.h"

class LogicGate : public CircuitComponent
{
    Q_OBJECT
public:
    LogicGate(Point position = Point(0, 0), Orientation orientation = North);

signals:

public slots:

};

#endif // LOGICGATE_H
