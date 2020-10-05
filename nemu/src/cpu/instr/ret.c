#include "cpu/instr.h"

static int ret_near_(bool imm16)
{
    OPERAND s;
    s.type = OPR_MEM;
    s.sreg = SREG_CS;
    s.addr = cpu.esp;
    s.data_size = data_size;
    // s.data_size = 32;
    
    operand_read(&s);
    cpu.esp += data_size / 8;
    
    if(imm16)
    {
        opr_dest.type = OPR_IMM;
        opr_dest.sreg = SREG_CS;
        opr_dest.addr = cpu.eip + 1;
        opr_dest.data_size = 16;
        operand_read(&opr_dest);
        cpu.esp += opr_dest.val;
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