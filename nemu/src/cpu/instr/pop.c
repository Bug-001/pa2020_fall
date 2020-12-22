#include "cpu/instr.h"

static void instr_execute_1op()
{
    OPERAND s;
    s.type = OPR_MEM;
    s.addr = cpu.esp;
    s.data_size = data_size;
    s.sreg = SREG_SS;
    operand_read(&s);
    
    opr_src.val = s.val;
    
    operand_write(&opr_src);
    
    cpu.esp += data_size / 8;
}

make_instr_impl_1op(pop, r, v)
make_instr_impl_1op(pop, rm, v)

make_instr_func(popa)
{
    OPERAND s, r;
    
    s.type = OPR_MEM;
    s.data_size = data_size;
    s.sreg = SREG_SS;
    
    r.type = OPR_REG;
    r.data_size = data_size;
    
    for(int i = 7; i >= 0; --i)
    {
        if(i != REG_ESP)
        {
            s.addr = cpu.esp;
            operand_read(&s);
            r.val = s.val;
            r.addr = i;
            operand_write(&r);
        }
        cpu.esp += data_size / 8;
    }
    print_asm_0("popa", "", 1);
    return 1;
}