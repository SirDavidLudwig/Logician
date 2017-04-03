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
