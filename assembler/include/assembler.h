#pragma once
#include "label.h"
#include "token.h"
#include "encode.h"
#include <string.h>
#include <stdint.h>
#define NUM_OPCODE 26

typedef struct {

    uint8_t* bytes;
    int size;
    int pc;

} asm_prog_t;

int asm_first_pass(tokens_t*, label_table_t*, asm_prog_t*);
asm_prog_t* asm_prog_init();
//actually idk
//return -1 for these if false, return the bytecode if true
int is_opcode(char*);
int is_directive(char*);
int is_label(char*);

int process_opcode(tokens_t*, label_table_t*, asm_prog_t*, int);
int process_directive(tokens_t*, label_table_t*, asm_prog_t*, int);
int process_label(tokens_t*, label_table_t*, asm_prog_t*, int);
