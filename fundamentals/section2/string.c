# include <stdio.h>

int main() {
    // This is a string in C
    // A string is just an array of characters
    // Example of security vulnerability
    // char my_str[] = {'h', 'e', 'l', 'l', 'o'}; 
    
    // The string is null terminated, meaning it ends with a zero byte
    // This is important for functions that operate on strings, like printf
    char my_str[] = {'h', 'e', 'l', 'l', 'o', 0}; // Null terminated string
    printf("%s\n", my_str);
    return 0;
}
