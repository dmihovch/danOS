#include "label.h"
#include "token.h"


int asm_first_pass(tokens_t*, label_table_t*);

//actually idk
//return -1 for these if false, return the bytecode if true
int is_opcode();
int is_directive();
int is_label();
