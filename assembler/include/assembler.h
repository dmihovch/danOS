#include "label.h"
#include "token.h"


int asm_first_pass(tokens_t*, label_table_t*);
int isOpcode();
int isDirective();
int isLabel();
