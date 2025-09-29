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

    int16_t sum;
    int16_t a;
    int16_t b;
    switch(instr.mode){
        a = cpu->regs.r[instr.dest];
        case REG:
            b = cpu->regs.r[instr.src_fl];
            sum = a + b;
        case IMM4:
            b = instr.src_fl;
            sum = cpu->regs.r[instr.dest]+=(uint16_t)instr.src_fl;
    }
    if(sum == 0){
        set_flag_bit(&cpu->regs.flags, FLAG_ZERO, SET_TRUE);
    }
    else{
        set_flag_bit(&cpu->regs.flags, FLAG_ZERO, SET_FALSE);
    }
    if(sum < 0){
        set_flag_bit(&cpu->regs.flags, FLAG_SIGN, SET_TRUE);
    }
    else{
        set_flag_bit(&cpu->regs.flags, FLAG_SIGN, SET_FALSE);
    }
    if((uint16_t)sum > 0xFF){
        set_flag_bit(&cpu->regs.flags, FLAG_CARRY, SET_TRUE);
    }
    else {
        set_flag_bit(&cpu->regs.flags, FLAG_CARRY,SET_FALSE);
    }
    if((a>0 && b>0 && sum < 0) || (a<0 && b < 0 && sum>0)){
        set_flag_bit(&cpu->regs.flags,FLAG_OVERFLOW, SET_TRUE);
    }
    else{
        set_flag_bit(&cpu->regs.flags,FLAG_OVERFLOW,SET_FALSE);
    }

    cpu->regs.r[instr.dest] = (uint16_t)sum;
    return 0;
}
