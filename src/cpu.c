#include "../include/cpu.h"
#include <stdint.h>

cpu_t* init_cpu(){
    return calloc(1,sizeof(cpu_t));
}

int load_program(uint8_t* ram, uint16_t* pc, uint8_t* program, int plen){

    for(int i = 0; i<plen; i++){
        ram[*pc] = program[i];
        pc++;
    }

    return 0;
}
