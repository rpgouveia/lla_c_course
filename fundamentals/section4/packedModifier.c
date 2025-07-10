#include <stdio.h>
#include <stdint.h>
#include <string.h>  // Para memcpy

// Declarações das funções
void process_sensor_data(uint8_t *i2c_buffer);
void demo_sensor_reading(void);

// Struct normal (com padding automático)
struct normal_struct {
    uint8_t  byte1;     // 1 byte
    uint32_t dword;     // 4 bytes
    uint8_t  byte2;     // 1 byte
    uint16_t word;      // 2 bytes
};

// Struct packed (sem padding)
struct __attribute__((packed)) packed_struct {
    uint8_t  byte1;     // 1 byte
    uint32_t dword;     // 4 bytes
    uint8_t  byte2;     // 1 byte
    uint16_t word;      // 2 bytes
};

// Exemplo prático: Protocolo de comunicação
struct __attribute__((packed)) protocol_header {
    uint8_t  start_byte;    // 0xAA
    uint8_t  command;       // Comando
    uint16_t length;        // Tamanho dos dados
    uint32_t timestamp;     // Timestamp
    uint8_t  checksum;      // Checksum
};

// Exemplo: Registro de microcontrolador
struct __attribute__((packed)) mcu_register {
    uint8_t bit0_3   : 4;   // Bits 0-3
    uint8_t bit4_7   : 4;   // Bits 4-7
    uint8_t reserved : 6;   // Bits 8-13 (reservados)
    uint8_t enable   : 1;   // Bit 14
    uint8_t ready    : 1;   // Bit 15
};

// União para facilitar acesso aos registros
union register_access {
    struct __attribute__((packed)) {
        uint8_t low_byte;
        uint8_t high_byte;
    } bytes;
    uint16_t word;
} __attribute__((packed));

int main() {
    printf("=== COMPARAÇÃO DE TAMANHOS ===\n");
    printf("Struct normal: %zu bytes\n", sizeof(struct normal_struct));
    printf("Struct packed: %zu bytes\n", sizeof(struct packed_struct));
    printf("\n");
    
    // Análise detalhada da struct normal
    struct normal_struct normal = {0x11, 0x22334455, 0x66, 0x7788};
    printf("=== STRUCT NORMAL (com padding) ===\n");
    printf("Endereços dos membros:\n");
    printf("byte1: %p (offset: %zu)\n", &normal.byte1, (size_t)&normal.byte1 - (size_t)&normal);
    printf("dword: %p (offset: %zu)\n", &normal.dword, (size_t)&normal.dword - (size_t)&normal);
    printf("byte2: %p (offset: %zu)\n", &normal.byte2, (size_t)&normal.byte2 - (size_t)&normal);
    printf("word:  %p (offset: %zu)\n", &normal.word, (size_t)&normal.word - (size_t)&normal);
    printf("\n");
    
    // Análise detalhada da struct packed
    struct packed_struct packed = {0x11, 0x22334455, 0x66, 0x7788};
    printf("=== STRUCT PACKED (sem padding) ===\n");
    printf("Endereços dos membros:\n");
    printf("byte1: %p (offset: %zu)\n", &packed.byte1, (size_t)&packed.byte1 - (size_t)&packed);
    printf("dword: %p (offset: %zu)\n", &packed.dword, (size_t)&packed.dword - (size_t)&packed);
    printf("byte2: %p (offset: %zu)\n", &packed.byte2, (size_t)&packed.byte2 - (size_t)&packed);
    printf("word:  %p (offset: %zu)\n", &packed.word, (size_t)&packed.word - (size_t)&packed);
    printf("\n");
    
    // Exemplo prático: cabeçalho de protocolo
    printf("=== EXEMPLO PRÁTICO: PROTOCOLO ===\n");
    struct protocol_header header = {
        .start_byte = 0xAA,
        .command = 0x01,
        .length = 1024,
        .timestamp = 0x12345678,
        .checksum = 0xFF
    };
    
    printf("Tamanho do cabeçalho: %zu bytes\n", sizeof(header));
    printf("Dados do cabeçalho:\n");
    
    // Mostra os bytes como seriam transmitidos
    uint8_t *bytes = (uint8_t*)&header;
    printf("Bytes: ");
    for (size_t i = 0; i < sizeof(header); i++) {
        printf("0x%02X ", bytes[i]);
    }
    printf("\n\n");
    
    // Exemplo com bit fields
    printf("=== EXEMPLO: BIT FIELDS ===\n");
    struct mcu_register reg = {
        .bit0_3 = 0x5,    // 0101 em binário
        .bit4_7 = 0xA,    // 1010 em binário
        .reserved = 0,
        .enable = 1,
        .ready = 0
    };
    
    printf("Tamanho do registro: %zu bytes\n", sizeof(reg));
    
    // MÉTODO SEGURO 1: Usar memcpy para evitar problemas de alinhamento
    uint16_t reg_value;
    memcpy(&reg_value, &reg, sizeof(uint16_t));
    printf("Valor do registro (memcpy): 0x%04X\n", reg_value);
    
    // MÉTODO SEGURO 2: Acessar byte por byte
    uint8_t *reg_bytes = (uint8_t*)&reg;
    uint16_t reg_value2 = reg_bytes[0] | (reg_bytes[1] << 8);
    printf("Valor do registro (byte a byte): 0x%04X\n", reg_value2);
    
    // MÉTODO INSEGURO (gera warning): 
    // uint16_t *reg_ptr = (uint16_t*)&reg;  // <- EVITE ISSO!
    
    printf("Bit 0-3: 0x%X\n", reg.bit0_3);
    printf("Bit 4-7: 0x%X\n", reg.bit4_7);
    printf("Enable: %d\n", reg.enable);
    printf("Ready: %d\n", reg.ready);
    printf("\n");
    
    // Exemplo com união
    printf("=== EXEMPLO: UNIÃO PARA ACESSO A BYTES ===\n");
    union register_access reg_union;
    reg_union.word = 0x1234;
    
    printf("Valor da palavra: 0x%04X\n", reg_union.word);
    printf("Byte baixo: 0x%02X\n", reg_union.bytes.low_byte);
    printf("Byte alto: 0x%02X\n", reg_union.bytes.high_byte);
    
    // Demonstração com dados de sensor
    demo_sensor_reading();
    
    return 0;
}

