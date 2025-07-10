#include <stdio.h>
#include <stdint.h>
#include <string.h>

// ==========================================
// DEMONSTRAÇÃO: ENDEREÇOS DE MEMÓRIA
// ==========================================

struct exemplo_struct {
    int inteiro;
    float decimal;
    char caractere;
};

union exemplo_union {
    int inteiro;
    float decimal;
    char caractere;
    uint8_t bytes[4];  // Array para ver byte por byte
};

// ==========================================
// FUNÇÃO PARA MOSTRAR ENDEREÇOS
// ==========================================

void mostrar_enderecos() {
    printf("=== COMPARAÇÃO DE ENDEREÇOS DE MEMÓRIA ===\n\n");
    
    struct exemplo_struct s;
    union exemplo_union u;
    
    printf("STRUCT (cada membro tem seu próprio endereço):\n");
    printf("  Endereço de s.inteiro:   %p\n", (void*)&s.inteiro);
    printf("  Endereço de s.decimal:   %p\n", (void*)&s.decimal);
    printf("  Endereço de s.caractere: %p\n", (void*)&s.caractere);
    printf("  Diferença entre inteiro e decimal: %ld bytes\n\n", 
            (char*)&s.decimal - (char*)&s.inteiro);
    
    printf("UNION (todos os membros têm o MESMO endereço):\n");
    printf("  Endereço de u.inteiro:   %p\n", (void*)&u.inteiro);
    printf("  Endereço de u.decimal:   %p\n", (void*)&u.decimal);
    printf("  Endereço de u.caractere: %p\n", (void*)&u.caractere);
    printf("  Endereço de u.bytes:     %p\n", (void*)&u.bytes);
    printf("  Diferença entre endereços: %ld bytes\n\n", 
            (char*)&u.decimal - (char*)&u.inteiro);
}

// ==========================================
// DEMONSTRAÇÃO: SOBREPOSIÇÃO DE DADOS
// ==========================================

void demonstrar_sobreposicao() {
    printf("=== DEMONSTRAÇÃO: SOBREPOSIÇÃO DE DADOS ===\n\n");
    
    union exemplo_union u;
    
    // Zerando toda a union
    memset(&u, 0, sizeof(u));
    
    printf("Estado inicial (todos os bytes zerados):\n");
    printf("  inteiro: %d\n", u.inteiro);
    printf("  decimal: %f\n", u.decimal);
    printf("  caractere: '%c' (código: %d)\n", u.caractere, u.caractere);
    printf("  bytes: [%02X %02X %02X %02X]\n\n", 
            u.bytes[0], u.bytes[1], u.bytes[2], u.bytes[3]);
    
    // Escrevendo um inteiro
    printf("Escrevendo u.inteiro = 0x12345678 (305419896 em decimal):\n");
    u.inteiro = 0x12345678;
    
    printf("  inteiro: %d (0x%08X)\n", u.inteiro, u.inteiro);
    printf("  decimal: %f (interpretação incorreta!)\n", u.decimal);
    printf("  caractere: '%c' (código: %d)\n", 
            u.caractere >= 32 && u.caractere <= 126 ? u.caractere : '?', u.caractere);
    printf("  bytes: [%02X %02X %02X %02X]\n\n", 
            u.bytes[0], u.bytes[1], u.bytes[2], u.bytes[3]);
    
    // Escrevendo um float
    printf("Agora escrevendo u.decimal = 3.14159:\n");
    u.decimal = 3.14159f;
    
    printf("  inteiro: %d (interpretação incorreta!)\n", u.inteiro);
    printf("  decimal: %f (0x%08X em hex)\n", u.decimal, *(uint32_t*)&u.decimal);
    printf("  caractere: '%c' (código: %d)\n", 
            u.caractere >= 32 && u.caractere <= 126 ? u.caractere : '?', u.caractere);
    printf("  bytes: [%02X %02X %02X %02X]\n\n", 
            u.bytes[0], u.bytes[1], u.bytes[2], u.bytes[3]);
    
    // Modificando apenas um byte
    printf("Modificando apenas u.bytes[0] = 0xFF:\n");
    u.bytes[0] = 0xFF;
    
    printf("  inteiro: %d\n", u.inteiro);
    printf("  decimal: %f\n", u.decimal);
    printf("  caractere: '%c' (código: %d)\n", 
            u.caractere >= 32 && u.caractere <= 126 ? u.caractere : '?', u.caractere);
    printf("  bytes: [%02X %02X %02X %02X]\n\n", 
            u.bytes[0], u.bytes[1], u.bytes[2], u.bytes[3]);
}

