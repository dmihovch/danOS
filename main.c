#include "include/cpu.h"

int main(int argc, char** argv){

    cpu_t* cpu = init_cpu();
    if(cpu == NULL){
        return 1;
    }
    store(cpu->ram, 0xFFFF, 0xFA);

    print_memory(cpu->ram);

    free(cpu);

    return 0;
}
