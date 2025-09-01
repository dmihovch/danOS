#include "memory.h"

#define PROGRAM {0x00, 0x12, 0x34}

void print_memory(uint8_t*);


/*
 *
 *  LOD R0, 15
 *  LOD R1, 10
 *  ADD R1, R0
 *  STR R1, [0xFFFE]
 *
 * 0101|00|00 00001111 00000000
 * 0101|00|01 00001010 00000000
 * 0001|10|01 00000001 00000000
 * 0110|01|01 11111111 11111110
 *
 */
