#include <stdio.h>
#include <stdlib.h>
#include <errno.h>      
#include <string.h>     
#include <fcntl.h>      
#include <unistd.h>     
#include <sys/stat.h>   
#include <dirent.h>     
#include <stdint.h>     
#include <limits.h>     

/*
=====================================================
FUNÇÕES AUXILIARES PARA TRATAMENTO DE ERROS
=====================================================
Reutilizáveis em todos os exercícios
*/

// ✅ Função auxiliar para tratamento padronizado de erro
void handle_file_error(const char *operation, const char *filename) {
    int saved_errno = errno;
    
    // Mensagem básica com perror
    perror(operation);
    
    // Detalhes específicos com strerror
    printf("Detalhes: %s\n", strerror(saved_errno));
    
    // Análise específica do erro
    switch (saved_errno) {
        case ENOENT:
            printf("Diagnóstico: Arquivo/diretório '%s' não encontrado\n", filename);
            break;
        case EACCES:
            printf("Diagnóstico: Permissão negada para '%s'\n", filename);
            break;
        case EEXIST:
            printf("Diagnóstico: '%s' já existe\n", filename);
            break;
        case EISDIR:
            printf("Diagnóstico: '%s' é um diretório\n", filename);
            break;
        case ENOTDIR:
            printf("Diagnóstico: Componente do caminho '%s' não é diretório\n", filename);
            break;
        default:
            printf("Diagnóstico: Erro %d (%s) em '%s'\n", saved_errno, strerror(saved_errno), filename);
    }
}

// ✅ Função auxiliar para testar abertura de arquivo
int test_file_operation(const char *filename, int flags, mode_t mode, const char *operation_desc) {
    printf("\n🔍 Testando: %s\n", operation_desc);
    printf("Arquivo: %s\n", filename);
    
    int fd = open(filename, flags, mode);
    if (fd == -1) {
        handle_file_error("Erro na operação", filename);
        return -1;
    } else {
        printf("✅ Sucesso: Arquivo aberto com fd=%d\n", fd);
        close(fd);
        return 0;
    }
}

// ✅ Função auxiliar para testar operações de diretório
int test_directory_operation(const char *dirname, const char *operation_desc) {
    printf("\n🔍 Testando: %s\n", operation_desc);
    printf("Diretório: %s\n", dirname);
    
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        handle_file_error("Erro ao abrir diretório", dirname);
        return -1;
    } else {
        printf("✅ Sucesso: Diretório aberto\n");
        closedir(dir);
        return 0;
    }
}

// ✅ Função auxiliar para criar arquivo protegido
int create_protected_file(const char *filename) {
    printf("Criando arquivo protegido: %s\n", filename);
    
    int fd = open(filename, O_CREAT | O_WRONLY, 0000);  // Sem permissões
    if (fd == -1) {
        handle_file_error("Erro ao criar arquivo protegido", filename);
        return -1;
    }
    
    close(fd);
    printf("✅ Arquivo protegido criado\n");
    return 0;
}

// ✅ Função auxiliar para análise de malloc
void analyze_malloc_result(void *ptr, size_t size) {
    if (ptr == NULL) {
        int saved_errno = errno;
        
        printf("❌ malloc() falhou ao alocar %zu bytes\n", size);
        printf("errno atual: %d (%s)\n", saved_errno, strerror(saved_errno));
        
        // Análise específica
        if (saved_errno == ENOMEM) {
            printf("Diagnóstico: Memória insuficiente (ENOMEM)\n");
        } else if (saved_errno == 0) {
            printf("Diagnóstico: malloc() falhou mas não definiu errno\n");
            printf("Nota: Comportamento dependente da implementação\n");
        } else {
            printf("Diagnóstico: Erro inesperado %d\n", saved_errno);
        }
        
        printf("📚 Lição: malloc() nem sempre define errno!\n");
        printf("   Sempre verifique o retorno (ptr == NULL) primeiro\n");
    } else {
        printf("✅ malloc() sucedeu: alocou %zu bytes em %p\n", size, ptr);
        free(ptr);
    }
}

// ✅ Função auxiliar para análise de system()
void analyze_system_result(const char *command, int result) {
    printf("\n🔍 Analisando comando: %s\n", command);
    printf("Retorno: %d\n", result);
    
    if (result == -1) {
        int saved_errno = errno;
        printf("❌ system() falhou na execução\n");
        printf("errno: %d (%s)\n", saved_errno, strerror(saved_errno));
        
        if (saved_errno == ENOENT) {
            printf("Diagnóstico: Shell ou comando não encontrado\n");
        } else {
            printf("Diagnóstico: Erro de sistema na execução\n");
        }
    } else {
        printf("✅ system() executou o comando\n");
        
        if (WIFEXITED(result)) {
            int exit_status = WEXITSTATUS(result);
            printf("Status de saída: %d\n", exit_status);
            
            if (exit_status == 0) {
                printf("Diagnóstico: Comando executado com sucesso\n");
            } else {
                printf("Diagnóstico: Comando executado mas falhou (exit=%d)\n", exit_status);
            }
        } else {
            printf("Diagnóstico: Comando terminou anormalmente\n");
        }
    }
}

