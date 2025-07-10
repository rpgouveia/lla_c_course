#include <stdio.h>

/*
 *  Finish the employee struct. Create a character buffer to store the employees name and a variable for his age.
 *  Create an employee named "Steve", 42 years.
 */

struct Employee {
    char name[50];
    int age;
};


int main(int argc, char **argv) {

    struct Employee emp = {"Steve", 42};

    printf("%s, aged %d years\n", emp.name, emp.age);

    return 0;

}