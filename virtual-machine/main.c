#include "include/cpu.h"

int main(int argc, char** argv){
    uint8_t program[] = {
            // LDI R1, 5 (0x0005)
            0x09, 0x10,  // Instruction: Opcode 0x02 (LDI), Mode 0x01 (immediate), Dest R1 (0x1), unused (0x0)
            0x00, 0x05,  // Immediate value: 5

            // LDI R2, 7 (0x0007)
            0x09, 0x20,  // Instruction: Opcode 0x02 (LDI), Mode 0x01 (immediate), Dest R2 (0x2), unused (0x0)
            0x00, 0x07,  // Immediate value: 7

            // ADD R3, R1 (R3 = 0 + 5 = 5)
            0x0C, 0x31,  // Instruction: Opcode 0x03 (ADD), Mode 0x00 (reg-reg), Dest R3 (0x3), Src R1 (0x1)

            // ADD R3, R2 (R3 = 5 + 7 = 12)
            0x0C, 0x32,  // Instruction: Opcode 0x03 (ADD), Mode 0x00 (reg-reg), Dest R3 (0x3), Src R2 (0x2)

            // HALT
            0x64, 0x00   // Instruction: Opcode 0x19 (HALT), rest don't matter
        };



    cpu_t* cpu = init_cpu();
    if(cpu == NULL){
        return 1;
    }
    store(cpu->ram, 0xFFFF, 0xFA);

    load_program(cpu, program, 14);
    print_memory_slice(cpu->ram, PROGRAM_CODE_START_ADDR, 32);
    printf("%d\n",cpu->regs.pc);



    int ret_code = 0;
    int count = 0;
    while(!ret_code && count < 20){


        instr_t instr = format_instruction(fetch_instruction(cpu));
        printf("executing: 0x%x\n",instr.opcode);
        ret_code = execute_instruction(cpu, instr);
        count++;
    }

    print_regs(cpu);
    printf("\n%d\n",cpu->regs.pc);
    free(cpu);

    return 0;
}