/*
=====================================================
EXERCÍCIO 1 MELHORADO - MANIPULAÇÃO DE ARQUIVOS
=====================================================
*/

void exercicio1_arquivos_melhorado() {
    printf("\n=== EXERCÍCIO 1 MELHORADO: MANIPULAÇÃO DE ARQUIVOS ===\n");
    printf("Usando funções auxiliares para tratamento padronizado\n");
    
    // 1.1 - Arquivo inexistente
    test_file_operation("arquivo_que_nao_existe.txt", O_RDONLY, 0, 
                       "Abertura de arquivo inexistente");
    
    // 1.2 - Arquivo sem permissão
    if (create_protected_file("arquivo_protegido.txt") == 0) {
        test_file_operation("arquivo_protegido.txt", O_RDWR, 0, 
                           "Abertura de arquivo protegido para leitura/escrita");
    }
    
    // 1.3 - Diretório que já existe
    printf("\n🔍 Testando: Criação de diretório existente\n");
    mkdir("test_dir", 0755);  // Criar primeiro
    
    if (mkdir("test_dir", 0755) == -1) {
        handle_file_error("Tentativa de criar diretório existente", "test_dir");
    } else {
        printf("✅ Inesperado: Diretório foi criado novamente\n");
    }
    
    // 1.4 - Diretório inexistente
    test_directory_operation("diretorio_inexistente", 
                            "Abertura de diretório inexistente");
    
    // Limpeza com verificação
    printf("\n🧹 Limpeza:\n");
    if (unlink("arquivo_protegido.txt") == 0) {
        printf("✅ Arquivo protegido removido\n");
    }
    if (rmdir("test_dir") == 0) {
        printf("✅ Diretório de teste removido\n");
    }
}

/*
=====================================================
EXERCÍCIO 2 MELHORADO - MEMÓRIA E SISTEMA
=====================================================
*/

void exercicio2_memoria_sistema_melhorado() {
    printf("\n=== EXERCÍCIO 2 MELHORADO: MEMÓRIA E SISTEMA ===\n");
    
    // 2.1 - Análise detalhada do malloc()
    printf("\n📊 Seção 2.1: Análise do malloc()\n");
    printf("═══════════════════════════════════\n");
    
    // Teste 1: Alocação normal
    printf("\nTeste 1: Alocação normal (100 bytes)\n");
    errno = 0;  // Limpar errno
    void *ptr_normal = malloc(100);
    analyze_malloc_result(ptr_normal, 100);
    
    // Teste 2: Alocação gigante
    printf("\nTeste 2: Alocação impossível\n");
    #ifdef SIZE_MAX
        size_t huge_size = SIZE_MAX;
    #else
        size_t huge_size = (size_t)-1;
    #endif
    
    errno = 0;  // Limpar errno antes do teste
    void *ptr_huge = malloc(huge_size);
    analyze_malloc_result(ptr_huge, huge_size);
    
    // 2.2 - Análise detalhada do system()
    printf("\n📊 Seção 2.2: Análise do system()\n");
    printf("══════════════════════════════════\n");
    
    // Teste 1: Comando válido que existe
    analyze_system_result("echo 'Teste de comando válido'", 
                         system("echo 'Teste de comando válido'"));
    
    // Teste 2: Comando válido que falha
    analyze_system_result("ls /diretorio_que_nao_existe 2>/dev/null", 
                         system("ls /diretorio_que_nao_existe 2>/dev/null"));
    
    // Teste 3: Comando completamente inválido
    analyze_system_result("comando_completamente_invalido_12345", 
                         system("comando_completamente_invalido_12345"));
    
    // 2.3 - Resumo das diferenças
    printf("\n📚 Seção 2.3: Resumo das Diferenças\n");
    printf("═══════════════════════════════════\n");
    
    printf("🔍 malloc() vs errno:\n");
    printf("• malloc() NEM SEMPRE define errno quando falha\n");
    printf("• Depende da implementação da biblioteca C\n");
    printf("• SEMPRE verifique ptr == NULL primeiro\n");
    printf("• errno é informação adicional, não definitiva\n\n");
    
    printf("🔍 system() vs errno:\n");
    printf("• system() define errno apenas para erros DE EXECUÇÃO\n");
    printf("• Código de retorno ≠ errno\n");
    printf("• -1 = erro ao executar (errno válido)\n");
    printf("• ≥0 = comando executado (status de saída)\n\n");
    
    printf("🎯 Lição principal:\n");
    printf("• Nem todas as funções usam errno da mesma forma\n");
    printf("• Sempre consulte a man page de cada função\n");
    printf("• Teste o comportamento no seu sistema específico\n");
}

