#include <stdio.h>
#include <stdint.h>

// ==========================================
// EXEMPLO 1: Comparação entre Union e Struct
// ==========================================

// Struct tradicional - cada membro tem seu próprio espaço
struct dados_struct
{
    int inteiro;
    float decimal;
    char caractere;
};

// Union - todos os membros compartilham o mesmo espaço
union dados_union
{
    int inteiro;
    float decimal;
    char caractere;
};

// ==========================================
// EXEMPLO 2: Manipulação de registradores (muito comum em embarcados)
// ==========================================

// Union para acessar um registrador de 32 bits de diferentes formas
union registrador_32bits
{
    uint32_t valor_completo; // Acesso ao valor completo (32 bits)
    uint16_t metades[2];     // Acesso às duas metades de 16 bits
    uint8_t bytes[4];        // Acesso aos 4 bytes individuais

    struct
    { // Acesso a bits específicos
        uint32_t bit0 : 1;
        uint32_t bit1 : 1;
        uint32_t bits2_7 : 6;
        uint32_t byte1 : 8;
        uint32_t byte2 : 8;
        uint32_t byte3 : 8;
    } bits;
};

// ==========================================
// EXEMPLO 3: Protocolo de comunicação
// ==========================================

// Union para pacote de dados em comunicação serial
union pacote_dados
{
    uint8_t buffer[8]; // Buffer bruto de bytes

    struct
    { // Estrutura do pacote
        uint8_t header;
        uint8_t comando;
        uint16_t dados;
        uint32_t checksum;
    } campos;

    struct
    { // Interpretação como valores diferentes
        uint32_t parte1;
        uint32_t parte2;
    } dwords;
};

// ==========================================
// EXEMPLO 4: Conversão de tipos (Type Punning)
// ==========================================

// Union para converter entre float e seus bytes
union float_bytes
{
    float valor_float;
    uint8_t bytes[4];
    uint32_t valor_hex;
};

// ==========================================
// EXEMPLO 5: Estados de uma máquina de estados
// ==========================================

// Enum para tipos de dados
typedef enum
{
    TIPO_SENSOR_TEMP,
    TIPO_SENSOR_PRESSAO,
    TIPO_MOTOR_VELOCIDADE,
    TIPO_LED_STATUS
} tipo_dado_t;

// Union para diferentes tipos de dados do sistema
union valor_sistema
{
    struct
    {
        float temperatura;
        uint8_t unidade; // 'C' ou 'F'
    } sensor_temp;

    struct
    {
        uint16_t pressao;
        uint8_t escala; // 0=Pa, 1=bar, 2=psi
    } sensor_pressao;

    struct
    {
        uint16_t rpm;
        uint8_t direcao; // 0=horário, 1=anti-horário
    } motor;

    struct
    {
        uint8_t vermelho;
        uint8_t verde;
        uint8_t azul;
        uint8_t intensidade;
    } led_rgb;
};

// Estrutura que combina tipo e valor
typedef struct
{
    tipo_dado_t tipo;
    union valor_sistema valor;
} dado_sistema_t;

// ==========================================
// FUNÇÕES DEMONSTRATIVAS
// ==========================================

void demonstrar_basico()
{
    printf("=== DEMONSTRAÇÃO BÁSICA ===\n");

    // Comparando tamanhos
    printf("Tamanho da struct: %lu bytes\n", sizeof(struct dados_struct));
    printf("Tamanho da union:  %lu bytes\n", sizeof(union dados_union));

    union dados_union exemplo;

    // Definindo um inteiro
    exemplo.inteiro = 1234567890;
    printf("Inteiro: %d\n", exemplo.inteiro);
    printf("Float (interpretado): %f\n", exemplo.decimal);
    printf("Char (interpretado): %c (%d)\n", exemplo.caractere, exemplo.caractere);

    // Definindo um float
    exemplo.decimal = 3.14159f;
    printf("\nFloat: %f\n", exemplo.decimal);
    printf("Inteiro (interpretado): %d\n", exemplo.inteiro);

    printf("\n");
}

void demonstrar_registrador()
{
    printf("=== MANIPULAÇÃO DE REGISTRADOR ===\n");

    union registrador_32bits reg;

    // Definindo valor completo
    reg.valor_completo = 0x12345678;

    printf("Valor completo: 0x%08X\n", reg.valor_completo);
    printf("Metade alta: 0x%04X\n", reg.metades[1]);
    printf("Metade baixa: 0x%04X\n", reg.metades[0]);

    printf("Bytes individuais:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("  Byte[%d]: 0x%02X\n", i, reg.bytes[i]);
    }

    // Modificando bits específicos
    reg.bits.bit0 = 1;
    reg.bits.bit1 = 0;
    printf("Após modificar bits 0 e 1: 0x%08X\n", reg.valor_completo);

    printf("\n");
}

void demonstrar_protocolo()
{
    printf("=== PROTOCOLO DE COMUNICAÇÃO ===\n");

    union pacote_dados pacote;

    // Montando pacote pelos campos
    pacote.campos.header = 0xAA;
    pacote.campos.comando = 0x01;
    pacote.campos.dados = 0x1234;
    pacote.campos.checksum = 0x56789ABC;

    printf("Pacote montado:\n");
    printf("  Header: 0x%02X\n", pacote.campos.header);
    printf("  Comando: 0x%02X\n", pacote.campos.comando);
    printf("  Dados: 0x%04X\n", pacote.campos.dados);
    printf("  Checksum: 0x%08X\n", pacote.campos.checksum);

    printf("Buffer bruto: ");
    for (int i = 0; i < 8; i++)
    {
        printf("0x%02X ", pacote.buffer[i]);
    }
    printf("\n\n");
}

