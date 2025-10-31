#include "../include/assembler.h"

asm_prog_t* asm_prog_init(){
   return NULL;
}


int asm_first_pass(tokens_t* t, label_table_t* lt, asm_prog_t* ap){



    int i, tok_opcode, tok_directive, tok_label;
    int tsz = t->size;
    for(i = 0; i<tsz; i++){

    }
    return 0;
}


int process_label(tokens_t * t, label_table_t * lt, asm_prog_t * ap, int i){
    char* tok = t->tokens[i];


}
