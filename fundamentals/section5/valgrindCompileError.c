#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
=====================================================
TODOS OS TIPOS DE ERROS QUE O VALGRIND DETECTA
=====================================================

COMANDO COMPLETO:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./programa

FLAGS ÚTEIS:
--leak-check=full        → Mostra todos os vazamentos
--show-leak-kinds=all    → Mostra todos os tipos de vazamento
--track-origins=yes      → Rastreia origem de valores não inicializados
--show-reachable=yes     → Mostra memória ainda acessível
*/

/*
=====================================================
1. INVALID READ/WRITE - ACESSO INVÁLIDO À MEMÓRIA
=====================================================
Detecta quando você acessa memória que não deveria
*/

void exemplo_invalid_read_write() {
    printf("\n=== 1. INVALID READ/WRITE ===\n");
    
    // CASO 1: Buffer overflow
    printf("CASO 1: Buffer Overflow\n");
    char *buffer = malloc(10);
    strcpy(buffer, "Este texto é muito grande para 10 bytes!");  // ❌ OVERFLOW
    printf("Buffer: %s\n", buffer);
    
    // CASO 2: Array out of bounds
    printf("CASO 2: Array Out of Bounds\n");
    int *array = malloc(5 * sizeof(int));
    array[10] = 42;  // ❌ INVALID WRITE: índice 10 em array de 5
    printf("array[10] = %d\n", array[10]);  // ❌ INVALID READ
    
    // CASO 3: Use after free (você já viu!)
    printf("CASO 3: Use After Free\n");
    free(buffer);
    printf("Buffer após free: %c\n", buffer[0]);  // ❌ INVALID READ
    
    free(array);
}

/*
=====================================================
Erro de compilação: buffer overflow
=====================================================
gcc -o valgrindCompileError.out valgrindCompileError.c -g
valgrindCompileError.c: In function ‘exemplo_invalid_read_write’:
valgrindCompileError.c:33:5: warning: ‘__builtin_memcpy’ writing 42 bytes into a region of size 10 overflows the destination [-Wstringop-overflow=]
   33 |     strcpy(buffer, "Este texto é muito grande para 10 bytes!");  // ❌ OVERFLOW
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
valgrindCompileError.c:32:20: note: destination object of size 10 allocated by ‘malloc’
   32 |     char *buffer = malloc(10);
      |                    ^~~~~~~~~~
*/