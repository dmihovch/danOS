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

    low_byte = cpu->ram[cpu->regs.pc];
    cpu->regs.pc++;
    if(cpu->regs.pc > PROGRAM_CODE_END_ADDR){
        printf("broke through program code space in ldi\n");
        return 1;
    }
    high_byte = cpu->ram[cpu->regs.pc];
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
            break;
            case IMM4:
            b = (uint16_t)instr.src_fl;
            break;
        default:
            printf("No valid mode given in op_add: 0x%x\n",instr.mode);
            return 1;
    }

    sum = a + b;
    update_flags_add(&cpu->regs.flags,(int16_t)sum, (int16_t)a, (int16_t)b);
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
            break;
        case IMM4:
            b = (uint16_t)instr.src_fl;
            break;
        default:
            printf("No valid mode given in op_sub: 0x%x\n",instr.mode);
            return 1;
    }

    dif = a - b;
    update_flags_sub(&cpu->regs.flags, (int16_t)dif, (int16_t)a, (int16_t)b);
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
            break;
        case IMM4:
            b = (uint16_t)instr.src_fl;
            break;
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
            break;
        case IMM4:
            divisor = (uint16_t)instr.src_fl;
            break;
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
            break;
        case IMM4:
            src = (uint16_t)instr.src_fl;
            break;
        default:
            printf("No valid mode given in op_and: 0x%x\n",instr.mode);
            return 1;
    }

    prod = dest & src;
    update_flags_logic(&cpu->regs.flags, (int16_t)prod);
    cpu->regs.r[instr.dest] = prod;
    return 0;
}

int op_or(cpu_t * cpu, instr_t instr){
    uint16_t prod;
    uint16_t dest;
    uint16_t src;
    dest = cpu->regs.r[instr.dest];
    switch(instr.mode){
        case REG:
            src = cpu->regs.r[instr.src_fl];
            break;
        case IMM4:
            src = (uint16_t)instr.src_fl;
            break;
        default:
            printf("No valid mode given in op_or: 0x%x\n", instr.mode);
            return 1;
    }

    prod = dest | src;
    update_flags_logic(&cpu->regs.flags, (int16_t)prod);
    cpu->regs.r[instr.dest] = prod;
    return 0;
}

int op_xor(cpu_t *cpu, instr_t instr){
    uint16_t prod;
    uint16_t dest;
    uint16_t src;
    dest = cpu->regs.r[instr.dest];
    switch(instr.mode){
        case REG:
            src = cpu->regs.r[instr.src_fl];
            break;
        case IMM4:
            src = (uint16_t)instr.src_fl;
            break;
        default:
            printf("No valid mode given in op_xor: 0x%x\n",instr.mode);
            return 1;
    }

    prod = dest ^ src;
    update_flags_logic(&cpu->regs.flags, (int16_t)prod);
    cpu->regs.r[instr.dest] = prod;
    return 0;
}

int op_not(cpu_t* cpu, instr_t instr){
    uint16_t prod = ~(cpu->regs.r[instr.dest]);
    if(prod == 0){
        set_flag_bit(&cpu->regs.flags, FLAG_ZERO, SET_TRUE);
    }
    else{
        set_flag_bit(&cpu->regs.flags, FLAG_ZERO, SET_FALSE);
    }
    if((int16_t)prod < 0){
        set_flag_bit(&cpu->regs.flags, FLAG_SIGN, SET_TRUE);
    }
    else{
        set_flag_bit(&cpu->regs.flags, FLAG_SIGN, SET_FALSE);
    }
    set_flag_bit(&cpu->regs.flags, FLAG_CARRY, SET_FALSE);
    set_flag_bit(&cpu->regs.flags, FLAG_OVERFLOW, SET_FALSE);
    cpu->regs.r[instr.dest] = prod;
    return 0;

}

int op_shl(cpu_t *cpu, instr_t instr){

    uint16_t prod= cpu->regs.r[instr.dest];
    uint16_t orig_val = prod;
    uint16_t bits_sh= instr.src_fl;
    uint16_t pushed_out = (prod >> (16 - bits_sh)) & 0b0000000000000001;
    prod <<= bits_sh;
    update_flags_bitshift(&cpu->regs.flags, prod, bits_sh, pushed_out, orig_val);

    cpu->regs.r[instr.dest] = prod;
    return 0;

}

int op_shr(cpu_t *cpu, instr_t instr){
    uint16_t prod = cpu->regs.r[instr.dest];
    uint16_t orig_val = prod;
    uint16_t bits_sh = instr.src_fl;
    uint16_t pushed_out = ((prod << (16-bits_sh)) >> 15) & 0b0000000000000001; //yikers
    prod >>= bits_sh;
    update_flags_bitshift(&cpu->regs.flags, prod, bits_sh, pushed_out, orig_val);

    cpu->regs.r[instr.dest] = prod;
    return 0;
}

