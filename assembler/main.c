#include <stdio.h>
#include "include/input.h"
#include "include/assembler.h"
int main(int argc, char** argv){

    if(argc <= 1) {
        printf("no input files provided\n");
        return 1;
    }

    tokens_t* t = tokenize_file(argv[1]);
    if(t == NULL){
        return 1;
    }


    asm_prog_t* ap = asm_prog_init();
    if(ap == NULL){
        tokens_free(t);
        return 1;
    }






    print_tokens(t);

    tokens_free(t);


    return 0;
}
