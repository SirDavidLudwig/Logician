#ifndef XNORGATE_H
#define XNORGATE_H

#include <QObject>

#include "logicgate.h"
#include "orgate.h"

class XnorGate : public LogicGate
{
    Q_OBJECT
public:
    XnorGate(QPointF position = QPointF(0, 0), Orientation orientation = East);

public slots:
    void draw(QPainter &painter);

};

#endif // XNORGATE_H
