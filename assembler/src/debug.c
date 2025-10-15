#include "../include/debug.h"

void print_tokens(char ** tokens, int size){

    for(int i = 0; i<size; i++){
        if(i == size-1){
            printf("[%s]\n",tokens[i]);
        }
        else{
            printf("[%s],",tokens[i]);
        }

    }

}