/*
=====================================================
EXERCÍCIO 3 - SUA IMPLEMENTAÇÃO EXCELENTE
=====================================================
Mantendo sua implementação que já está perfeita!
*/

typedef enum {
    COPY_SUCCESS = 0,
    COPY_ERROR_SOURCE,      
    COPY_ERROR_DEST,        
    COPY_ERROR_READ,        
    COPY_ERROR_WRITE,       
    COPY_ERROR_CLOSE        
} CopyResult;

ssize_t write_all(int fd, const char *buffer, size_t count) {
    size_t total_written = 0;
    ssize_t bytes_written;
    
    while (total_written < count) {
        bytes_written = write(fd, buffer + total_written, count - total_written);
        if (bytes_written == -1) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        total_written += bytes_written;
    }
    
    return total_written;
}

void safe_close(int *fd) {
    if (*fd != -1) {
        if (close(*fd) == -1) {
            perror("Aviso: erro ao fechar arquivo");
        }
        *fd = -1;
    }
}

CopyResult copy_file_with_errno_handling(const char *source, const char *dest) {
    printf("\n=== EXERCÍCIO 3: CÓPIA ROBUSTA (SUA IMPLEMENTAÇÃO) ===\n");
    printf("Copiando %s para %s\n", source, dest);
    
    int source_fd = -1, dest_fd = -1;
    char buffer[1024];
    ssize_t bytes_read;
    CopyResult result = COPY_SUCCESS;
    
    if (!source || !dest) {
        printf("Erro: Parâmetros inválidos\n");
        return COPY_ERROR_SOURCE;
    }
    
    source_fd = open(source, O_RDONLY);
    if (source_fd == -1) {
        handle_file_error("Erro ao abrir arquivo origem", source);
        return COPY_ERROR_SOURCE;
    }
    
    dest_fd = open(dest, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (dest_fd == -1) {
        handle_file_error("Erro ao criar arquivo destino", dest);
        safe_close(&source_fd);
        return COPY_ERROR_DEST;
    }
    
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        if (write_all(dest_fd, buffer, bytes_read) == -1) {
            handle_file_error("Erro na escrita", dest);
            result = COPY_ERROR_WRITE;
            break;
        }
    }
    
    if (bytes_read == -1) {
        handle_file_error("Erro na leitura", source);
        if (result == COPY_SUCCESS) {
            result = COPY_ERROR_READ;
        }
    }
    
    safe_close(&source_fd);
    safe_close(&dest_fd);
    
    // Mostrar resultado
    const char *result_names[] = {
        "SUCESSO", "ERRO_ORIGEM", "ERRO_DESTINO", 
        "ERRO_LEITURA", "ERRO_ESCRITA", "ERRO_FECHAMENTO"
    };
    
    printf("Resultado da cópia: %s\n", result_names[result]);
    
    return result;
}

void exercicio3_copia_robusta_melhorado() {
    printf("\n=== EXERCÍCIO 3 MELHORADO: TESTES ABRANGENTES ===\n");
    
    // Criar arquivo de teste com conteúdo mais interessante
    printf("🔧 Preparando arquivos de teste...\n");
    int test_fd = open("teste_origem.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (test_fd != -1) {
        const char *content = "Este é um arquivo de teste\n"
                             "com múltiplas linhas\n"
                             "para testar a cópia robusta\n"
                             "incluindo caracteres especiais: áéíóú\n"
                             "e números: 12345\n";
        write(test_fd, content, strlen(content));
        close(test_fd);
        printf("✅ Arquivo de teste criado\n");
    }
    
    printf("\n📋 Executando bateria de testes:\n");
    
    // Teste 1: Cópia normal
    printf("\n🟢 Teste 1: Cópia normal\n");
    copy_file_with_errno_handling("teste_origem.txt", "teste_destino.txt");
    
    // Teste 2: Origem inexistente
    printf("\n🔴 Teste 2: Arquivo origem inexistente\n");
    copy_file_with_errno_handling("arquivo_inexistente.txt", "destino.txt");
    
    // Teste 3: Destino em local protegido
    printf("\n🔴 Teste 3: Destino em diretório protegido\n");
    mkdir("dir_protegido", 0000);
    copy_file_with_errno_handling("teste_origem.txt", "dir_protegido/destino.txt");
    
    // Teste 4: Origem sem permissão de leitura
    printf("\n🔴 Teste 4: Origem sem permissão de leitura\n");
    if (create_protected_file("origem_protegida.txt") == 0) {
        copy_file_with_errno_handling("origem_protegida.txt", "destino_normal.txt");
    }
    
    // Limpeza detalhada
    printf("\n🧹 Limpeza detalhada:\n");
    const char *files_to_remove[] = {
        "teste_origem.txt", "teste_destino.txt", "destino.txt", 
        "origem_protegida.txt", "destino_normal.txt", NULL
    };
    
    for (int i = 0; files_to_remove[i]; i++) {
        if (unlink(files_to_remove[i]) == 0) {
            printf("✅ Removido: %s\n", files_to_remove[i]);
        }
    }
    
    if (rmdir("dir_protegido") == 0) {
        printf("✅ Removido: dir_protegido\n");
    }
}

