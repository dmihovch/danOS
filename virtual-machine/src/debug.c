#include "../include/debug.h"



void print_memory(uint8_t* ram){

    if(ram == NULL){
        //needs to crash
        return;
    }

    for(int i = 0; i<MEMORY_CAP_BYTES; i++){
        if(i % 32 == 0){
            printf("0x%x\n",ram[i]);
        } else {
            printf("0x%x ",ram[i]);
        }

    }
    printf("\n");

}

void print_memory_slice(uint8_t * ram, uint16_t start_addr, uint16_t end_addr){
    if(ram == NULL){
        return;
    }
    for(int i = start_addr; i<end_addr; i++){
        if(i %32 == 0 && i != 0){
            printf("0x%x\n",ram[i]);
        } else {
            printf("0x%x ", ram[i]);
        }
    }
    printf("\n");
}
