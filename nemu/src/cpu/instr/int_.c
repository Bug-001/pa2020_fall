#include "cpu/intr.h"
#include "cpu/instr.h"

/*
Put the implementations of `int' instructions here.

Special note for `int': please use the instruction name `int_' instead of `int'.
*/

make_instr_func(int_)
{
    assert(cpu.cr0.pe == 1);
    uint8_t intr_no = instr_fetch(eip + 1, 1);
    raise_sw_intr(intr_no);
    
    OPERAND temp;
    temp.val = intr_no;
    print_asm_1("int", "", 2, &temp);
    
    return 0;
}