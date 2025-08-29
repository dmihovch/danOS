#include <stdint.h>
#define MEMORY_CAP_BYTES 65536 //64KB


/*
 * uint8_t ram: memory array, size defined by MEMORY_CAP_BYTES
 * uint16_t pc: program counter
 * uint16_t sp: stack pointer
 */
typedef struct memory_t{

  uint8_t ram[MEMORY_CAP_BYTES];
  uint16_t pc;
  uint16_t sp;

} memory_t;

/*
 * p1: memory block
 * p2: uint16 mem address
 * RET: uint8 mem value
 */
uint8_t load(memory_t*, uint16_t);

/*
 * p1: memory block
 * p2: uint16 mem address
 * p3: uint8 mem value
 *
 */
void store(memory_t*, uint16_t, uint8_t);
