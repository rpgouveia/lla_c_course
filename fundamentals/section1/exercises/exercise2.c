/*
    Exercise 2: Simple Local Scope
    Objective: Understand scope within functions
    #include <stdio.h>
    int main() {
        int number = 10;
        
        // Your code here
        {
            // Declare a new variable 'number' with value 20
            // Print the value of this new variable    
        }
        // Print the value of the original 'number' variable
    }
    Complete the code and explain why the values are different.
*/

#include <stdio.h>

int main() {
    int number = 10;
    
    {
        // Declare a new variable 'number' with value 20
        int number = 20;
        // Print the value of this new variable
        printf("New value of 'number': %d\n", number);
    }
    // Print the value of the original 'number' variable
    printf("Original value of 'number': %d\n", number);
    return 0;
}

/*
    Explanation:
    In this code, we have two variables named 'number'. The first one is declared in the main function's scope with a value of 10. 
    Inside the inner block, we declare a new variable 'number' that shadows the outer one, and it is initialized with a value of 20.
    When we print the value of 'number' inside the inner block, it refers to the inner variable, which outputs 20.

    However, when we print the value of 'number' outside the inner block, it refers to the original variable declared in the main function, 
    which output is 10.

    This demonstrates how variable scope works in C: 
    Variables declared within a block are local to that block and do not affect variables with the same name in outer scopes.
*/
