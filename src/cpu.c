#include "../include/cpu.h"
#include <stdint.h>

cpu_t* init_cpu(){
    cpu_t* c = calloc(1,sizeof(cpu_t));
    if(c == NULL){
        return NULL;
    }
    c->regs.pc = PROGRAM_CODE_START_ADDR;
    c->regs.sp = STACK_START_ADDR;
    return c;
}

int load_program(uint8_t* ram, uint16_t* pc, uint8_t* program, int plen){
    if(ram == NULL || program == NULL || pc == NULL){
        //needs to crash
        exit(1);

    }


    uint16_t pc_val = *pc;

    for(int i = 0; i<plen; i++){
        ram[pc_val] = program[i];
        pc_val++;
    }

    return 0;
}



uint8_t fetch_instruction(uint8_t* ram, uint16_t* pc){

    if(ram == NULL || pc == NULL){
        //needs to crash
        printf("ram or pc null in fetch_instruction");
        exit(1);
    }

    uint8_t instruction = ram[*pc];
    (*pc)++;
    return instruction;
}
