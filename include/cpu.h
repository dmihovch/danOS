#include "memory.h"
#include "debug.h"
#define GENERAL_REGISTER_COUNT 16
#define PROGRAM_CODE_START_ADDR 0x0000
#define PROGRAM_CODE_END_ADDR 0x4FFF
#define DATA_START_ADDR 0x5000
#define DATA_END_ADDR 0x8FFF
#define STACK_END_ADDR 0x9000 //more of a guide than anything
#define STACK_START_ADDR 0xFEFF
#define IO_SPEC_START_ADDR 0xFF00
#define IO_SPEC_END_ADDR 0xFFFF



/*
 * uint16_t* r: general registers (R0, R1, etc), amount defined by GENERAL_REGISTER_COUNT
 * uint16_t pc: program counter
 * uint16_t sp: stack pointer
 * uint16_t hp: heap pointer
 *
 *
 */
typedef struct registers_t {
    uint16_t r[GENERAL_REGISTER_COUNT];
    uint16_t pc;
    uint16_t sp;
    uint16_t flags;
} registers_t;

/*
 * opcode_mode: 6 MSB: opcode, 2 LSB: modes
 * operands: 4 MSB: dest register, 4 LSB: src register or small immediate (4 bits)
 */
typedef struct instr_t{
    uint8_t opcode_mode;
    uint8_t operands;
} instr_t;

/*
 * uint8_t* ram: memory array, size defined by MEMORY_CAP_BYTES
 *
 *
 * Stack Pointer points to the last thing added to the stack, so MEM[SP] == last thing added to stack,
 * MEM[SP+1] == next available memory space
 *
 *

 *
 */



typedef struct cpu_t {

    uint8_t ram[MEMORY_CAP_BYTES];
    registers_t regs;

} cpu_t;


cpu_t* init_cpu();

/*
 * p1: uint8_t* ram
 * p2: uint16_t* program counter
 * p3: uint8_t* program
 * p4: int program length
 */
int load_program(uint8_t*, uint16_t*, uint8_t*, int);


int fetch_decode_execute_loop();

/*
 * returns the primary instruction for decoding
 */
uint32_t fetch_instruction(uint8_t*, uint16_t*);
/*
 *
 */
instr_t format_instruction(uint32_t);

int execute_instruction(cpu_t*, instr_t);
