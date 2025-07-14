/*
    C Programming Fundamentals
    Exercise 1: Variable Declaration and Initialization
    Objective: Practice variable declaration and naming conventions

    Declare the following variables with appropriate names and initial values:
    The age of a person (23 years)
    The salary of an employee (R$ 3500.50)
    The number of products in stock (150 units)
    Whether a customer is premium or not (true)

    Write a program that declares these variables and prints their values.
*/

#include <stdio.h>
#include <stdbool.h>

int main() {
    // Declaration and Initialization of Variables
    int age = 23;
    float salary = 3500.50;
    int stockQuantity = 150;
    bool isPremiumClient = true;

    // Print values
    printf("Age: %d years old\n", age);
    printf("Salary: R$ %.2f\n", salary);
    printf("Stock Quantity: %d units\n", stockQuantity);
    printf("Is Premium Client: %s\n", isPremiumClient ? "Yes" : "No");

    return 0;
}