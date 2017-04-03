#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <QDebug>
#include <QObject>
#include <QPainter>

#include "../circuitcomponent.h"
#include "../../utils/math.h"

class LogicGate : public CircuitComponent
{
    Q_OBJECT
public:
    LogicGate(QPointF position = QPointF(0, 0), Orientation orientation = East);

signals:

public slots:

};

#endif // LOGICGATE_H