/*
=====================================================
DEMONSTRAÇÃO DE BOAS PRÁTICAS (MANTIDA)
=====================================================
*/

void demonstrar_boas_praticas() {
    printf("\n=== DEMONSTRAÇÃO: BOAS PRÁTICAS ===\n");
    
    printf("\n✅ BOA PRÁTICA 1: Funções auxiliares para tratamento\n");
    printf("• Código mais limpo e reutilizável\n");
    printf("• Tratamento padronizado de erros\n");
    printf("• Facilita manutenção e debugging\n");
    
    printf("\n✅ BOA PRÁTICA 2: Salvamento imediato de errno\n");
    int fd = open("arquivo_inexistente.txt", O_RDONLY);
    if (fd == -1) {
        int saved_errno = errno;
        printf("Erro detectado!\n");
        printf("Erro foi: %s\n", strerror(saved_errno));
    }
    
    printf("\n✅ BOA PRÁTICA 3: Verificação antes de errno\n");
    printf("• SEMPRE verifique valor de retorno primeiro\n");
    printf("• errno só é válido se função indicou erro\n");
    
    printf("\n✅ BOA PRÁTICA 4: Limpeza de recursos\n");
    printf("• Use funções auxiliares como safe_close()\n");
    printf("• Garanta cleanup mesmo em caso de erro\n");
    printf("• Evite vazamentos de file descriptors\n");
}

void mostrar_codigos_comuns() {
    printf("\n=== CÓDIGOS DE ERRO COMUNS ===\n\n");
    
    printf("📋 ERROS DE ARQUIVO:\n");
    printf("ENOENT (%d): %s\n", ENOENT, strerror(ENOENT));
    printf("EACCES (%d): %s\n", EACCES, strerror(EACCES));
    printf("EISDIR (%d): %s\n", EISDIR, strerror(EISDIR));
    printf("ENOTDIR (%d): %s\n", ENOTDIR, strerror(ENOTDIR));
    printf("EEXIST (%d): %s\n", EEXIST, strerror(EEXIST));
    
    printf("\n📋 ERROS DE MEMÓRIA:\n");
    printf("ENOMEM (%d): %s\n", ENOMEM, strerror(ENOMEM));
    
    printf("\n📋 ERROS DE E/O:\n");
    printf("EIO (%d): %s\n", EIO, strerror(EIO));
    printf("EPIPE (%d): %s\n", EPIPE, strerror(EPIPE));
    
    printf("\n📋 ERROS DE ARGUMENTOS:\n");
    printf("EINVAL (%d): %s\n", EINVAL, strerror(EINVAL));
    printf("ERANGE (%d): %s\n", ERANGE, strerror(ERANGE));
}

/*
=====================================================
MAIN MELHORADO
=====================================================
*/

int main() {
    printf("EXERCÍCIOS errno MELHORADOS COM FUNÇÕES AUXILIARES\n");
    printf("=================================================\n");
    
    printf("\n🎯 MELHORIAS IMPLEMENTADAS:\n");
    printf("✅ Funções auxiliares para tratamento padronizado\n");
    printf("✅ Análise detalhada de resultados\n");
    printf("✅ Menos código duplicado\n");
    printf("✅ Melhor didática e legibilidade\n");
    printf("✅ Testes mais abrangentes\n");
    
    demonstrar_boas_praticas();
    mostrar_codigos_comuns();
    
    exercicio1_arquivos_melhorado();
    exercicio2_memoria_sistema_melhorado();
    exercicio3_copia_robusta_melhorado();
    
    printf("\n🏆 RESUMO FINAL:\n");
    printf("✅ Dominiu conceitos fundamentais de errno\n");
    printf("✅ Implementou tratamento robusto de erros\n");
    printf("✅ Usou funções auxiliares para código limpo\n");
    printf("✅ Aplicou boas práticas de programação C\n");
    
    printf("\n📚 PRÓXIMOS ESTUDOS SUGERIDOS:\n");
    printf("• Programação de rede com errno\n");
    printf("• Multi-threading e errno thread-local\n");
    printf("• Sinais e interrupções (EINTR)\n");
    printf("• Debugging avançado com strace\n");
    
    return 0;
}