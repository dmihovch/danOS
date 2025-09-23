#include "include/cpu.h"

int main(int argc, char** argv){

    //this is now out of date, need to change into our new ISA format
    uint8_t program[] = {0x91,0x92,0x93,0xA4,0xD5,0xF6,0x27,0x38,0x49,0x11,0x22,0x33};

    cpu_t* cpu = init_cpu();
    if(cpu == NULL){
        return 1;
    }
    store(cpu->ram, 0xFFFF, 0xFA);

    load_program(cpu->ram, &cpu->regs.pc, program, 12);
    print_memory_slice(cpu->ram, PROGRAM_CODE_START_ADDR, 32);
    printf("%d\n",cpu->regs.pc);


    for(int i = 0; i<6; i++){
        instr_t instr = format_instruction(fetch_instruction(cpu->ram, &cpu->regs.pc));
        printf("0x%x, 0x%x\n", instr.opcode + instr.mode, instr.dest + instr.src_fl);
    }


    printf("\n%d\n",cpu->regs.pc);
    free(cpu);

    return 0;
}
