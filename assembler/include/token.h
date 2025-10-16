#include <stdlib.h>
#include <stdio.h>


typedef struct {
    char** tokens;
    int size;
} tokens_t;

void free_tokens(tokens_t*);
void print_tokens(tokens_t*);
