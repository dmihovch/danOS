
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct {
    char** tokens;
    int size;
} tokens_t;

void tokens_free(tokens_t*);
void print_tokens(tokens_t*);

void tok_lowercase(char* tok);
