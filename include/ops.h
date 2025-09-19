#include "cpu.h"
#include "utils.h"


//all of these are going to DIE

//data movement operations
int nop(cpu_t*, instr_t);
int mov_reg_reg(cpu_t*, instr_t);
int mov_reg_imm(cpu_t*, instr_t);
int load_reg_addr(cpu_t*, instr_t);
int load_reg_regoff(cpu_t*, instr_t);
int store_addr_reg(cpu_t*, instr_t);
int store_regoff_reg(cpu_t*, instr_t);
int push_reg(cpu_t*, instr_t);
int pop_reg(cpu_t*, instr_t);
int lea_reg_addr(cpu_t*, instr_t);


//arithmetic operations
int add_reg_reg(cpu_t*, instr_t);
int add_reg_imm(cpu_t*, instr_t);
int sub_reg_reg(cpu_t*, instr_t);
int sub_reg_imm(cpu_t*, instr_t);
int mul_reg_reg(cpu_t*, instr_t);
int mul_reg_imm(cpu_t*, instr_t);
int div_reg_reg(cpu_t*, instr_t);
int div_reg_imm(cpu_t*, instr_t);
int inc_reg(cpu_t*, instr_t);
int dec_reg(cpu_t*, instr_t);


//logical / bitwise operations
int and_reg_reg(cpu_t*, instr_t);
int and_reg_imm(cpu_t*, instr_t);
int or_reg_reg(cpu_t*, instr_t);
int or_reg_imm(cpu_t*, instr_t);
int xor_reg_reg(cpu_t*, instr_t);
int xor_reg_imm(cpu_t*, instr_t);
int not_reg(cpu_t*, instr_t);
int shl_reg_imm(cpu_t*, instr_t);
int shr_reg_imm(cpu_t*, instr_t);
int rol_reg_imm(cpu_t*, instr_t);
int ror_reg_imm(cpu_t*, instr_t);



//comparisons and condition code operations
int cmp_reg_reg(cpu_t*, instr_t);
int cmp_reg_imm(cpu_t*, instr_t);
int test_reg_reg(cpu_t*, instr_t);
int test_reg_imm(cpu_t*, instr_t);
int seteq_reg(cpu_t*, instr_t);
int setne_reg(cpu_t*, instr_t);
int setgt_reg(cpu_t*, instr_t);
int setlt_reg(cpu_t*, instr_t);


//branch / control flow operations
int jmp_addr(cpu_t*, instr_t);
int jz_addr(cpu_t*, instr_t);
int jnz_addr(cpu_t*, instr_t);
int jg_addr(cpu_t*, instr_t);
int jl_addr(cpu_t*, instr_t);
int call_addr(cpu_t*, instr_t);
int ret(cpu_t*, instr_t);
int loop_reg_addr(cpu_t*, instr_t);



//stack/procedure helper operations
int enter_imm(cpu_t*, instr_t);
int leave(cpu_t*, instr_t);
int push_imm(cpu_t*, instr_t);
int popall(cpu_t*, instr_t);

//system / special operations
int interupt_imm(cpu_t*, instr_t);
int syscall_reg(cpu_t*, instr_t);
int halt_op(cpu_t*, instr_t);
int wait_op(cpu_t*, instr_t);
int break_op(cpu_t*, instr_t);
