#include "cpu/instr.h"

static void instr_execute_1op()
{
    cpu.esp -= opr_src.data_size / 8;
    
    operand_read(&opr_src);
    
    OPERAND s;
    s.type = OPR_MEM;
    s.addr = cpu.esp;
    s.val = opr_src.val;
    s.data_size = opr_src.data_size;
    s.sreg = SREG_SS;
    
    operand_write(&s);
}

make_instr_impl_1op(push, r, v)
make_instr_impl_1op(push, rm, v)
make_instr_impl_1op(push, i, b)
make_instr_impl_1op(push, i, v)

make_instr_func(pusha)
{
    OPERAND s, r;
    
    s.type = OPR_MEM;
    s.data_size = data_size;
    s.sreg = SREG_SS;
    s.addr = cpu.esp;
    
    r.type = OPR_REG;
    r.data_size = data_size;
    
    uint32_t temp[8];
    for(int i = 0; i < 8; ++i)
    {
        r.addr = i;
        operand_read(&r);
        temp[i] = r.val;
    }
    temp[REG_ESP] = cpu.esp;
    for(int i = 0; i < 8; ++i)
    {
        s.addr -= data_size / 8;
        s.val = temp[i];
        operand_write(&s);
    }
    cpu.esp = s.addr;
    print_asm_0("pusha", data_size == 32 ? "d" : "", 1);
    return 1;
}