#include "cpu/instr.h"

make_instr_func(leave_v)
{
    OPERAND eBP;
    eBP.type = OPR_REG;
    eBP.data_size = data_size;
    eBP.addr = 5;
    
    // eSP <- eBP
    // operand_read(&eBP);
    // eSP.val = eBP.val;
    // operand_write(&eSP);
    cpu.esp = cpu.ebp;
    
    OPERAND s;
    s.type = OPR_MEM;
    s.addr = cpu.esp;
    s.data_size = data_size;
    s.sreg = SREG_SS;
    
    // eBP <- Pop()
    operand_read(&s);
    eBP.val = s.val;
    operand_write(&eBP);
    cpu.esp += data_size / 8;
    
    print_asm_0("leave", " ", 1);
    
    return 1;
}
