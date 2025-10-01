#include "../include/ops.h"
#include <stdint.h>

cpu_t* init_cpu(){
    cpu_t* c = calloc(1,sizeof(cpu_t));
    if(c == NULL){
        return NULL;
    }
    c->regs.pc = PROGRAM_CODE_START_ADDR;
    c->regs.sp = STACK_START_ADDR;
    c->regs.sfp = STACK_START_ADDR;
    c->regs.flags = 0;
    return c;
}


int load_program(cpu_t* cpu, uint8_t* program, int plen){


    uint16_t pc_val = cpu->regs.pc;
    cpu->regs.psa = pc_val;
    //purposely not mutating the value @pc
    for(int i = 0; i<plen; i++){
        cpu->ram[pc_val] = program[i];
        pc_val++;
        if(pc_val > PROGRAM_CODE_END_ADDR){
            printf("exceeded program code memory region\n");
            return 1;
            //crash?
        }
    }

    return 0;
}



uint16_t fetch_instruction(cpu_t* cpu){


    uint16_t raw_instr;
    raw_instr = cpu->ram[cpu->regs.pc];
    cpu->regs.pc++;

    raw_instr <<= 8;
    raw_instr |= cpu->ram[cpu->regs.pc];

    cpu->regs.pc++;

    return raw_instr;
}


instr_t format_instruction(uint16_t raw_instr){
    instr_t instr;
    instr.opcode= raw_instr >> 10;
    instr.mode = (raw_instr >> 8) & 0b00000011;
    instr.dest = (raw_instr >> 4) & 0b00001111;
    instr.src_fl = raw_instr & 0b00001111;
    return instr;
}


int execute_instruction(cpu_t* cpu, instr_t instr){

    switch(instr.opcode){
        case 0x00:
            return 0; //NOP
        case 0x01:
            return op_mov(cpu, instr);
        case 0x02:
            return op_ldi(cpu, instr);
        case 0x03:
            return op_add(cpu,instr);
        case 0x04:
            return op_sub(cpu, instr);
        case 0x05:
            return op_mul(cpu, instr);
        case 0x06:
            return op_div(cpu, instr);
        case 0x07:
            return op_and(cpu, instr);
        case 0x08:
            return op_or(cpu, instr);
        case 0x09:
            return op_xor(cpu, instr);
        case 0x0A:
            return op_not(cpu, instr);
        case 0x0B:
            return op_shl(cpu, instr);
        case 0x0C:
            return op_shr(cpu, instr);
        case 0x0D:
            return op_load(cpu, instr);
        case 0x0E:
            return op_stor(cpu, instr);
        case 0x0F:
            return op_comp(cpu, instr);
        case 0x10:
            return op_jump(cpu, instr);
        case 0x11:
            return op_jz(cpu, instr);
        case 0x12:
            return op_jnz(cpu, instr);
        case 0x13:
            return op_jg(cpu, instr);
        case 0x14:
            return op_jl(cpu, instr);
        case 0x15:
            return op_call(cpu, instr);
        case 0x16:
            return op_ret(cpu, instr);
        case 0x17:
            return op_push(cpu, instr);
        case 0x18:
            return op_pop(cpu, instr);
        case 0x19:
            return 1; //halt
        default:
            printf("provided opcode not defined in ISA: 0x%x\n", instr.opcode);
            return 1;
    }


    return 0;
}

void print_regs(cpu_t *cpu){
    for(int i = 0; i<16; i++){
        printf("R%d: %d\n",i,cpu->regs.r[i]);
    }

}
