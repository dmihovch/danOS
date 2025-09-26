#include "../include/ops.h"

int op_mov(cpu_t* cpu, instr_t instr){

    switch(instr.mode){
        case REG:
            //reg,reg
            cpu->regs.r[instr.dest] = cpu->regs.r[instr.src_fl];
            return 0;
        case IMM4:
            cpu->regs.r[instr.dest] = instr.src_fl;
            //reg,imm4
            return 0;
        case MEM:
            cpu->regs.r[instr.dest] = cpu->ram[cpu->regs.r[instr.src_fl]];
            //reg,mem
            return 0;
        default:
            printf("undefined mode in op_mov: 0x%x\n",instr.mode);
            return 1;
    }


}

int op_ldi(cpu_t * cpu, instr_t instr){
    uint8_t high_byte;
    uint8_t low_byte;
    uint16_t imm;

    high_byte = cpu->ram[cpu->regs.pc];
    cpu->regs.pc++;
    if(cpu->regs.pc > PROGRAM_CODE_END_ADDR){
        printf("broke through program code space in ldi\n");
        return 1;
    }
    low_byte = cpu->ram[cpu->regs.pc];
    cpu->regs.pc++;
    if(cpu->regs.pc > PROGRAM_CODE_END_ADDR){
        printf("broke through program code space in ldi\n");
        return 1;
    }
    imm = ((uint16_t)high_byte<<8) | low_byte;

    cpu->regs.r[instr.dest] = imm;
    return 0;

}

int op_add(cpu_t * cpu, instr_t instr){
    switch(instr.mode){
        case REG:
            cpu->regs.r[instr.dest]+=cpu->regs.r[instr.src_fl];
    }
}
