#include "../include/cpu.h"
#include <stdint.h>

cpu_t* init_cpu(){
    cpu_t* c = calloc(1,sizeof(cpu_t));
    if(c == NULL){
        return NULL;
    }
    c->regs.pc = PROGRAM_CODE_START_ADDR;
    c->regs.sp = STACK_START_ADDR;
    return c;
}

int load_program(uint8_t* ram, uint16_t* pc, uint8_t* program, int plen){
    if(ram == NULL || program == NULL || pc == NULL){
        //needs to crash
        exit(1);

    }


    uint16_t pc_val = *pc;

    for(int i = 0; i<plen; i++){
        ram[pc_val] = program[i];
        pc_val++;
    }

    return 0;
}



uint32_t fetch_instruction(uint8_t* ram, uint16_t* pc){

    if(ram == NULL || pc == NULL){
        //needs to crash
        printf("ram or pc null in fetch_instruction");
        exit(1);
    }

    uint32_t instr_four_byte = 0;
    for(int i = 0; i<4; i++){
        uint8_t instr_byte = ram[*pc];
        (*pc)++;
        if(!i){
            instr_four_byte = instr_byte;
        }
        if(i) {
            instr_four_byte <<= 8;
            instr_four_byte |= instr_byte;
        }
    }
    return instr_four_byte;
}


decoded_instr_t format_instruction(uint32_t instr){
    decoded_instr_t di;
    di.operand = instr;
    di.reg_type_flag = instr >> 16;
    di.opcode = instr >> 24;
    return di;
}


int execute_instruction(cpu_t* cpu, decoded_instr_t instr){

    uint8_t primary_opcode = instr.opcode >> 4;

    switch(primary_opcode) {
        case OP_DATA_MOVE:
            subopcode_ops(cpu, instr, data_movement_ops);
        case OP_ARITH:
            subopcode_ops(cpu, instr, arithmetic_ops);
        case OP_LOGIC:
            subopcode_ops(cpu, instr, logic_bitwise_ops);
        case OP_COMP:
            subopcode_ops(cpu, instr, compare_condition_ops);
        case OP_BRANCH:
            branch_controlflow_ops(cpu, instr);
        case OP_STACK:
            stack_ops(cpu, instr);
        case OP_SYS:
            system_ops(cpu, instr);
        default:
            //needs to crash
            printf("Encountered bad opcode: 0x%x\n",instr.opcode >> 4);
            exit(1);
    }

}

int data_movement_ops(cpu_t* cpu, decoded_instr_t instr){

    uint8_t secondary_opcode = instr.opcode >> 4;
    switch(secondary_opcode){
        case DM_NOP:
        case DM_MOV_REG_REG:
        case DM_MOV_REG_IMM:
        case DM_LOAD_REG_ADDR:
        case DM_LOAD_REG_REGOFF:
        case DM_STORE_ADDR_REG:
        case DM_STORE_REGOFF_REG:
        case DM_PUSH_REG:
        case DM_POP_REG:
        case DM_LEA_REG_ADDR:
        default:
            printf("Bad Secondary Opcode in Data Movement: 0x%x\n",secondary_opcode);
            //needs to crash
            exit(1);
    }

}

int subopcode_ops(cpu_t * cpu, decoded_instr_t instr, int (*popcode_func)(cpu_t *cpu, decoded_instr_t instr)){

}