/* 
=== COMO EVITAR WARNINGS DE ALINHAMENTO ===

1. USE MEMCPY PARA CONVERSÕES SEGURAS:
   uint16_t value;
   memcpy(&value, &packed_struct, sizeof(uint16_t));

2. ACESSE BYTE POR BYTE:
   uint8_t *bytes = (uint8_t*)&packed_struct;
   uint16_t value = bytes[0] | (bytes[1] << 8);

3. USE UNIÕES QUANDO APROPRIADO:
   union {
       struct packed_data data;
       uint8_t bytes[sizeof(struct packed_data)];
   } converter;

4. PARA REGISTRADORES DE MCU, CONSIDERE:
   volatile uint16_t *reg = (volatile uint16_t*)0x40000000; // Endereço do HW

=== EXEMPLO PRÁTICO: LENDO SENSOR VIA I2C ===
*/

// Exemplo: Dados de um sensor de temperatura via I2C
struct __attribute__((packed)) temp_sensor_data {
    uint8_t  status;        // Status do sensor
    int16_t  temperature;   // Temperatura em centésimos de grau
    uint8_t  humidity;      // Umidade em %
    uint16_t pressure;      // Pressão em Pa
};

void process_sensor_data(uint8_t *i2c_buffer) {
    struct temp_sensor_data sensor;
    
    // Método seguro: copiar dados do buffer I2C
    memcpy(&sensor, i2c_buffer, sizeof(sensor));
    
    printf("\n=== DADOS DO SENSOR ===\n");
    printf("Status: 0x%02X\n", sensor.status);
    printf("Temperatura: %.2f°C\n", sensor.temperature / 100.0);
    printf("Umidade: %d%%\n", sensor.humidity);
    printf("Pressão: %d Pa\n", sensor.pressure);
}

// Exemplo: Função para demonstrar
void demo_sensor_reading() {
    // Simula dados recebidos via I2C (6 bytes)
    uint8_t i2c_data[] = {0x01, 0x6C, 0x07, 0x45, 0x10, 0x27}; // Status=1, Temp=18.92°C, Hum=69%, Press=10000Pa
    
    process_sensor_data(i2c_data);
}