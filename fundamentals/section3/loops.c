#include <stdio.h>

int main() {
    printf("Using a for loop:\n");
    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {
            printf("%d\n", i);
        }
    }

    // pressing Enter to continue
    printf("\nPress Enter to continue...\n");
    getchar();

    printf("\nUsing a while loop:\n");
    int j = 0;
    while (j < 1000) {
        if (j % 2 == 0) {
            printf("%d\n", j);
        }
        j++;
    }

    // pressing Enter to continue
    printf("\nPress Enter to continue...\n");
    getchar();

    printf("\nUsing a do-while loop:\n");
    int k = 0;
    do {
        if (k % 2 == 0) {
            printf("%d\n", k);
        }
        k++;
    } while (k < 1000); 

    return 0;
}