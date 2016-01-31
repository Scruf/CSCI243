/// file: circle.c
/// description: implementation for circle functions
/// @author RIT CS Dept.

/// define the precision of PI used by this module.
#define M_PI 3.14159265358979323846

#include "circle.h"

/// @return the area of a circle of the given radius.
double getAreas(int radius) {
    double temp = radius;
    return M_PI * temp * temp;
}

/// @return the circumference of a circle of the given radius.
double getCircumference(int radius) {

    return 2.0* M_PI * radius;
}
