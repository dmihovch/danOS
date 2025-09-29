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

    uint16_t sum;
    uint16_t a;
    uint16_t b;
    a = cpu->regs.r[instr.dest];
    switch(instr.mode){
        case REG:
            b = cpu->regs.r[instr.src_fl];
        case IMM4:
            b = (uint16_t)instr.src_fl;
        default:
            printf("No valid mode given in op_add: 0x%x\n",instr.mode);
            return 1;
    }

    update_flags_add(&cpu->regs.flags,(int16_t)sum, (int16_t)a, (int16_t)b);
    sum = a + b;
    cpu->regs.r[instr.dest] = sum;
    return 0;
}

int op_sub(cpu_t * cpu, instr_t instr){
    uint16_t dif;
    uint16_t a;
    uint16_t b;
    a = cpu->regs.r[instr.dest];
    switch(instr.mode){
        case REG:
            b = cpu->regs.r[instr.src_fl];
        case IMM4:
            b = (uint16_t)instr.src_fl;
        default:
            printf("No valid mode given in op_sub: 0x%x\n",instr.mode);
            return 1;
    }
    update_flags_sub(&cpu->regs.flags, (int16_t)dif, (int16_t)a, (int16_t)b);
    dif = a - b;
    cpu->regs.r[instr.dest] = dif;
    return 0;
}

int op_mul(cpu_t * cpu, instr_t instr){
    uint16_t prod;
    uint16_t a;
    uint16_t b;
    a = cpu->regs.r[instr.dest];
    switch(instr.mode){
        case REG:
            b = cpu->regs.r[instr.src_fl];
        case IMM4:
            b = (uint16_t)instr.src_fl;
        default:
            printf("No valid mode given in op_mul: 0x%x\n",instr.mode);
            return 1;

    }
    prod = a*b;
    cpu->regs.r[instr.dest] = prod;

    return 0;
}

int op_div(cpu_t * cpu, instr_t instr){
    uint16_t quo;
    uint16_t dividend;
    uint16_t divisor;
    dividend = cpu->regs.r[instr.dest];
    switch(instr.mode){
        case REG:
            divisor = cpu->regs.r[instr.src_fl];
        case IMM4:
            divisor = (uint16_t)instr.src_fl;
        default:
            printf("No valid mode given in op_div: 0x%x\n", instr.mode);
            return 1;
    }

    quo = (uint16_t)(dividend/divisor);
    cpu->regs.r[instr.dest] = quo;

    return 0;
}

int op_and(cpu_t *cpu, instr_t instr){
    uint16_t prod;
    uint16_t dest;
    uint16_t src;
    dest = cpu->regs.r[instr.dest];
    switch(instr.mode){
        case REG:
            src = cpu->regs.r[instr.src_fl];
        case IMM4:
            src = (uint16_t)instr.src_fl;
        default:
            //print
            return 1;
    }
   //update flags
    prod = dest & src;
    cpu->regs.r[instr.dest] = prod;
    return 0;
}
