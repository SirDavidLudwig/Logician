#ifndef CIRCUITSELECTTOOL_H
#define CIRCUITSELECTTOOL_H

#include "circuittool.h"

class CircuitSelectTool: public CircuitTool
{
public:
    CircuitSelectTool();

    bool mousePressEvent(CircuitView *view, QMouseEvent *event);
};

#endif // CIRCUITSELECTTOOL_H
