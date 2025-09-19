#include "include/cpu.h"

int main(int argc, char** argv){

    //this is now out of date, need to change into our new ISA format
    uint8_t program[] = {};

    cpu_t* cpu = init_cpu();
    if(cpu == NULL){
        return 1;
    }
    store(cpu->ram, 0xFFFF, 0xFA);

    load_program(cpu->ram, &cpu->regs.pc, program, 12);
    print_memory_slice(cpu->ram, PROGRAM_CODE_START_ADDR, 32);
    printf("%d\n",cpu->regs.pc);



    printf("\n%d\n",cpu->regs.pc);
    free(cpu);

    return 0;
}
