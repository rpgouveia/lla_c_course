/*
Exercise 7: Preprocessor Configuration System
Objective: Create a configurable calculator program using the preprocessor.

Create a calculator program that uses the preprocessor to:
Define which operations are available (ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION)
Define the data type (USE_FLOAT or USE_INT)
Define debug level (DEBUG_LEVEL_1, DEBUG_LEVEL_2, DEBUG_LEVEL_3)

The program should compile different versions based on the active definitions.
// Configurations (comment/uncomment as needed)
#define ADDITION
#define SUBTRACTION
// #define MULTIPLICATION
// #define DIVISION
#define USE_FLOAT
// #define DEBUG_LEVEL_1
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// ===== CONFIGURATIONS (comment/uncomment as needed) =====
#define ADDITION
#define SUBTRACTION  
#define MULTIPLICATION
#define DIVISION

// Define ONLY ONE data type:
#define USE_FLOAT
// #define USE_INT

// Define ONLY ONE debug level (or none):
// #define DEBUG_LEVEL_1
// #define DEBUG_LEVEL_2
#define DEBUG_LEVEL_3

// ===== DEFINITION CONDITIONAL OF DATA TYPE =====
#ifdef USE_FLOAT
    typedef float number_t;
    #define PRINT_NUMBER(num) printf("%.2f", num)
    #define PRECISION "with 2 decimal places"
    
    // safe_read_float function to read floats safely
    int safe_read_float(number_t *value) {
        char buffer[100];
        char *endptr;
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0; // Read error
        }
        
        // Convert string to float
        // Using strtof to handle conversion and check for errors
        *value = strtof(buffer, &endptr);

        // Check if the conversion was successful
        if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
            return 0; // Conversion failed
        }

        return 1; // Success
    }
    #define SAFE_READ_NUMBER(ptr) safe_read_float(ptr)
    
#elif defined(USE_INT)
    typedef int number_t;
    #define PRINT_NUMBER(num) printf("%d", num)
    #define PRECISION "integer numbers"
    
    // safe_read_int function to read integers safely
    int safe_read_int(number_t *value) {
        char buffer[100];
        char *endptr;
        long temp;
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0; // Read error
        }
        
        // Convert string to long first to check range
        // This helps to avoid overflow issues with int
        temp = strtol(buffer, &endptr, 10);

        // Check if the conversion was successful and if it's in the int range
        if (endptr == buffer || (*endptr != '\n' && *endptr != '\0') || 
            temp < INT_MIN || temp > INT_MAX) {
            return 0; // Conversion failed
        }
        
        *value = (int)temp;
        return 1; // Success
    }
    #define SAFE_READ_NUMBER(ptr) safe_read_int(ptr)
    
#else
    #error "You must define either USE_FLOAT or USE_INT"
#endif

// ===== MACROS FOR OPERATIONS =====
#ifdef ADDITION
    #define DO_ADDITION(a, b) ((a) + (b))
#endif

#ifdef SUBTRACTION
    #define DO_SUBTRACTION(a, b) ((a) - (b))
#endif

#ifdef MULTIPLICATION
    #define DO_MULTIPLICATION(a, b) ((a) * (b))
#endif

#ifdef DIVISION
    #define DO_DIVISION(a, b) ((b) != 0 ? ((a) / (b)) : (printf("Error: Division by zero!\n"), 0))
#endif

// ===== MACROS FOR DEBUG =====
#ifdef DEBUG_LEVEL_1
    #define DEBUG(msg) printf("DEBUG: %s\n", msg)
#elif defined(DEBUG_LEVEL_2)
    #define DEBUG(msg) printf("DEBUG: %s (file: %s, line: %d)\n", msg, __FILE__, __LINE__)
#elif defined(DEBUG_LEVEL_3)
    #define DEBUG(msg) printf("DEBUG: %s (file: %s, line: %d, function: %s)\n", msg, __FILE__, __LINE__, __func__)
#else
    #define DEBUG(msg)  // Does nothing if debug is not active
#endif

// ===== CHECK IF AT LEAST ONE OPERATION IS DEFINED =====
#if !defined(ADDITION) && !defined(SUBTRACTION) && !defined(MULTIPLICATION) && !defined(DIVISION)
    #error "At least one operation must be defined (ADDITION, SUBTRACTION, MULTIPLICATION, or DIVISION)"
#endif

// ===== MAIN FUNCTION =====
int main() {
    number_t a, b, result;
    
    printf("=== CONFIGURABLE CALCULATOR ===\n");
    printf("Mode: %s\n", PRECISION);
    printf("Available operations:");

    // Show which operations are available
    #ifdef ADDITION
        printf(" [+]");
    #endif
    #ifdef SUBTRACTION
        printf(" [-]");
    #endif
    #ifdef MULTIPLICATION
        printf(" [*]");
    #endif
    #ifdef DIVISION
        printf(" [/]");
    #endif
    printf("\n");
    printf("===============================\n\n");

    // Safe input reading with validation
    printf("Enter first number: ");
    while (!SAFE_READ_NUMBER(&a)) {
        printf("Invalid input! Please enter a valid number: ");
        // Clear the buffer if necessary (fgets already reads the whole line)
    }
    
    printf("Enter second number: ");
    while (!SAFE_READ_NUMBER(&b)) {
        printf("Invalid input! Please enter a valid number: ");
        // Clear the buffer if necessary (fgets already reads the whole line)
    }
    
    printf("\nResults:\n");
    printf("--------\n");

    // Execute operations based on the defined macros
    #ifdef ADDITION
        DEBUG("Performing addition");
        result = DO_ADDITION(a, b);
        printf("Addition: ");
        PRINT_NUMBER(a);
        printf(" + ");
        PRINT_NUMBER(b);
        printf(" = ");
        PRINT_NUMBER(result);
        printf("\n");
    #endif

    #ifdef SUBTRACTION
        DEBUG("Performing subtraction");
        result = DO_SUBTRACTION(a, b);
        printf("Subtraction: ");
        PRINT_NUMBER(a);
        printf(" - ");
        PRINT_NUMBER(b);
        printf(" = ");
        PRINT_NUMBER(result);
        printf("\n");
    #endif

    #ifdef MULTIPLICATION
        DEBUG("Performing multiplication");
        result = DO_MULTIPLICATION(a, b);
        printf("Multiplication: ");
        PRINT_NUMBER(a);
        printf(" * ");
        PRINT_NUMBER(b);
        printf(" = ");
        PRINT_NUMBER(result);
        printf("\n");
    #endif

    #ifdef DIVISION
        DEBUG("Performing division");
        if (b != 0) {
            result = DO_DIVISION(a, b);
            printf("Division: ");
            PRINT_NUMBER(a);
            printf(" / ");
            PRINT_NUMBER(b);
            printf(" = ");
            PRINT_NUMBER(result);
            printf("\n");
        } else {
            printf("Division: Cannot divide by zero!\n");
        }
    #endif

    DEBUG("Program completed successfully");
    return 0;
}