#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
=====================================================
ERROS SUTIS QUE O COMPILADOR NÃO DETECTA
MAS O VALGRIND SIM!
=====================================================

Esta versão contém erros que passam pelo compilador
mas são detectados pelo Valgrind em tempo de execução.
*/

/*
=====================================================
1. INVALID READ/WRITE - VERSÃO SUTIL
=====================================================
*/

void exemplo_invalid_read_write_sutil() {
    printf("\n=== 1. INVALID READ/WRITE (SUTIL) ===\n");
    
    // CASO 1: Overflow baseado em entrada do usuário
    printf("CASO 1: Buffer Overflow Dinâmico\n");
    char *buffer = malloc(10);
    char *input = "Texto grande";  // Simulando entrada do usuário
    
    // O compilador não consegue detectar este overflow
    // porque depende de valores em runtime
    for (int i = 0; input[i] != '\0'; i++) {
        buffer[i] = input[i];  // ❌ OVERFLOW após índice 9
    }
    buffer[9] = '\0';  // Tentativa de null terminator
    printf("Buffer: %s\n", buffer);
    
    // CASO 2: Array bounds via ponteiro
    printf("CASO 2: Out of Bounds via Ponteiro\n");
    int *array = malloc(5 * sizeof(int));
    int *ptr = array;
    
    // Inicializar normalmente
    for (int i = 0; i < 5; i++) {
        array[i] = i * 10;
    }
    
    // Erro sutil: acessar além dos limites
    ptr += 10;  // Aponta 10 posições à frente
    *ptr = 999;  // ❌ INVALID WRITE bem longe do array
    
    printf("Tentativa de acesso inválido realizada\n");
    
    free(buffer);
    free(array);
}

/*
=====================================================
2. USE AFTER FREE - VERSÃO SUTIL
=====================================================
*/

char* funcao_que_retorna_ponteiro() {
    char *local_ptr = malloc(20);
    strcpy(local_ptr, "Dados temporários");
    free(local_ptr);  // ❌ Libera mas ainda retorna o ponteiro
    return local_ptr;  // ❌ Retorna ponteiro inválido
}

void exemplo_use_after_free_sutil() {
    printf("\n=== 2. USE AFTER FREE (SUTIL) ===\n");
    
    // CASO 1: Ponteiro retornado após free
    printf("CASO 1: Ponteiro de Função\n");
    char *dados = funcao_que_retorna_ponteiro();
    printf("Dados: %s\n", dados);  // ❌ USE AFTER FREE
    
    // CASO 2: Array de ponteiros com um elemento liberado
    printf("CASO 2: Array de Ponteiros\n");
    char **lista = malloc(3 * sizeof(char*));
    lista[0] = malloc(10); strcpy(lista[0], "Item 1");
    lista[1] = malloc(10); strcpy(lista[1], "Item 2");
    lista[2] = malloc(10); strcpy(lista[2], "Item 3");
    
    // Liberar apenas um item
    free(lista[1]);
    
    // Depois tentar usar todos
    for (int i = 0; i < 3; i++) {
        printf("lista[%d]: %s\n", i, lista[i]);  // ❌ i=1 é use after free
    }
    
    // Limpar o resto
    free(lista[0]);
    free(lista[2]);
    free(lista);
}

/*
=====================================================
3. UNINITIALIZED VALUES - VERSÃO SUTIL
=====================================================
*/

int calcular_media(int *numeros, int tamanho) {
    int soma = 0;
    
    // ❌ numeros pode conter lixo se não foi inicializado
    for (int i = 0; i < tamanho; i++) {
        soma += numeros[i];  // ❌ UNINITIALIZED VALUE
    }
    
    return soma / tamanho;
}

void exemplo_uninitialized_sutil() {
    printf("\n=== 3. UNINITIALIZED VALUES (SUTIL) ===\n");
    
    // CASO 1: Array malloc sem inicialização
    printf("CASO 1: Cálculo com Lixo\n");
    int *numeros = malloc(5 * sizeof(int));
    
    // Inicializar apenas alguns elementos
    numeros[0] = 10;
    numeros[2] = 30;
    // numeros[1], numeros[3], numeros[4] ficam com lixo
    
    int media = calcular_media(numeros, 5);  // ❌ Usa valores não inicializados
    printf("Média calculada: %d\n", media);
    
    // CASO 2: Struct com campos parcialmente inicializados
    printf("CASO 2: Struct Parcial\n");
    typedef struct {
        int id;
        char nome[20];
        float salario;
        int ativo;  // ❌ Este campo não será inicializado
    } Funcionario;
    
    Funcionario *func = malloc(sizeof(Funcionario));
    func->id = 123;
    strcpy(func->nome, "João");
    func->salario = 5000.0;
    // func->ativo não inicializado
    
    if (func->ativo) {  // ❌ CONDITIONAL JUMP com valor não inicializado
        printf("Funcionário %s está ativo\n", func->nome);
    } else {
        printf("Funcionário %s está inativo\n", func->nome);
    }
    
    free(numeros);
    free(func);
}

