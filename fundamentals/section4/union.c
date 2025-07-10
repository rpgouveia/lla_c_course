#include <stdio.h>

/*
A union is similar to a struct in that it can store members of different data types.

However, there are some differences:

In a struct, each member has its own memory.
In a union, all members share the same memory, which means you can only use one of the values at a time.

Good application for unions is when you need to store different types of data in the same memory location, 
but you only need to use one type at a time.

This can save memory space, especially when dealing with large data types.
Unions are often used in low-level programming, such as embedded systems or operating systems, where memory efficiency is crucial.
*/

union myUnion
{
    int myNum;
    char myLetter;
    char myString[30];
};

int main()
{
    union myUnion u1;

    u1.myNum = 1000;

    // Since this is the last value written to the union, myNum no longer holds 1000 - its value is now invalid
    u1.myLetter = 'A';

    printf("myNum: %d\n", u1.myNum);       // This value is no longer reliable
    printf("myLetter: %c\n", u1.myLetter); // Prints 'A'

    return 0;
}

/* Output:
myNum: 833
myLetter: A
*/