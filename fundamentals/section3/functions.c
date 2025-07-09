#include <stdio.h>

int add_two_numbers(int x, int y) {
    int z = x + y;
    return z;
}

int main() {
    int a = 5;
    int b = 10;
    int result = add_two_numbers(a, b);
    printf("The sum of %d and %d is %d\n", a, b, result);
    return 0;
}