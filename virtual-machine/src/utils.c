#include "../include/utils.h"
#include "../include/ops.h"

int set_flag_bit(uint16_t* reg, int flag, int val){
    if(val == SET_TRUE){
       *reg |= (1 << flag);
    }
    if(val == SET_FALSE){
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

int update_flags_bitshift(uint16_t *flag, uint16_t prod, uint16_t bits_sh, uint16_t pushed_out, uint16_t orig_val){
    if(prod == 0){
        set_flag_bit(flag, FLAG_ZERO, SET_TRUE);
    }
    else{
        set_flag_bit(flag,FLAG_ZERO,SET_FALSE);
    }
    if(bits_sh == 1){
        //if a 1 bit shift, sets overflow flag to the prior MSB
        set_flag_bit(flag, FLAG_OVERFLOW, orig_val>>15);
    }
    //sets sign bit to MSB
    set_flag_bit(flag, FLAG_SIGN, prod>>15);
    set_flag_bit(flag, FLAG_CARRY, pushed_out);
    return 0;
}

int check_flag(uint16_t flag, uint16_t bit){
    return (flag >> bit) & 0b0000000000000001;
}
