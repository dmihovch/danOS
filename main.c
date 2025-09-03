#include "include/cpu.h"

int main(int argc, char** argv){


    uint8_t program[] = {0x50, 0x00, 0x0F, 0x51, 0x00, 0x0A, 0x19, 0x00, 0x01, 0x65, 0xFF, 0xFE};

    cpu_t* cpu = init_cpu();
    if(cpu == NULL){
        return 1;
    }
    store(cpu->ram, 0xFFFF, 0xFA);

    load_program(cpu->ram, &cpu->regs.pc, program, 12);
    print_memory_slice(cpu->ram, PROGRAM_CODE_START_ADDR, 32);
    printf("%d\n",cpu->regs.pc);

    uint8_t instr;

    for(int i = 0; i<12; i++){
        instr = fetch_instruction(cpu->ram,&cpu->regs.pc);
        printf("0x%x\n",instr);
    }
    printf("%d\n",cpu->regs.pc);
    free(cpu);

    return 0;
}
