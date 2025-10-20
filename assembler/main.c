#include <stdio.h>
#include "include/input.h"
#include "include/debug.h"
int main(int argc, char** argv){

    if(argc <= 1) {
        printf("no input files provided\n");
        return 1;
    }

    tokens_t* t = tokenize_file(argv[1]);
    if(t == NULL){
        return 1;
    }







    print_tokens(t);

    free_tokens(t);


    return 0;
}
