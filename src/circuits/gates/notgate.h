#ifndef NOTGATE_H
#define NOTGATE_H

#include <QObject>

#include "logicgate.h"

class NotGate : public LogicGate
{
    Q_OBJECT
public:
    NotGate(QPointF position = QPointF(0, 0), Orientation orientation = East);

public slots:
    void draw(QPainter &painter);

};

#endif // NOTGATE_H
