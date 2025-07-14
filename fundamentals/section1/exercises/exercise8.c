/*
Exercise 8: Complex Scope and Shadowing
Objective: Master advanced scope concepts
Analyze and complete this code, explaining what happens in each printf:
#include <stdio.h>
int value = 100;  // global
void function1() {
    int value = 200;  // local
    printf("Function 1: %d\n", value);
    
    {
        int value = 300;  // inner block
        printf("Inner block function 1: %d\n", value);
    }
    
    printf("Function 1 after block: %d\n", value);
}
void function2() {
    printf("Function 2: %d\n", value);  // which value?
    // Add code here to:
    // 1. Create a local variable 'value' with value 400
    // 2. Print this local variable
    // 3. Find a way to access the global variable
}

int main() {
    printf("Main start: %d\n", value);
    function1();
    function2();
    
    // Complete the main testing different scopes
    return 0;
}
*/

#include <stdio.h>

int value = 100;  // global

void function1() {
    int value = 200;  // local
    printf("Function 1: %d\n", value);

    {
        int value = 300;  // inner block
        printf("Inner block function 1: %d\n", value);
    }

    printf("Function 1 after block: %d\n", value);
}

void function2() {
    printf("Function 2: %d\n", value);  // which value? >> global value 100
    int *ptr_global = &value; // pointer to the global variable

    // Add code here to:
    // 1. Create a local variable 'value' with value 400
    int value = 400;
    // 2. Print this local variable
    printf("Function 2: %d\n", value);
    // 3. Find a way to access the global variable
    printf("Function 2 (global): %d\n", *ptr_global);
}

int main() {
    printf("Main start: %d\n", value);
    function1();
    function2();
    {
        int value = 500;
        printf("Main inner block: %d\n", value);
    }
    return 0;
}