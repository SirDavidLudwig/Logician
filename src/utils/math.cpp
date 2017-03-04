#include "math.h"

long double Math::dmod(long double x, long double y)
{
    return x - floor(x/y)*y;
}

