#include "../include/input.h"




tokens_t* tokenize_file(char* fn){



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

    tokens_t* t = calloc(1,sizeof(tokens_t));
    char* tok = strtok(buf, delims);
    while(tok){
        char** tmp = realloc(t->tokens,(t->size+ 1)*(sizeof(char*)));
        if(tmp == NULL){
            free(buf);
            if(t->tokens != NULL){
                tokens_free(t);
            }
            return NULL;
        }
        t->tokens = tmp;
        t->tokens[t->size] = strdup(tok);
        if(t->tokens[t->size] == NULL){
           tokens_free(t);
           free(buf);
        }
        t->size++;
        tok = strtok(NULL, delims);
    }


    return t;
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
