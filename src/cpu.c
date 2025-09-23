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


int load_program(uint8_t* ram, uint16_t* pc, uint8_t* program, int plen){
    if(ram == NULL || program == NULL || pc == NULL){
        //needs to crash
        exit(1);

    }


    uint16_t pc_val = *pc;
    //purposely not mutating the value @pc
    for(int i = 0; i<plen; i++){
        ram[pc_val] = program[i];
        pc_val++;
        if(pc_val > PROGRAM_CODE_END_ADDR){
            printf("exceeded program code memory region\n");
            return 1;
            //crash?
        }
    }

    return 0;
}



uint16_t fetch_instruction(uint8_t* ram, uint16_t* pc){

    if(ram == NULL || pc == NULL){
        //needs to crash
        printf("ram or pc null in fetch_instruction");
        exit(1);
    }

    uint16_t raw_instr;
    raw_instr = ram[*pc];
    (*pc)++;

    raw_instr <<= 8;
    raw_instr |= ram[*pc];
    (*pc)++;

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





    return 0;
}
