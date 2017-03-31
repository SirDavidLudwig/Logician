#ifndef INPUTPIN_H
#define INPUTPIN_H

#include <QDebug>
#include <QObject>
#include <QPointF>

#include "../circuitcomponent.h"

class InputPin : public CircuitComponent
{
    Q_OBJECT
public:
    InputPin(QPointF position = QPointF(0, 0));

signals:

public slots:
    void draw(QPainter &painter);
};

#endif // INPUTPIN_H
