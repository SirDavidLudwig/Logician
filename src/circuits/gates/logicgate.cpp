#include "logicgate.h"

LogicGate::LogicGate(Point position, Orientation orientation) :
    CircuitComponent(position, orientation)
{
    setObjectName("LogicGate");
}
