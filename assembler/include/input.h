#include <stdlib.h>
#include <stdio.h>


char** tokenize_file(char*, int*);

char* create_file_buffer(FILE* );

/*
 * idx = index to free up to exclusive
 */
void free_tokens(char**, int);
