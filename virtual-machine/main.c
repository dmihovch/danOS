#include "include/cpu.h"

int main(int argc, char** argv){


    uint8_t program[] = {
    0x0B, 0x10, 0x00, 0x0A, // LDI R1, 10
    0x0B, 0x20, 0x00, 0x14, // LDI R2, 20
    0x3C, 0x12,             // COMP R1, R2
    0x0B, 0x40, 0x00, 0x12, // LDI R4, 18 (address of 'less' label)
    0x52, 0x40,             // JL R4
    0x04, 0x31,             // MOV R3, R1
    0x0B, 0x40, 0x00, 0x16, // LDI R4, 22 (address of 'end' label)
    0x42, 0x40,             // JUMP R4
    0x04, 0x32,             // less: MOV R3, R2
    0x64, 0x00              // end: HALT
    };
    cpu_t* cpu = init_cpu();
    if(cpu == NULL){
        return 1;
    }
    store(cpu->ram, 0xFFFF, 0xFA);

    load_program(cpu, program, 28);
    print_memory_slice(cpu->ram, PROGRAM_CODE_START_ADDR, 32);
    printf("%d\n",cpu->regs.pc);



    int ret_code = 0;
    while(!ret_code){

        instr_t instr = format_instruction(fetch_instruction(cpu->ram, &cpu->regs.pc));
        ret_code = execute_instruction(cpu, instr);

    }

    print_regs(cpu);
    printf("\n%d\n",cpu->regs.pc);
    free(cpu);

    return 0;
}
