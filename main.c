#include "include/cpu.h"

int main(int argc, char** argv){

    //this is now out of date, need to change into our new ISA format
    uint8_t program[] = {0x50, 0x00, 0x0F, 0x51, 0x00, 0x0A, 0x19, 0x00, 0x01, 0x65, 0xFF, 0xFE};

    cpu_t* cpu = init_cpu();
    if(cpu == NULL){
        return 1;
    }
    store(cpu->ram, 0xFFFF, 0xFA);

    load_program(cpu->ram, &cpu->regs.pc, program, 12);
    print_memory_slice(cpu->ram, PROGRAM_CODE_START_ADDR, 32);
    printf("%d\n",cpu->regs.pc);

    uint32_t instr;

    for(int i = 0; i<3; i++){
        instr = fetch_instruction(cpu->ram,&cpu->regs.pc);
        decoded_instr_t di = format_instruction(instr);
        printf("0x%x, 0x%x, 0x%x\n",di.opcode,di.reg_type_flag,di.operand);
    }
    printf("\n%d\n",cpu->regs.pc);
    free(cpu);

    return 0;
}