/*
=====================================================
4. MEMORY LEAKS SUTIS
=====================================================
*/

void exemplo_leaks_sutis() {
    printf("\n=== 4. MEMORY LEAKS SUTIS ===\n");
    
    // CASO 1: Leak em estrutura complexa
    printf("CASO 1: Estrutura Aninhada\n");
    typedef struct {
        char *nome;
        int *notas;
        char **materias;
    } Estudante;
    
    Estudante *est = malloc(sizeof(Estudante));
    est->nome = malloc(30);
    strcpy(est->nome, "Maria");
    
    est->notas = malloc(3 * sizeof(int));
    est->notas[0] = 85; est->notas[1] = 90; est->notas[2] = 78;
    
    est->materias = malloc(3 * sizeof(char*));
    est->materias[0] = malloc(20); strcpy(est->materias[0], "Matemática");
    est->materias[1] = malloc(20); strcpy(est->materias[1], "Física");
    est->materias[2] = malloc(20); strcpy(est->materias[2], "Química");
    
    printf("Estudante: %s\n", est->nome);
    printf("Primeira nota: %d\n", est->notas[0]);
    printf("Primeira matéria: %s\n", est->materias[0]);
    
    // ❌ VAZAMENTO: Libera só a estrutura principal
    // Esquece de liberar campos internos
    free(est);  // ❌ Leak de nome, notas, materias e strings das matérias
    
    // CASO 2: Leak em caso de erro
    printf("CASO 2: Leak em Error Path\n");
    char *buffer1 = malloc(100);
    char *buffer2 = malloc(200);
    char *buffer3 = malloc(300);
    
    // Simular erro na metade do processo
    int erro_simulado = 1;
    
    if (erro_simulado) {
        printf("Erro simulado - saindo da função\n");
        free(buffer1);  // ✅ Libera apenas o primeiro
        return;         // ❌ LEAK: buffer2 e buffer3 não liberados
    }
    
    // Código nunca executado devido ao erro
    free(buffer1);
    free(buffer2);
    free(buffer3);
}

/*
=====================================================
5. CONDITIONAL JUMPS SUTIS
=====================================================
*/

void exemplo_conditional_jumps_sutis() {
    printf("\n=== 5. CONDITIONAL JUMPS SUTIS ===\n");
    
    // CASO 1: Estrutura com padding não inicializado
    printf("CASO 1: Struct Padding\n");
    typedef struct {
        char flag;      // 1 byte
        // 3 bytes de padding aqui (não inicializados)
        int valor;      // 4 bytes
    } Dados;
    
    Dados *dados = malloc(sizeof(Dados));
    dados->flag = 1;
    dados->valor = 42;
    
    // Comparar toda a estrutura (incluindo padding não inicializado)
    Dados *outros_dados = malloc(sizeof(Dados));
    outros_dados->flag = 1;
    outros_dados->valor = 42;
    
    // ❌ CONDITIONAL baseado em padding não inicializado
    if (memcmp(dados, outros_dados, sizeof(Dados)) == 0) {
        printf("Estruturas são iguais\n");
    } else {
        printf("Estruturas são diferentes\n");
    }
    
    free(dados);
    free(outros_dados);
}

/*
=====================================================
MAIN
=====================================================
*/

int main() {
    printf("ERROS SUTIS QUE O COMPILADOR NÃO DETECTA\n");
    printf("========================================\n");
    printf("✅ Compila sem warnings\n");
    printf("❌ Mas tem muitos bugs detectáveis pelo Valgrind!\n\n");
    
    printf("🔍 Execute com:\n");
    printf("valgrind --leak-check=full --track-origins=yes ./programa\n\n");
    
    exemplo_invalid_read_write_sutil();
    exemplo_use_after_free_sutil();
    exemplo_uninitialized_sutil();
    exemplo_leaks_sutis();
    exemplo_conditional_jumps_sutis();
    
    printf("\n🎯 MISSÃO CUMPRIDA:\n");
    printf("• Código compila limpo ✅\n");
    printf("• Mas está cheio de bugs ❌\n");
    printf("• Só o Valgrind consegue detectar! 🔍\n");
    
    return 0;
}