// ==========================================
// EXEMPLO PRÁTICO: ANÁLISE BYTE A BYTE
// ==========================================

void analisar_representacao() {
    printf("=== ANÁLISE BYTE A BYTE ===\n\n");
    
    union {
        uint32_t valor_32bits;
        uint16_t valores_16bits[2];
        uint8_t valores_8bits[4];
        struct {
            uint8_t byte0;
            uint8_t byte1; 
            uint8_t byte2;
            uint8_t byte3;
        } bytes_nomeados;
    } dados;
    
    // Definindo um valor conhecido
    dados.valor_32bits = 0xAABBCCDD;
    
    printf("Valor original: 0x%08X\n\n", dados.valor_32bits);
    
    printf("Interpretações diferentes dos MESMOS 4 bytes:\n");
    printf("  Como uint32_t:     0x%08X (%u)\n", 
            dados.valor_32bits, dados.valor_32bits);
    printf("  Como uint16_t[0]:  0x%04X (%u)\n", 
            dados.valores_16bits[0], dados.valores_16bits[0]);
    printf("  Como uint16_t[1]:  0x%04X (%u)\n", 
            dados.valores_16bits[1], dados.valores_16bits[1]);
    
    printf("  Como bytes individuais:\n");
    for(int i = 0; i < 4; i++) {
        printf("    byte[%d]: 0x%02X (%u)\n", 
                i, dados.valores_8bits[i], dados.valores_8bits[i]);
    }
    
    printf("  Como bytes nomeados:\n");
    printf("    byte0: 0x%02X\n", dados.bytes_nomeados.byte0);
    printf("    byte1: 0x%02X\n", dados.bytes_nomeados.byte1);
    printf("    byte2: 0x%02X\n", dados.bytes_nomeados.byte2);
    printf("    byte3: 0x%02X\n", dados.bytes_nomeados.byte3);
    
    printf("\nTodos esses valores estão no MESMO lugar na memória!\n\n");
}

// ==========================================
// EXEMPLO: MODIFICAÇÃO CRUZADA
// ==========================================

void demonstrar_modificacao_cruzada() {
    printf("=== MODIFICAÇÃO CRUZADA ===\n\n");
    
    union {
        uint32_t numero;
        struct {
            uint16_t parte_baixa;
            uint16_t parte_alta;
        } partes;
        uint8_t bytes[4];
    } reg;
    
    // Estado inicial
    reg.numero = 0x12345678;
    printf("Valor inicial: 0x%08X\n", reg.numero);
    printf("  Parte alta: 0x%04X\n", reg.partes.parte_alta);
    printf("  Parte baixa: 0x%04X\n", reg.partes.parte_baixa);
    
    // Modificando apenas a parte alta
    printf("\nModificando apenas a parte alta para 0xAAAA:\n");
    reg.partes.parte_alta = 0xAAAA;
    
    printf("Valor completo agora: 0x%08X\n", reg.numero);
    printf("  Parte alta: 0x%04X\n", reg.partes.parte_alta);
    printf("  Parte baixa: 0x%04X (não mudou!)\n", reg.partes.parte_baixa);
    
    // Modificando apenas um byte
    printf("\nModificando apenas bytes[1] para 0xFF:\n");
    reg.bytes[1] = 0xFF;
    
    printf("Valor completo agora: 0x%08X\n", reg.numero);
    printf("  Parte alta: 0x%04X\n", reg.partes.parte_alta);
    printf("  Parte baixa: 0x%04X\n", reg.partes.parte_baixa);
    
    printf("  Bytes individuais: ");
    for(int i = 0; i < 4; i++) {
        printf("[%d]=0x%02X ", i, reg.bytes[i]);
    }
    printf("\n\n");
}

// ==========================================
// COMPARAÇÃO VISUAL DE TAMANHOS
// ==========================================

void comparar_tamanhos() {
    printf("=== COMPARAÇÃO DE TAMANHOS ===\n\n");
    
    struct grande_struct {
        int a;
        float b;
        double c;
        char d;
    };
    
    union grande_union {
        int a;
        float b;
        double c;    // Este é o maior (8 bytes)
        char d;
    };
    
    printf("Tamanhos em memória:\n");
    printf("  struct grande_struct: %lu bytes\n", sizeof(struct grande_struct));
    printf("  union grande_union:   %lu bytes\n", sizeof(union grande_union));
    printf("  double (maior membro): %lu bytes\n\n", sizeof(double));
    
    printf("A union sempre tem o tamanho do seu MAIOR membro!\n");
    printf("(pode ter padding adicional para alinhamento)\n\n");
}

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================

