#include "cpu/intr.h"
#include "cpu/instr.h"

/*
Put the implementations of `int' instructions here.

Special note for `int': please use the instruction name `int_' instead of `int'.
*/

make_instr_func(int_)
{
    assert(cpu.cr0.pe == 1);
    
    OPERAND temp;
    temp.type = OPR_IMM;
    temp.addr = eip + 1;
    temp.data_size = 8;
    temp.sreg = SREG_CS;
    operand_read(&temp);
    raise_sw_intr(temp.val);
    print_asm_1("int", "", 2, &temp);
    
    return 0;
}