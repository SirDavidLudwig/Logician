#include "math.h"

double Math::dmod(double x, double y)
{
    return x - floor(x/y)*y;
}

