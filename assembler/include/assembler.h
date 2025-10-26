#include "label.h"
#include "token.h"
#include <stdint.h>

typedef struct {

    uint8_t* bytes;
    int size;
    int pc;

} asm_prog_t;

int asm_first_pass(tokens_t*, label_table_t*, asm_prog_t*);
asm_prog_t* asm_prog_init();
//actually idk
//return -1 for these if false, return the bytecode if true
int is_opcode();
int is_directive();
int is_label();
