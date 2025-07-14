/*
Exercise 6: Macros with Parameters
Objective: Create more complex macros
Implement the following macros:

MAX(a, b) - returns the greater value between a and b
MIN(a, b) - returns the lesser value between a and b
SQUARE(x) - returns x²
IS_EVEN(n) - returns 1 if n is even, 0 otherwise

Test all macros in a main program.
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SQUARE(x) ((x) * (x))
#define IS_EVEN(n) ((n) % 2 == 0 ? true : false)

int main() {
    int a = 5, b = 10;

    printf("Values: a = %d, b = %d\n", a, b);
    printf("Max: %d\n", MAX(a, b));
    printf("Min: %d\n", MIN(a, b));
    printf("Square (%d): %d\n", a, SQUARE(a));
    printf("Square (%d): %d\n", b, SQUARE(b));
    printf("%d is even? %s\n", a, IS_EVEN(a) ? "true" : "false");
    printf("%d is even? %s\n", b, IS_EVEN(b) ? "true" : "false");

    return 0;
}
