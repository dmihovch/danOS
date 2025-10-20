#include "../include/encode.h"
#include <string.h>

//probably change name to be more specific
int first_pass(tokens_t * t, labels_t * l){
    int i;
    int sz = t->size;
    for(i = 0; i<sz; i++){

        //need to check if it is a directive or label, and then see from there what to do
        if(strcmp(t->tokens[i], ".text") == 0){
            //process program code
        }
        if(strcmp(t->tokens[i], ".data") == 0){
            //process static data
        }
        if(strcmp(t->tokens[i], ".bss") == 0){
            //process uninit data
        }



    }

}
