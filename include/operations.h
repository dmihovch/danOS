#include <stdint.h>


#define OP_DATA_MOVE 0b0000
#define OP_ARITH 0b0001
#define OP_LOGIC 0b0010
#define OP_COMP 0b0011
#define OP_BRANCH 0b0100
#define OP_STACK 0b0101
#define OP_SYS 0b0110


typedef struct decoded_instr_t{
    uint8_t opcode;
    uint8_t reg_type_flag;
    uint16_t operand;
} decoded_instr_t;


int data_movement_ops(decoded_instr_t);
int arithmetic_ops(decoded_instr_t);
int logic_bitwise_ops(decoded_instr_t);
int compare_condition_ops(decoded_instr_t);
int branch_controlflow_ops(decoded_instr_t);
int stack_ops(decoded_instr_t);
int system_ops(decoded_instr_t);
