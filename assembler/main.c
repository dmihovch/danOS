#include <stdio.h>

int main(int argc, char** argv){

    if(argc <= 1) {
        printf("no input files provided\n");
        return 1;
    }

    FILE* input = fopen(argv[1],"r");
    if(input == NULL){
        perror("error opening file\n");
        return 1;
    }




    return 0;
}
