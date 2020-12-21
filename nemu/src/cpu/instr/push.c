#include "cpu/instr.h"

static void instr_execute_1op()
{
    cpu.esp -= data_size / 8;
    
    operand_read(&opr_src);
    
    OPERAND s;
    s.type = OPR_MEM;
    s.addr = cpu.esp;
    s.val = opr_src.val;
    s.data_size = data_size;
    s.sreg = SREG_SS;
    
    operand_write(&s);
}

make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, rm, v)
make_instr_impl_1op(push, i, b)
make_instr_impl_1op(push, i, v)