#include "../include/ops.h"


int nop(cpu_t* cpu, decoded_instr_t instr){

    printf("[debug] - nop\n");

    return 0;
}

int mov_reg_reg(cpu_t* cpu, decoded_instr_t instr){


    printf("[debug] - mov_reg_reg\n");

    uint8_t reg_dest = instr.reg_flags>> 5;
    uint8_t reg_src = instr.operand;
    cpu->regs.r[reg_dest] = cpu->regs.r[reg_src];

    return 0;

}

int mov_reg_imm(cpu_t * cpu, decoded_instr_t instr){

    printf("[debug] - mov_reg_imm\n");


    uint8_t reg_dest = get_register(instr.reg_flags);
    cpu->regs.r[reg_dest] = instr.operand;

    return 0;
}

int load_reg_addr(cpu_t * cpu, decoded_instr_t instr){




}
