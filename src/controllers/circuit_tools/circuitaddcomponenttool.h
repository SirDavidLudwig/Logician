#ifndef CIRCUITADDCOMPONENTTOOL_H
#define CIRCUITADDCOMPONENTTOOL_H

#include "circuittool.h"
#include "../../circuits/circuitcomponent.h"

class CircuitAddComponentTool: public CircuitTool
{
public:
    CircuitAddComponentTool(CircuitComponent *component);

private:
    CircuitComponent *component_ = nullptr;
};

#endif // CIRCUITADDCOMPONENTTOOL_H
