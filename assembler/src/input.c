#include "../include/input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char** tokenize_file(char* fn, int* szp){

    const char* delims = ";, \t\n";

    FILE *fp = fopen(fn,"r");
    if(fp == NULL){
        return NULL;
    }

    char* buf = create_file_buffer(fp);
    fclose(fp);
    if(buf == NULL){
        return NULL;
    }

    char** tokens = NULL;
    int count = 0;

    char* tok = strtok(buf, delims);
    while(tok){
        char** tmp = realloc(tokens,(count+1)*(sizeof(char*)));
        if(tmp == NULL){
            free(buf);
            if(tokens != NULL){
                free_tokens(tokens,count);
            }
            return NULL;
        }
        tokens = tmp;
        tokens[count] = strdup(tok);
        if(tokens[count] == NULL){
           free_tokens(tokens, count);
           free(buf);
        }
        count++;
        tok = strtok(NULL, delims);
    }

    *szp = count;

    return tokens;
}

char* create_file_buffer(FILE* fp){
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char* buf = malloc(size+1);
    if(buf == NULL){
        return NULL;
    }
    fread(buf, 1, size, fp);
    buf[size] = '\0';


    return buf;
}

void free_tokens(char ** tokens, int idx){
    for(int i = 0; i<idx; i++){
        free(tokens[i]);
    }
    free(tokens);
}
