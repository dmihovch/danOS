
#pragma once
#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
tokens_t* tokenize_file(char*);

char* create_file_buffer(FILE* );


void tok_lowercase(char*);
