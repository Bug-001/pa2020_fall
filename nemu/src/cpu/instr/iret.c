#include "cpu/instr.h"

make_instr_func(iret)
{
    if(cpu.cr0.pe == 0)
    {
        // OPERAND 
        if(data_size == 32)
        {
            // EIP <- Pop()
        }
        else
        {
            // IP <- Pop()
        }
        // CS <- Pop()
        if(data_size == 32)
        {
            // EFLAGS <- Pop()
        }
        else
        {
            
        }
    }
    else
    {
        
    }
    print_asm_0("iret", data_size == 32 ? "d" : "", 1);
    return 1;
}