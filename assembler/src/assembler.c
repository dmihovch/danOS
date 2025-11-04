#include "../include/assembler.h"
#include <string.h>


program_t* program_init(){
   return NULL;
}


int asm_first_pass(tokens_t* t, label_table_t* lt, program_t* p){
    //reg, imm, mem
    opcode_def_t opcodes[NUM_OPCODE] = {
        {"nop", 2, 0, 0, 0},
        {"mov", 2, 1, 1, 0},
        {"ldi", 4, 0, 1, 0},
        {"add", 2, 1, 1, 0},
        {"sub", 2, 1,1,0},
        {"mul", 2, 1,1,0},
        {"div", 2,1,1,0},
        {"and", 2,1,1,0},
        {"or", 2,1,1,0},
        {"xor", 2, 1,1,0},
        {"not", 2, 1, 0, 0},
        {"shl", 2, 0, 1,0},
        {"shr", 2,0,1,0},
        {"load", 2, 0,0,1},
        {"stor", 2, 0,0,1},
        {"comp", 2,1,1,0},
        {"jump", 2,0,0,1},
        {"jz", 2,0,0,1},
        {"jnz", 2,0,0,1},
        {"jg", 2,0,0,1},
        {"jl", 2,0,0,1},
        {"call",2,0,0,1},
        {"ret", 2,0,0,0},
        {"push", 2, 1, 0,0}, //maybe need to address
        {"pop", 2, 1,0,0},
        {"halt", 2, 0,0,0}
    };

    int i, j, tok_opcode, tok_directive, tok_label, found, tok_len;
    char* tok;
    int tsz = t->size;
    for(i = 0; i<tsz; i++){
        found = 0;

        tok = t->tokens[i];
        tok_len = strlen(tok);

        //directive
        if(!strcmp(".data", tok)){
            p->sec = DATA;
            found = 1;
        }
        if(!strcmp(".bss", tok)){
            p->sec = BSS;
            found = 1;
        }
        if(!strcmp(".text",tok)){
            p->sec = TEXT;
            found = 1;
        }
        //label
        if(tok[tok_len-1] == ':'){
            found = 1;
        }

        if(found){
            continue;
        }


        //opcode

        for(j = 0; j<NUM_OPCODE; j++){
            if(!strcmp(opcodes[j].op_name, tok)){
                p->text_pc += opcodes[j].bytes;
                found = 1;
                break;
            }
        }
        if(found){
            continue;
        }







    }
    return 0;
}
