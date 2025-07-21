#include <stdio.h>
#include <stdlib.h>

/**
Correct this code to update the value in the heap 
to 10 before giving the address to main
**/

int foo(int **ptr) {
    int value = 10;
    *ptr = (int *)malloc(sizeof(int));  // CORREÇÃO: usar *ptr ao invés de ptr

    if (*ptr == NULL) {                 // CORREÇÃO: verificar *ptr ao invés de ptr
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    **ptr = value; 
    return 0;
}


int main() {
    int *my_ptr = NULL;
    
    if (foo(&my_ptr) == 0) {
        printf("Valor no heap: %d\n", *my_ptr);
        printf("Endereço: %p\n", (void*)my_ptr);
        
        // Libera a memória alocada
        free(my_ptr);
    }
    
    return 0;
}