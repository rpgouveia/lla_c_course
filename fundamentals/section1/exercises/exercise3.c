/*
    Exercise 3: Simple Macro
    Objective: Use #define for constants
    Create a program that:
    Defines a macro for PI (3.14159)
    Defines a macro to calculate the area of a circle: CIRCLE_AREA(radius)
    Use these macros to calculate and print the area of a circle with radius 5
*/

#include <stdio.h>

#define PI 3.14159
#define CIRCLE_AREA(radius) (PI * (radius) * (radius))

int main() {
    int radius = 5;
    printf("Circle area with radius %d: %.2f\n", radius, CIRCLE_AREA(radius));
    return 0;
}