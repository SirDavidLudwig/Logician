#ifndef ORGATE_H
#define ORGATE_H

#include <QObject>

#include "logicgate.h"

class OrGate : public LogicGate
{
    Q_OBJECT
public:
    OrGate(QPointF position = QPointF(0, 0), Orientation orientation = East);

public slots:
    void draw(QPainter &painter);

};

#endif // ORGATE_H
