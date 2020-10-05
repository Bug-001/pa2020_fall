#include "cpu/instr.h"

make_instr_func(leave_v)
{
    OPERAND eBP, eSP, s;
    eBP.type = eSP.type = OPR_REG;
    eBP.data_size = eSP.data_size = data_size;
    eBP.addr = 5, eSP.addr = 4;
    s.type = OPR_MEM;
    s.addr = cpu.esp;
    s.data_size = data_size;
    s.sreg = SREG_CS;
    
    // eSP <- eBP
    operand_read(&eBP);
    eSP.val = eBP.val;
    operand_write(&eSP);
    
    // eBP <- Pop()
    operand_read(&s);
    eBP.val = s.val;
    operand_write(&eBP);
    cpu.esp += data_size / 8;
}
