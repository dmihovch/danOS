#include "memory.h"
#include "debug.h"
#define GENERAL_REGISTER_COUNT 4

/*
 * uint16_t* r: general registers (R0, R1, etc), amount defined by GENERAL_REGISTER_COUNT
 * uint16_t pc: program counter
 * uint16_t sp: stack pointer
 *
 *
 */
typedef struct registers_t {
    uint16_t r[GENERAL_REGISTER_COUNT];
    uint16_t pc;
    uint16_t sp;
} registers_t;

/*
 * uint8_t* ram: memory array, size defined by MEMORY_CAP_BYTES
 *
 *
 * the address of the stack pointer will always point to the next available chunk,
 * so ram[sp] is empty memory, ram[sp - 1] is the last index of the last element on the stack
 *
 * Memory is segmented in the following way:
 *
 * 0x0000 - 0x3FFF ; Program code
 * 0x4000 - 0x5FFF ; Data/global vars
 * 0x6000 - 0xCFFF ; Heap (starts at 0x6000)
 * 0xD000 - 0xFEFF ; Stack (starts at 0xFEFF)
 * 0xFF00 - 0xFFFF ; I/O special addresses
 *
 */
typedef struct cpu_t {

    uint8_t ram[MEMORY_CAP_BYTES];
    registers_t regs;

} cpu_t;


cpu_t* init_cpu();
