#include "../include/ops.h"
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
            return data_movement_ops(cpu, instr);
        case OP_ARITH:
            return arithmetic_ops(cpu, instr);
        case OP_LOGIC:
            return logic_bitwise_ops(cpu, instr);
        case OP_COMP:
            return compare_condition_ops(cpu,instr);
        case OP_BRANCH:
            return branch_controlflow_ops(cpu,instr);
        case OP_STACK:
            return stack_ops(cpu,instr);
        case OP_SYS:
            return system_ops(cpu,instr);
        default:
            //needs to crash
            printf("Encountered bad opcode: 0x%x\n",instr.opcode >> 4);
            exit(1);
    }

}

int data_movement_ops(cpu_t* cpu, decoded_instr_t instr){

    uint8_t secondary_opcode = instr.opcode & 0b00001111;



    int(*func)(cpu_t*,decoded_instr_t) = NULL;

    switch(secondary_opcode){
        case 0b0000:
            func = nop;
        case 0b0001:
            func = mov_reg_reg;
        case 0b0010:
            func = mov_reg_imm;
        case 0b0011:
            func = load_reg_addr;
        case 0b0100:
            func = load_reg_regoff;
        case 0b0101:
            func = store_addr_reg;
        case 0b0110:
            func = store_regoff_reg;
        case 0b0111:
            func = push_reg;
        case 0b1000:
            func = pop_reg;
        case 0b1001:
             func = lea_reg_addr;
        default:
            printf("Invalid secondary opcode in datamovement ops: 0x%x\n",secondary_opcode);

    }

    if(func == NULL){
        //needs to crash
        exit(1);
    }
    return func(cpu,instr);
}

int arithmetic_ops(cpu_t* cpu, decoded_instr_t instr){

    uint8_t secondary_opcode = instr.opcode & 0b00001111;


    int(*func)(cpu_t*,decoded_instr_t) = NULL;

    switch(secondary_opcode){
        case 0b0000:
            func = add_reg_reg;
        case 0b0001:
            func = add_reg_imm;
        case 0b0010:
            func = sub_reg_reg;
        case 0b0011:
            func = sub_reg_imm;
        case 0b0100:
            func = mul_reg_reg;
        case 0b0101:
            func = mul_reg_imm;
        case 0b0110:
            func = div_reg_reg;
        case 0b0111:
            func = div_reg_imm;
        case 0b1000:
            func = inc_reg;
        case 0b1001:
            func = dec_reg;
        default:
            printf("Invalid secondary opcode in arthimetic ops: 0x%x\n",secondary_opcode);

    }


    if(func == NULL){
        //needs to crash
        exit(1);
    }
    return func(cpu,instr);


}
int logic_bitwise_ops(cpu_t* cpu, decoded_instr_t instr){

    uint8_t secondary_opcode = instr.opcode & 0b00001111;


    int(*func)(cpu_t*,decoded_instr_t) = NULL;
    switch(secondary_opcode){
        case 0b0000:
            func = cmp_reg_reg;
        case 0b0001:
            func = cmp_reg_imm;
        case 0b0010:
            func = test_reg_reg;
        case 0b0011:
            func = test_reg_imm;
        case 0b0100:
            func = seteq_reg;
        case 0b0101:
            func = setne_reg;
        case 0b0110:
            func = setgt_reg;
        case 0b0111:
            func = setlt_reg;
        default:
            printf("Invalid secondary opcode in logical bitwise ops ops: 0x%x\n",secondary_opcode);

    }

    if(func == NULL){
        //needs to crash
        exit(1);
    }
    return func(cpu,instr);


}
int compare_condition_ops(cpu_t* cpu, decoded_instr_t instr){

    uint8_t secondary_opcode = instr.opcode & 0b00001111;

    int(*func)(cpu_t*, decoded_instr_t) = NULL;
    switch(secondary_opcode){
        case 0b0000:
            func = cmp_reg_reg;
        case 0b0001:
            func = cmp_reg_imm;
        case 0b0010:
            func = test_reg_reg;
        case 0b0011:
            func = test_reg_imm;
        case 0b0100:
            func = seteq_reg;
        case 0b0101:
            func = setne_reg;
        case 0b0110:
            func = setgt_reg;
        case 0b0111:
            func = setlt_reg;
        default:
            printf("Invalid secondary opcode in logical bitwise ops ops: 0x%x\n",secondary_opcode);

    }

    if(func == NULL){
        //needs to crash
        exit(1);
    }
    return func(cpu,instr);
}
int branch_controlflow_ops(cpu_t* cpu, decoded_instr_t instr){

    uint8_t secondary_opcode = instr.opcode & 0b00001111;

    int(*func)(cpu_t*, decoded_instr_t) = NULL;
    switch(secondary_opcode){
        case 0b0000:
            func = jmp_addr;
        case 0b0001:
            func = jz_addr;
        case 0b0010:
            func = jnz_addr;
        case 0b0011:
            func = jg_addr;
        case 0b0100:
            func = jl_addr;
        case 0b0101:
            func = call_addr;
        case 0b0110:
            func = ret;
        case 0b0111:
            func = loop_reg_addr;
        default:
            printf("Invalid secondary opcode in branch controlflow ops: 0x%x\n",secondary_opcode);

    }

    if(func == NULL){
        //needs to crash
        exit(1);
    }
    return func(cpu,instr);
}


int stack_ops(cpu_t* cpu, decoded_instr_t instr){

    uint8_t secondary_opcode = instr.opcode & 0b00001111;

    int(*func)(cpu_t*, decoded_instr_t) = NULL;
    switch(secondary_opcode){
        case 0b0000:
            func = enter_imm;
        case 0b0001:
            func = leave;
        case 0b0010:
            func = push_imm;
        case 0b0011:
            func = popall;
        case 0b0100:
            func = NULL;
        case 0b0101:
            func = NULL;
        case 0b0110:
            func = NULL;
        case 0b0111:
            func = NULL;
        default:
            printf("Invalid secondary opcode in branch controlflow ops: 0x%x\n",secondary_opcode);

    }

    if(func == NULL){
        //needs to crash
        exit(1);
    }
    return func(cpu,instr);
}
int system_ops(cpu_t* cpu, decoded_instr_t instr){

    uint8_t secondary_opcode = instr.opcode & 0b00001111;

    int(*func)(cpu_t*, decoded_instr_t) = NULL;
    switch(secondary_opcode){
        case 0b0000:
            func = interupt_imm;
        case 0b0001:
            func = syscall_reg;
        case 0b0010:
            func = halt_op;
        case 0b0011:
            func = wait_op;
        case 0b0100:
            func = break_op;
        case 0b0101:
            func = NULL;
        case 0b0110:
            func = NULL;
        case 0b0111:
            func = NULL;
        default:
            printf("Invalid secondary opcode in system calls ops: 0x%x\n",secondary_opcode);

    }

    if(func == NULL){
        //needs to crash
        exit(1);
    }
    return func(cpu,instr);
}
