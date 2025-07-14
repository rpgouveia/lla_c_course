/*
    Exercise 5: Conditional Compilation
    Objective: Use #ifdef for debugging
    Create a program that:
    Has a DEBUG macro that can be defined or not
    If DEBUG is defined, print debug messages
    If not, execute only the main code
    Test by compiling with and without the DEBUG macro defined
    // Example structure:
    #define DEBUG  // comment/uncomment this line
    // Use #ifdef DEBUG to control the messages
*/

#include <stdio.h>

#define DEBUG  // comment/uncomment this line

int main() {
    int x = 5;
    int y = 10;
    int z = x + y;

#ifdef DEBUG
    printf("Debug: x = %d, y = %d, z = %d\n", x, y, z);
#endif

    printf("Result: %d\n", z);
    return 0;
}

/*
    With DEBUG defined:
    Debug: x = 5, y = 10, z = 15
    Result: 15
    
    Without DEBUG:
    Result: 15
*/