void demonstrar_conversao_float()
{
    printf("=== CONVERSÃO DE FLOAT ===\n");

    union float_bytes conversor;

    conversor.valor_float = 3.14159f;

    printf("Float: %f\n", conversor.valor_float);
    printf("Representação hexadecimal: 0x%08X\n", conversor.valor_hex);
    printf("Bytes individuais: ");
    for (int i = 0; i < 4; i++)
    {
        printf("0x%02X ", conversor.bytes[i]);
    }
    printf("\n\n");
}

void demonstrar_sistema_embarcado()
{
    printf("=== SISTEMA EMBARCADO ===\n");

    dado_sistema_t dados[4];

    // Sensor de temperatura
    dados[0].tipo = TIPO_SENSOR_TEMP;
    dados[0].valor.sensor_temp.temperatura = 25.5f;
    dados[0].valor.sensor_temp.unidade = 'C';

    // Sensor de pressão
    dados[1].tipo = TIPO_SENSOR_PRESSAO;
    dados[1].valor.sensor_pressao.pressao = 1013;
    dados[1].valor.sensor_pressao.escala = 1; // bar

    // Motor
    dados[2].tipo = TIPO_MOTOR_VELOCIDADE;
    dados[2].valor.motor.rpm = 1500;
    dados[2].valor.motor.direcao = 0; // horário

    // LED RGB
    dados[3].tipo = TIPO_LED_STATUS;
    dados[3].valor.led_rgb.vermelho = 255;
    dados[3].valor.led_rgb.verde = 128;
    dados[3].valor.led_rgb.azul = 0;
    dados[3].valor.led_rgb.intensidade = 200;

    // Exibindo dados
    for (int i = 0; i < 4; i++)
    {
        switch (dados[i].tipo)
        {
        case TIPO_SENSOR_TEMP:
            printf("Temperatura: %.1f°%c\n",
                    dados[i].valor.sensor_temp.temperatura,
                    dados[i].valor.sensor_temp.unidade);
            break;

        case TIPO_SENSOR_PRESSAO:
            printf("Pressão: %d %s\n",
                    dados[i].valor.sensor_pressao.pressao,
                    dados[i].valor.sensor_pressao.escala == 1 ? "bar" : "Pa");
            break;

        case TIPO_MOTOR_VELOCIDADE:
            printf("Motor: %d RPM (%s)\n",
                    dados[i].valor.motor.rpm,
                    dados[i].valor.motor.direcao == 0 ? "horário" : "anti-horário");
            break;

        case TIPO_LED_STATUS:
            printf("LED RGB: R=%d, G=%d, B=%d (intensidade: %d)\n",
                    dados[i].valor.led_rgb.vermelho,
                    dados[i].valor.led_rgb.verde,
                    dados[i].valor.led_rgb.azul,
                    dados[i].valor.led_rgb.intensidade);
            break;
        }
    }

    printf("Tamanho de cada dado: %lu bytes\n", sizeof(dado_sistema_t));
}

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================

int main()
{
    printf("EXEMPLOS DE UNION EM C PARA SISTEMAS EMBARCADOS\n");
    printf("===============================================\n\n");

    demonstrar_basico();
    demonstrar_registrador();
    demonstrar_protocolo();
    demonstrar_conversao_float();
    demonstrar_sistema_embarcado();

    return 0;
}

/*
Output:
EXEMPLOS DE UNION EM C PARA SISTEMAS EMBARCADOS
===============================================

=== DEMONSTRAÇÃO BÁSICA ===
Tamanho da struct: 12 bytes
Tamanho da union:  4 bytes
Inteiro: 1234567890
Float (interpretado): 1228890.250000
Char (interpretado): � (-46)

Float: 3.141590
Inteiro (interpretado): 1078530000

=== MANIPULAÇÃO DE REGISTRADOR ===
Valor completo: 0x12345678
Metade alta: 0x1234
Metade baixa: 0x5678
Bytes individuais:
  Byte[0]: 0x78
  Byte[1]: 0x56
  Byte[2]: 0x34
  Byte[3]: 0x12
Após modificar bits 0 e 1: 0x12345679

=== PROTOCOLO DE COMUNICAÇÃO ===
Pacote montado:
  Header: 0xAA
  Comando: 0x01
  Dados: 0x1234
  Checksum: 0x56789ABC
Buffer bruto: 0xAA 0x01 0x34 0x12 0xBC 0x9A 0x78 0x56 

=== CONVERSÃO DE FLOAT ===
Float: 3.141590
Representação hexadecimal: 0x40490FD0
Bytes individuais: 0xD0 0x0F 0x49 0x40 

=== SISTEMA EMBARCADO ===
Temperatura: 25.5°C
Pressão: 1013 bar
Motor: 1500 RPM (horário)
LED RGB: R=255, G=128, B=0 (intensidade: 200)
Tamanho de cada dado: 12 bytes
*/