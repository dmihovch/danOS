#pragma once
#include "label.h"
#include "token.h"
#include "encode.h"
#include <string.h>
#include <stdint.h>
#define NUM_OPCODE 26

enum section {TEXT, DATA, BSS};


typedef struct {
    uint8_t* sections[3];
    int text_size;
    int text_pc;
    int data_size;
    int data_pc;
    int bss_size;
    int bss_pc;
    enum section sec;
} program_t;

int asm_first_pass(tokens_t*, label_table_t*, program_t*);
program_t* program_init();
//actually idk
//return -1 for these if false, return the bytecode if true
int is_opcode(char*);
int is_directive(char*);
int is_label(char*);

int process_opcode(tokens_t*, label_table_t*, program_t*, int);
int process_directive(tokens_t*, label_table_t*, program_t*, int);
int process_label(tokens_t*, label_table_t*, program_t*, int);
