#include "math.h"

double Math::dmod(double x, double y)
{
    return x - floor(x/y)*y;
}

double Math::radians(double degrees)
{
    return degrees*M_PIl/180;
}

double Math::degrees(double radians)
{
    return radians*180/M_PIl;
}

// Absolute floor, 1.4 becomes 1, -1.4 becomes -1
double Math::absFloor(double value)
{
    return floor(abs(value)) * (value < 0 ? -1 : 1);
}

// Absolute ceil, 1.4 becomes 2, -1.4 becomes -2
double Math::absCeil(double value)
{
    return ceil(abs(value)) * (value < 0 ? -1 : 1);
}
