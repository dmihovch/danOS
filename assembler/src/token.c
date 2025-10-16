#include "../include/token.h"


void free_tokens(tokens_t* t){
    for(int i = 0; i<t->size; i++){
        free(t->tokens[i]);
    }
    free(t->tokens);
    free(t);
}

void print_tokens(tokens_t* t){

    for(int i = 0; i<t->size; i++){
        if(i == t->size-1){
            printf("[%s]\n",t->tokens[i]);
        }
        else{
            printf("[%s],",t->tokens[i]);
        }

    }

}
