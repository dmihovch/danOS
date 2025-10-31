
#pragma once
#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
tokens_t* tokenize_file(char*);

char* create_file_buffer(FILE* );
