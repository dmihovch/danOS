#include "../include/memory.h"


uint8_t load(memory_t* mem, uint16_t adr){

    if(mem == NULL){
        //needs to crash
        exit(1);
    }
    return mem->ram[adr];
}

void store(memory_t * mem, uint16_t adr, uint8_t val){

    if(mem == NULL){
        //needs to crash
        exit(1);
    }
    mem->ram[adr] = val;

}
