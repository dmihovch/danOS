#include "../include/utils.h"

uint8_t get_dest_reg(uint8_t operands){
    return 0;
}

int set_flag_bit(uint16_t* reg, int flag, int val){
    if(SET_TRUE){
       *reg |= (1 << flag);
    }
    if(SET_FALSE){
        *reg &= ~(1 << flag);
    }
}
