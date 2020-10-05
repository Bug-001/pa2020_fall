#include "cpu/instr.h"

static void instr_execute_1op()
{
    OPERAND s;
    s.type = OPR_MEM;
    s.addr = cpu.esp;
    s.data_size = data_size;
    s.sreg = SREG_CS;
    operand_read(&s);
    
    opr_src.val = s.val;
    
    operand_write(&opr_src);
    
    cpu.esp += data_size / 8;
}

make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, rm, v)