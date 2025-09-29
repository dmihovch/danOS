#include "../include/utils.h"
#include "../include/ops.h"
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
    return 0;
}

int update_flags_add(uint16_t* flag, int16_t sum, int16_t a, int16_t b){

        if(sum == 0){
            set_flag_bit(flag, FLAG_ZERO, SET_TRUE);
        }
        else{
            set_flag_bit(flag, FLAG_ZERO, SET_FALSE);
        }
        if(sum < 0){
            set_flag_bit(flag, FLAG_SIGN, SET_TRUE);
        }
        else{
            set_flag_bit(flag, FLAG_SIGN, SET_FALSE);
        }
        if((uint16_t)sum > 0xFF){
            set_flag_bit(flag, FLAG_CARRY, SET_TRUE);
        }
        else {
            set_flag_bit(flag, FLAG_CARRY,SET_FALSE);
        }
        if((a>0 && b>0 && sum < 0) || (a<0 && b < 0 && sum>0)){
            set_flag_bit(flag,FLAG_OVERFLOW, SET_TRUE);
        }
        else{
            set_flag_bit(flag,FLAG_OVERFLOW,SET_FALSE);
        }

    return 0;
}

int update_flags_sub(uint16_t * flag, int16_t dif, int16_t a, int16_t b){
        if(dif == 0){
            set_flag_bit(flag, FLAG_ZERO, SET_TRUE);
        }
        else{
            set_flag_bit(flag, FLAG_ZERO, SET_FALSE);
        }
        if(dif < 0){
            set_flag_bit(flag, FLAG_SIGN, SET_TRUE);
        }
        else{
            set_flag_bit(flag, FLAG_SIGN, SET_FALSE);
        }
        if((uint16_t)b > (uint16_t)a){
            set_flag_bit(flag, FLAG_CARRY, SET_TRUE);
        }
        else{
            set_flag_bit(flag, FLAG_CARRY, SET_FALSE);
        }
        if((a^b)>=0 && (a^dif)<0){
            set_flag_bit(flag, FLAG_OVERFLOW, SET_TRUE);
        }
        else{
            set_flag_bit(flag, FLAG_OVERFLOW, SET_FALSE);
        }
    return 0;
}

int update_flags_and(uint16_t *flag, int16_t prod, int16_t a, int16_t b){

    if(prod == 0){
        set_flag_bit(flag,FLAG_ZERO,SET_TRUE);
    }
    else{
        set_flag_bit(flag,FLAG_ZERO,SET_FALSE);
    }
    if(prod < 0){
        set_flag_bit(flag,FLAG_SIGN,SET_TRUE);
    }
    else{
        set_flag_bit(flag,FLAG_SIGN,SET_FALSE);
    }
    set_flag_bit(flag,FLAG_CARRY,SET_FALSE);
    set_flag_bit(flag,FLAG_OVERFLOW, SET_FALSE);
    return 0;
}
