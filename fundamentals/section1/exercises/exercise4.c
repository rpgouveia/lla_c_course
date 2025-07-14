/*
    Exercise 4: Global vs Local Scope
    Objective: Understand issues with global variables
    #include <stdio.h>
    int counter = 0;  // global variable
    void increment() {
        // Implement this function
    }
    void decrement() {
        // Implement this function
    }
    int main() {
        // Test the functions and observe the effects on the global variable
        return 0;
    }
    Complete the code and then rewrite it avoiding the use of global variables.
    Compare both approaches.
*/

/*
// Using global variable approach
#include <stdio.h>

int counter = 0; // global variable

// Auxiliary functions
void increment() {
    counter++;
}

void decrement() {
    counter--;
}

// Main function
int main() {
    printf("Initial counter: %d\n", counter);
    increment();
    printf("Counter after increment: %d\n", counter);
    decrement();
    printf("Counter after decrement: %d\n", counter);
    return 0;
}
*/

// Avoiding global variable approach
#include <stdio.h>

// Auxiliary functions
int increment(int counter) {
    return counter + 1;
}
int decrement(int counter) {
    return counter - 1;
}

// Main function
int main() {
    int counter = 0; // local variable
    printf("Initial counter: %d\n", counter);
    counter = increment(counter);
    printf("Counter after increment: %d\n", counter);
    counter = decrement(counter);
    printf("Counter after decrement: %d\n", counter);
    return 0;
}

/*
    In the first approach, we used a global variable `counter` that can be accessed and modified by any function in the program. 
    This can lead to issues such as unintended side effects if multiple functions modify the same global variable, making debugging difficult.

    In the second approach, we avoided using a global variable by passing `counter` as an argument to the `increment` and `decrement` functions. 
    This encapsulates the state within the `main` function, making it clearer and safer to manage the variable's state without unintended interference
    from other parts of the code.
*/