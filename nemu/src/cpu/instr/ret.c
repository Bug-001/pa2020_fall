#include "cpu/instr.h"

static int ret_near_(bool imm16)
{
    OPERAND s;
    s.type = OPR_MEM;
    s.sreg = SREG_CS;
    s.addr = cpu.esp;
    s.data_size = data_size;
    
    operand_read(&s);
    cpu.esp += data_size / 8;
    
    if(imm16)
    {
        OPERAND i;
        i.type = OPR_IMM;
        i.sreg = SREG_CS;
        i.addr = cpu.eip + 1;
        i.data_size = 16;
        operand_read(&i);
        cpu.esp += i.val;
    }
    
    cpu.eip = s.val & (0xFFFFFFFF >> (32 - data_size));
    
    print_asm_0("ret", " ", 1);
    
    return 0;
}

make_instr_func(ret_near)
{
    return ret_near_(0);
}

make_instr_func(ret_near_imm16)
{
    return ret_near_(1);
}