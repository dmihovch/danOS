#include "../include/utils.h"

uint8_t get_register(uint8_t reg_flags){

        return reg_flags >> 5;
}
