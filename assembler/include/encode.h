#pragma once
#include <stdlib.h>

#include "../include/token.h"
#include <string.h>
int first_pass(tokens_t*);


typedef struct {
    char* op_name;
    int bytes;
    int reg_reg;
    int reg_imm;
    int reg_mem;
} opcode_def_t;
