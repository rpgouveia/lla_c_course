#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
=====================================================
EXERCÍCIO 1 - BÁSICO: Alocar e Inicializar
=====================================================
Complete a função para:
1. Alocar memória para um inteiro
2. Armazenar o valor 42 na memória alocada
3. Fazer o ponteiro original apontar para essa memória
*/

int exercicio1(int **ptr) {
    // TODO: Seu código aqui
    *ptr = (int *)malloc(sizeof(int));
    if (*ptr == NULL) return -1;
    **ptr = 42;
    return 0;
}

void teste_exercicio1() {
    printf("\n=== EXERCÍCIO 1 ===\n");
    int *meu_ptr = NULL;
    
    if (exercicio1(&meu_ptr) == 0) {
        printf("Valor: %d (esperado: 42)\n", *meu_ptr);
        free(meu_ptr);
    }
}

/*
=====================================================
EXERCÍCIO 2 - ARRAY: Alocar Array de Inteiros
=====================================================
Complete a função para:
1. Alocar memória para um array de 5 inteiros
2. Inicializar com valores: 10, 20, 30, 40, 50
3. Fazer o ponteiro original apontar para o array
*/

int exercicio2(int **arr, int size) {
    // TODO: Seu código aqui
    *arr = (int *)malloc(size * sizeof(int));
    if (*arr == NULL) return -1;
    for (int i = 0; i < size; i++) {
        (*arr)[i] = (i + 1) * 10;
    }
    return 0;
}

void teste_exercicio2() {
    printf("\n=== EXERCÍCIO 2 ===\n");
    int *meu_array = NULL;
    
    if (exercicio2(&meu_array, 5) == 0) {
        printf("Array: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", meu_array[i]);
        }
        printf("\n");
        free(meu_array);
    }
}

/*
=====================================================
EXERCÍCIO 3 - STRING: Copiar String
=====================================================
Complete a função para:
1. Alocar memória para uma cópia da string recebida
2. Copiar o conteúdo da string original
3. Fazer o ponteiro original apontar para a nova string
*/

int exercicio3(char **destino, const char *origem) {
    // TODO: Seu código aqui
    int length = strlen(origem);
    *destino = (char *)malloc((length + 1) * sizeof(char)); // +1 para o terminador nulo
    if (*destino == NULL) return -1;
    strcpy(*destino, origem);
    return 0;
}

void teste_exercicio3() {
    printf("\n=== EXERCÍCIO 3 ===\n");
    char *nova_string = NULL;
    
    if (exercicio3(&nova_string, "Olá, mundo!") == 0) {
        printf("String copiada: %s\n", nova_string);
        free(nova_string);
    }
}

/*
=====================================================
EXERCÍCIO 4 - REDIMENSIONAR: Realocação
=====================================================
Complete a função para:
1. Receber um array já alocado
2. Redimensionar para novo tamanho
3. Inicializar novos elementos com valor padrão
4. Atualizar o ponteiro original
*/

int exercicio4(int **arr, int tamanho_atual, int novo_tamanho, int valor_padrao) {
    // TODO: Seu código aqui
    *arr = (int *)realloc(*arr, novo_tamanho * sizeof(int));
    if (*arr == NULL) return -1;
    // Inicializar novos elementos com valor padrão
    for (int i = tamanho_atual; i < novo_tamanho; i++) {
        (*arr)[i] = valor_padrao;
    }
    return 0;
}

void teste_exercicio4() {
    printf("\n=== EXERCÍCIO 4 ===\n");
    
    // Criar array inicial
    int *meu_array = malloc(3 * sizeof(int));
    meu_array[0] = 1;
    meu_array[1] = 2;
    meu_array[2] = 3;
    
    // Redimensionar
    if (exercicio4(&meu_array, 3, 6, 99) == 0) {
        printf("Array redimensionado: ");
        for (int i = 0; i < 6; i++) {
            printf("%d ", meu_array[i]);
        }
        printf("\n");
        free(meu_array);
    }
}

/*
=====================================================
EXERCÍCIO 5 - AVANÇADO: Lista de Strings
=====================================================
Complete a função para:
1. Alocar um array de ponteiros para string
2. Para cada string no array de entrada, alocar e copiar
3. Fazer o ponteiro original apontar para o array de strings
*/

int exercicio5(char ***lista_destino, char *strings_origem[], int quantidade) {
    // TODO: Seu código aqui
    // Alocar array de ponteiros
    *lista_destino = (char **)malloc(quantidade * sizeof(char *));
    if (*lista_destino == NULL) return -1;
    
    // Alocar e copiar cada string
    for (int i = 0; i < quantidade; i++) {
        int len = strlen(strings_origem[i]);
        (*lista_destino)[i] = (char *)malloc((len + 1) * sizeof(char));
        if ((*lista_destino)[i] == NULL) return -1;
        strcpy((*lista_destino)[i], strings_origem[i]);
    }
    return 0;
}

void teste_exercicio5() {
    printf("\n=== EXERCÍCIO 5 ===\n");
    char *nomes[] = {"Ana", "Bruno", "Carlos"};
    char **lista_copiada = NULL;
    
    if (exercicio5(&lista_copiada, nomes, 3) == 0) {
        printf("Lista de nomes copiada:\n");
        for (int i = 0; i < 3; i++) {
            printf("  %d: %s\n", i + 1, lista_copiada[i]);
            free(lista_copiada[i]); // Liberar cada string
        }
        free(lista_copiada); // Liberar array de ponteiros
    }
}

/*
=====================================================
FUNÇÃO MAIN E GABARITO
=====================================================
*/

int main() {
    printf("EXERCÍCIOS DE PONTEIROS DUPLOS\n");
    printf("===============================\n");
    
    teste_exercicio1();
    teste_exercicio2();
    teste_exercicio3();
    teste_exercicio4();
    teste_exercicio5();
    
    return 0;
}