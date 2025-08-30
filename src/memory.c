#include "../include/memory.h"
#include <stdint.h>
#include <stdlib.h>





uint8_t load(uint8_t* ram, uint16_t adr){

    if(ram == NULL){
        //needs to crash
        printf("load failed!\n");
        exit(1);
    }
    return ram[adr];
}

void store(uint8_t* ram, uint16_t adr, uint8_t val){

    if(ram == NULL){
        //needs to crash
        printf("store failed!\n");
        exit(1);
    }
    printf("memory not null\n");
    print_memory(ram);
    ram[adr] = val;

}
