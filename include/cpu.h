#include "memory.h"
#include "debug.h"
#define GENERAL_REGISTER_COUNT 8
#define PROGRAM_CODE_START_ADDR 0x0000
#define PROGRAM_CODE_END_ADDR 0x3FFF
#define DATA_START_ADDR 0x4000
#define DATA_END_ADDR 0x5FFF
#define HEAP_START_ADDR 0x6000
#define HEAP_END_ADDR 0xCFFF
#define STACK_START_ADDR 0xD000
#define STACK_END_ADDR 0xFEFF
#define IO_SPEC_START_ADDR 0xFF00
#define IO_SPEC_END_ADDR 0xFFFF


#define OP_DATA_MOVE 0b0000
#define OP_ARITH 0b0001
#define OP_LOGIC 0b0010
#define OP_COMP 0b0011
#define OP_BRANCH 0b0100
#define OP_STACK 0b0101
#define OP_SYS 0b0110


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


typedef struct decoded_instr_t{
    uint8_t opcode;
    uint8_t reg_type_flag;
    uint16_t operand;
} decoded_instr_t;

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
decoded_instr_t format_instruction(uint32_t);

int execute_instruction(cpu_t*, decoded_instr_t );


int data_movement_ops(cpu_t*, decoded_instr_t);
int arithmetic_ops(cpu_t*, decoded_instr_t);
int logic_bitwise_ops(cpu_t*, decoded_instr_t);
int compare_condition_ops(cpu_t*, decoded_instr_t);
int branch_controlflow_ops(cpu_t*, decoded_instr_t);
int stack_ops(cpu_t*, decoded_instr_t);
int system_ops(cpu_t*, decoded_instr_t);

//deprecated?
int subopcode_ops(cpu_t*, decoded_instr_t, int(*)(cpu_t*, decoded_instr_t));
