#include <stdio.h>

// This program swaps two integers using pointers
// It reads two integers from standard input and prints them in swapped order to standard output.   
// Inputs = stdin [50,100]
// Output = stdout [100,50]

int swap( int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}

int main() {
    int x, y;
    
    printf("Enter two integers: ");
    // Read two integers from standard input safely
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        sscanf(buffer, "%d %d", &x, &y);
    }
    
    // Swap the integers using pointers
    swap(&x, &y);
    
    // Print the swapped integers to standard output
    printf("%d %d\n", x, y);
    
    return 0;
}