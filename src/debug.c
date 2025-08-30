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
