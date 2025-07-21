/*
=====================================================
EXERCÍCIOS DE VAZAMENTO DE MEMÓRIA COM VALGRIND
=====================================================

INSTRUÇÕES:
1. Compile cada exercício com: gcc -o exercicioX exercicioX.c -g
2. Execute com Valgrind: valgrind --leak-check=full ./exercicioX
3. Identifique e corrija os vazamentos de memória
4. Execute novamente para verificar se corrigiu

Dica: Valgrind mostra exatamente onde a memória foi alocada mas não liberada!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
=====================================================
EXERCÍCIO 1 - VAZAMENTO BÁSICO
=====================================================
PROBLEMA: Este código tem vazamentos de memória óbvios.
TAREFA: Execute com Valgrind, identifique e corrija TODOS os vazamentos.

Como testar:
gcc -o exercicio1 exercicio1.c -g
valgrind --leak-check=full ./exercicio1
*/

void exercicio1_com_vazamento() {
    printf("\n=== EXERCÍCIO 1: VAZAMENTO BÁSICO ===\n");
    
    // Vazamento 1: String simples
    char *nome = malloc(50 * sizeof(char));
    strcpy(nome, "João Silva");
    printf("Nome: %s\n", nome);
    // ❌ BUG: Faltou free(nome)
    
    // Vazamento 2: Array de inteiros
    int *numeros = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        numeros[i] = i * 10;
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }
    // ❌ BUG: Faltou free(numeros)
    
    // Vazamento 3: Buffer grande
    char *buffer = malloc(1000 * sizeof(char));
    strcpy(buffer, "Este é um buffer grande que não será liberado!");
    printf("Buffer: %.50s...\n", buffer);
    // ❌ BUG: Faltou free(buffer)
    
    // Correção: liberar memória alocada
    free(nome);
    free(numeros);
    free(buffer);
    printf("Função finalizada (com vazamentos!)\n");
}

/*
=====================================================
EXERCÍCIO 2 - VAZAMENTO EM LOOP
=====================================================
PROBLEMA: Este código tem vazamento dentro de um loop.
TAREFA: Execute com Valgrind e corrija o vazamento multiplicado.

Como testar:
gcc -o exercicio2 exercicio2.c -g
valgrind --leak-check=full ./exercicio2
*/

void exercicio2_loop_vazamento() {
    printf("\n=== EXERCÍCIO 2: VAZAMENTO EM LOOP ===\n");
    
    for (int i = 0; i < 3; i++) {
        printf("\n--- Iteração %d ---\n", i + 1);
        
        // Alocar memória para nome
        char *nome_pessoa = malloc(30 * sizeof(char));
        snprintf(nome_pessoa, 30, "Pessoa_%d", i + 1);
        printf("Criando: %s\n", nome_pessoa);
        
        // Alocar memória para dados
        int *dados = malloc(10 * sizeof(int));
        for (int j = 0; j < 10; j++) {
            dados[j] = i * 10 + j;
        }
        printf("Primeiro dado: %d, Último dado: %d\n", dados[0], dados[9]);
        
        // ❌ BUG: Memória alocada 3 vezes, mas nunca liberada!
        // ❌ Tanto nome_pessoa quanto dados vazam em cada iteração

        // Correção: liberar memória alocada dentro do loop
        free(nome_pessoa);
        free(dados);
    }
    
    printf("Loop finalizado (com 6 vazamentos!)\n");
}

/*
=====================================================
EXERCÍCIO 3 - VAZAMENTO PARCIAL (MAIS DIFÍCIL)
=====================================================
PROBLEMA: Este código libera PARTE da memória, mas não toda.
TAREFA: Execute com Valgrind e identifique vazamentos sutis.

Como testar:
gcc -o exercicio3 exercicio3.c -g
valgrind --leak-check=full ./exercicio3
*/

typedef struct {
    char *nome;
    int *notas;
    int num_notas;
} Estudante;

void exercicio3_vazamento_parcial() {
    printf("\n=== EXERCÍCIO 3: VAZAMENTO PARCIAL ===\n");
    
    // Criar array de estudantes
    Estudante *estudantes = malloc(2 * sizeof(Estudante));
    
    // Estudante 1
    estudantes[0].nome = malloc(20 * sizeof(char));
    strcpy(estudantes[0].nome, "Maria");
    estudantes[0].num_notas = 3;
    estudantes[0].notas = malloc(3 * sizeof(int));
    estudantes[0].notas[0] = 85;
    estudantes[0].notas[1] = 90;
    estudantes[0].notas[2] = 78;
    
    // Estudante 2
    estudantes[1].nome = malloc(20 * sizeof(char));
    strcpy(estudantes[1].nome, "Pedro");
    estudantes[1].num_notas = 2;
    estudantes[1].notas = malloc(2 * sizeof(int));
    estudantes[1].notas[0] = 92;
    estudantes[1].notas[1] = 88;
    
    // Exibir dados
    for (int i = 0; i < 2; i++) {
        printf("Estudante: %s\n", estudantes[i].nome);
        printf("Notas: ");
        for (int j = 0; j < estudantes[i].num_notas; j++) {
            printf("%d ", estudantes[i].notas[j]);
        }
        printf("\n");
    }
    
    // Limpeza INCOMPLETA
    // free(estudantes[0].nome);        // ✅ Libera nome do estudante 1
    // ❌ BUG: Não libera estudantes[0].notas
    // ❌ BUG: Não libera nada do estudante 2!
    // free(estudantes);                // ✅ Libera array principal
    // ❌ BUG: Mas ainda tem vazamentos internos!
    // printf("Limpeza 'completa' (mas com vazamentos sutis!)\n");
    
    // Correção: liberar tudo corretamente
    free(estudantes[0].nome);        // ✅ Libera nome do estudante 1
    free(estudantes[0].notas);       // ✅ Libera notas do estudante 1
    free(estudantes[1].nome);        // ✅ Libera nome do estudante 2
    free(estudantes[1].notas);       // ✅ Libera notas do estudante 2
    free(estudantes);                // ✅ Libera array principal
    printf("Limpeza completa!\n");
}

/*
=====================================================
MAIN E INSTRUÇÕES
=====================================================
*/

int main() {
    printf("EXERCÍCIOS DE DETECÇÃO DE VAZAMENTO DE MEMÓRIA\n");
    printf("==============================================\n");
    printf("\nINSTRUÇÕES:\n");
    printf("1. Compile: gcc -o programa programa.c -g\n");
    printf("2. Execute: valgrind --leak-check=full ./programa\n");
    printf("3. Analise o relatório do Valgrind\n");
    printf("4. Corrija os vazamentos adicionando free()\n");
    printf("5. Execute novamente até não ter vazamentos\n");
    
    // Execute todos os exercícios
    exercicio1_com_vazamento(); // Corrigido!
    exercicio2_loop_vazamento(); // Corrigido!
    exercicio3_vazamento_parcial(); // Corrigido!
    
    printf("\n=== EXECUTE COM VALGRIND PARA VER OS VAZAMENTOS! ===\n");
    printf("Comando: valgrind --leak-check=full ./programa\n");
    
    return 0;
}