int op_load(cpu_t *cpu, instr_t instr){
    cpu->regs.r[instr.dest] = (uint16_t)cpu->ram[cpu->regs.r[instr.src_fl]] | ((uint16_t)cpu->ram[cpu->regs.r[instr.src_fl]] << 8);
    return 0;
}

int op_stor(cpu_t *cpu, instr_t instr){
    cpu->ram[cpu->regs.r[instr.dest]] = cpu->regs.r[instr.src_fl];
    cpu->ram[cpu->regs.r[instr.dest]++] = cpu->regs.r[instr.src_fl] >> 8;
    return 0;
}

int op_comp(cpu_t *cpu, instr_t instr){
    uint16_t dif;
    uint16_t a = cpu->regs.r[instr.dest];
    uint16_t b;
    switch(instr.mode){
        case REG:
            b = cpu->regs.r[instr.src_fl];
            break;
        case IMM4:
            b = instr.src_fl;
            break;
        default:
            printf("No valid mode given in op_comp: 0x%x\n",instr.mode);
            return 1;
    }
    dif = a - b;
    update_flags_sub(&cpu->regs.flags, (int16_t)dif, (int16_t)a, (int16_t)b);
    return 0;
}

int op_jump(cpu_t *cpu, instr_t instr){
    uint16_t addr;
    uint16_t offset;
    switch(instr.mode){
        case REG:
            offset = cpu->regs.r[instr.dest];
            break;
        case MEM:
            offset = (uint16_t)cpu->ram[cpu->regs.r[instr.dest]] | ((uint16_t)cpu->ram[cpu->regs.r[instr.dest]++]<<8);
            break;
        case LABEL:
            //assembler will emit the correct jump statement based on offset
            offset =(instr.dest << 8) + instr.src_fl ;
            break;
        default:
            printf("No valid mode given in op_jump: 0x%x\n",instr.mode);
            return 1;
    }
    addr = cpu->regs.pc + offset;
    if(addr>PROGRAM_CODE_END_ADDR){
        printf("op_jump caused program counter to pass program code space: 0x%x\n",addr);
        return 1;
    }
    cpu->regs.pc = addr;
    return 0;
}

int op_jg(cpu_t *cpu, instr_t instr){
    uint16_t flag = cpu->regs.flags;
    if(!check_flag(flag, FLAG_ZERO) && !check_flag(flag, FLAG_SIGN)){
        op_jump(cpu,instr);
    }
    return 0;
}

int op_jl(cpu_t *cpu, instr_t instr){
    uint16_t flag = cpu->regs.flags;
    if(check_flag(flag,FLAG_SIGN)){
        op_jump(cpu,instr);
    }
    return 0;
}

int op_jnz(cpu_t *cpu, instr_t instr){
    uint16_t flag = cpu->regs.flags;
    if(!check_flag(flag,FLAG_ZERO)){
        op_jump(cpu, instr);
    }
    return 0;
}

int op_jz(cpu_t *cpu, instr_t instr){
    uint16_t flag = cpu->regs.flags;
    if(check_flag(flag, FLAG_ZERO)){
        op_jump(cpu, instr);
    }
    return 0;
}

int op_push(cpu_t *cpu, instr_t instr){
    cpu->regs.sp -= 2;
    cpu->ram[cpu->regs.sp] = cpu->regs.r[instr.dest];
    cpu->ram[cpu->regs.sp-1] = cpu->regs.r[instr.dest] >> 8;
    if(cpu->regs.sp < STACK_END_ADDR){
        printf("stack overflowed\n");
        return 1;
    }
    return 0;
}

int op_pop(cpu_t *cpu, instr_t instr){
    cpu->regs.r[instr.dest] = (uint16_t)cpu->ram[cpu->regs.sp] | (uint16_t)cpu->ram[cpu->regs.sp+1]<<8;
    cpu->regs.sp += 1;
    if(cpu->regs.sp > STACK_START_ADDR){
        printf("stack underflowed\n");
        return 1;
    }
    return 0;
}

int op_call(cpu_t *cpu, instr_t instr){
    cpu->regs.sp -= 2;
    cpu->ram[cpu->regs.sp] = cpu->regs.pc;
    cpu->ram[cpu->regs.sp+1] = cpu->regs.pc >> 8;
    if(cpu->regs.sp < STACK_END_ADDR){
        printf("stack underflowed in op_call\n");
        return 1;
    }
    return op_jump(cpu,instr);
}

int op_ret(cpu_t *cpu, instr_t instr){
    cpu->regs.pc = ((uint16_t)cpu->ram[cpu->regs.sp] << 8) | (uint16_t)cpu->ram[cpu->regs.sp-1];
    cpu->regs.sp += 2;
    if(cpu->regs.sp > STACK_START_ADDR){
        printf("stack underflowed in op_ret\n");
        return 1;
    }
    return 0;
}
