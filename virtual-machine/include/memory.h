#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#define MEMORY_CAP_BYTES 65536 //64KB



/*
 * p1: memory block
 * p2: uint16 mem address
 * RET: uint8 mem value
 */
uint8_t load(uint8_t*, uint16_t);

/*
 * p1: memory block
 * p2: uint16 mem address
 * p3: uint8 mem value
 *
 */
void store(uint8_t*, uint16_t, uint8_t);


void print_memory(uint8_t*);
