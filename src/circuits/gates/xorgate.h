#ifndef XORGATE_H
#define XORGATE_H

#include <QObject>

#include "logicgate.h"

class XorGate : public LogicGate
{
    Q_OBJECT
public:
    XorGate(QPointF position = QPointF(0, 0), Orientation orientation = East);

public slots:
    void draw(QPainter &painter);

};

#endif // XORGATE_H
