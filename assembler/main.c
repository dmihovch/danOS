#include <stdio.h>
#include "include/input.h"
#include "include/debug.h"
int main(int argc, char** argv){

    if(argc <= 1) {
        printf("no input files provided\n");
        return 1;
    }

    int size;
    char** tokens = tokenize_file(argv[1], &size);
    if(tokens == NULL){
        return 1;
    }

    print_tokens(tokens, size);

    free_tokens(tokens, size);


    return 0;
}
