#ifndef NORGATE_H
#define NORGATE_H

#include <QObject>

#include "logicgate.h"
#include "orgate.h"

class NorGate : public LogicGate
{
    Q_OBJECT
public:
    NorGate(QPointF position = QPointF(0, 0), Orientation orientation = East);

public slots:
    void draw(QPainter &painter);

};

#endif // NORGATE_H