int main() {
    printf("DEMONSTRAÇÃO: COMO AS UNIONS COMPARTILHAM MEMÓRIA\n");
    printf("=================================================\n\n");
    
    mostrar_enderecos();
    demonstrar_sobreposicao();
    analisar_representacao();
    demonstrar_modificacao_cruzada();
    comparar_tamanhos();
    
    printf("RESUMO:\n");
    printf("• Todos os membros de uma union ocupam o MESMO endereço\n");
    printf("• Modificar um membro afeta todos os outros\n");
    printf("• O tamanho da union é igual ao seu maior membro\n");
    printf("• Útil para economizar memória e interpretar dados\n");
    
    return 0;
}

/*
Output:
DEMONSTRAÇÃO: COMO AS UNIONS COMPARTILHAM MEMÓRIA
=================================================

=== COMPARAÇÃO DE ENDEREÇOS DE MEMÓRIA ===

STRUCT (cada membro tem seu próprio endereço):
  Endereço de s.inteiro:   0x7ffd1746b648
  Endereço de s.decimal:   0x7ffd1746b64c
  Endereço de s.caractere: 0x7ffd1746b650
  Diferença entre inteiro e decimal: 4 bytes

UNION (todos os membros têm o MESMO endereço):
  Endereço de u.inteiro:   0x7ffd1746b654
  Endereço de u.decimal:   0x7ffd1746b654
  Endereço de u.caractere: 0x7ffd1746b654
  Endereço de u.bytes:     0x7ffd1746b654
  Diferença entre endereços: 0 bytes

=== DEMONSTRAÇÃO: SOBREPOSIÇÃO DE DADOS ===

Estado inicial (todos os bytes zerados):
  inteiro: 0
  decimal: 0.000000
  caractere: '' (código: 0)
  bytes: [00 00 00 00]

Escrevendo u.inteiro = 0x12345678 (305419896 em decimal):
  inteiro: 305419896 (0x12345678)
  decimal: 0.000000 (interpretação incorreta!)
  caractere: 'x' (código: 120)
  bytes: [78 56 34 12]

Agora escrevendo u.decimal = 3.14159:
  inteiro: 1078530000 (interpretação incorreta!)
  decimal: 3.141590 (0x40490FD0 em hex)
  caractere: '?' (código: -48)
  bytes: [D0 0F 49 40]

Modificando apenas u.bytes[0] = 0xFF:
  inteiro: 1078530047
  decimal: 3.141601
  caractere: '?' (código: -1)
  bytes: [FF 0F 49 40]

=== ANÁLISE BYTE A BYTE ===

Valor original: 0xAABBCCDD

Interpretações diferentes dos MESMOS 4 bytes:
  Como uint32_t:     0xAABBCCDD (2864434397)
  Como uint16_t[0]:  0xCCDD (52445)
  Como uint16_t[1]:  0xAABB (43707)
  Como bytes individuais:
    byte[0]: 0xDD (221)
    byte[1]: 0xCC (204)
    byte[2]: 0xBB (187)
    byte[3]: 0xAA (170)
  Como bytes nomeados:
    byte0: 0xDD
    byte1: 0xCC
    byte2: 0xBB
    byte3: 0xAA

Todos esses valores estão no MESMO lugar na memória!

=== MODIFICAÇÃO CRUZADA ===

Valor inicial: 0x12345678
  Parte alta: 0x1234
  Parte baixa: 0x5678

Modificando apenas a parte alta para 0xAAAA:
Valor completo agora: 0xAAAA5678
  Parte alta: 0xAAAA
  Parte baixa: 0x5678 (não mudou!)

Modificando apenas bytes[1] para 0xFF:
Valor completo agora: 0xAAAAFF78
  Parte alta: 0xAAAA
  Parte baixa: 0xFF78
  Bytes individuais: [0]=0x78 [1]=0xFF [2]=0xAA [3]=0xAA 

=== COMPARAÇÃO DE TAMANHOS ===

Tamanhos em memória:
  struct grande_struct: 24 bytes
  union grande_union:   8 bytes
  double (maior membro): 8 bytes

A union sempre tem o tamanho do seu MAIOR membro!
(pode ter padding adicional para alinhamento)

RESUMO:
• Todos os membros de uma union ocupam o MESMO endereço
• Modificar um membro afeta todos os outros
• O tamanho da union é igual ao seu maior membro
• Útil para economizar memória e interpretar dados
*/