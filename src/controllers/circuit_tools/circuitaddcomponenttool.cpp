#include "circuitaddcomponenttool.h"
#include "../../widgets/circuitview.h"

CircuitAddComponentTool::CircuitAddComponentTool(CircuitComponent *component) :
    CircuitTool(AddComponentTool)
{
    component_ = component;
}
