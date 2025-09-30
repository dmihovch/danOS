#include <stdint.h>

#define FLAG_ZERO 0
#define FLAG_SIGN 1
#define FLAG_CARRY 2
#define FLAG_OVERFLOW 3
#define SET_TRUE 1
#define SET_FALSE 0
int set_flag_bit(uint16_t*, int ,int);
int update_flags_add(uint16_t*, int16_t, int16_t, int16_t);
int update_flags_sub(uint16_t*, int16_t, int16_t, int16_t);
int update_flags_logic(uint16_t*, int16_t, int16_t, int16_t);
int update_flags_bitshift(uint16_t*, uint16_t, uint16_t, uint16_t,uint16_t);
int check_flag(uint16_t, uint16_t);
