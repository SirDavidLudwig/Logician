#ifndef NANDGATE_H
#define NANDGATE_H

#include <QObject>

#include "logicgate.h"
#include "andgate.h"

class NandGate : public LogicGate
{
    Q_OBJECT
public:
    NandGate(QPointF position = QPointF(0, 0), Orientation orientation = East);

public slots:
    void draw(QPainter &painter);

};

#endif // NANDGATE_H
