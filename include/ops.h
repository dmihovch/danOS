#include "cpu.h"
#include "utils.h"


#define REG 0x00
#define IMM4 0x01
#define MEM 0x10

int op_mov(cpu_t*, instr_t);
int op_ldi(cpu_t*, instr_t);
int op_add(cpu_t*, instr_t);
int op_sub(cpu_t*, instr_t);
int op_mul(cpu_t*, instr_t);
int op_div(cpu_t*, instr_t);
int op_and(cpu_t*, instr_t);
int op_or(cpu_t*, instr_t);
int op_xor(cpu_t*, instr_t);
int op_not(cpu_t*, instr_t);
int op_shl(cpu_t*, instr_t);
int op_shr(cpu_t*, instr_t);
int op_load(cpu_t*, instr_t);
int op_stor(cpu_t*, instr_t);
int op_comp(cpu_t*, instr_t);
int op_jump(cpu_t*, instr_t);
int op_jz(cpu_t*, instr_t);
int op_jnz(cpu_t*, instr_t);
int op_jg(cpu_t*, instr_t);
int op_jl(cpu_t*, instr_t);
int op_call(cpu_t*, instr_t);
int op_ret(cpu_t*, instr_t);
int op_push(cpu_t*, instr_t);
int op_push(cpu_t*, instr_t);
int op_pop(cpu_t*, instr_t);
