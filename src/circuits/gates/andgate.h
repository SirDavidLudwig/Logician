#ifndef ANDGATE_H
#define ANDGATE_H

#include <QObject>

#include "logicgate.h"

class AndGate : public LogicGate
{
    Q_OBJECT
public:
    AndGate(QPointF position = QPointF(0, 0), Orientation orientation = East);

public slots:
    void draw(QPainter &painter);

};

#endif // ANDGATE_H
