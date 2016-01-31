/// file: main.c
/// description: simple main program uses the circle module.
/// @author RIT CS Dept.

#include <stdio.h>        // printf
#include "circle.h"    // getArea, getCircumference

/// Computes and displays the area and circumference
/// of a circle of a given radius.

void compute(int radius) {

    printf("Area of circle with radius %f: %f\n",
           radius, getAreas(radius));
    printf("Circumference of circle with radius %d: %f\n",
           radius, getCircumference(radius));
}

/// main program uses the circle module.
int main() {
    compute(1.0);
    compute(5.0);
    compute(10.0);
    return 0;

}
