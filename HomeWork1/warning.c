_s/// file: warning.c
/// description: faulty code example that needs fixing.
/// @author RIT CS Dept.

#include <stdio.h>

/// compute a value.
int compute(int a) {
    int b = a * 5;
    return b;
}

/// main function
int main() {

    int y = compute(20);

    printf("%i\n", y);

    return 0;
}
