#ifndef MATH_H
#define MATH_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <QtMath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef M_PIl
#define M_PIl (3.14159265358979323846264338327950288)
#endif

namespace Math
{
    // A fix for fmod
    double dmod(double x, double y);

    double radians(double degrees);
    double degrees(double radians);

    double absFloor(double value);
    double absCeil(double value);
}

#endif // MATH_H
