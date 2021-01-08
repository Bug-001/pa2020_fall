#include "cpu/instr.h"

make_instr_func(iret)
{
    assert(cpu.cr0.pe == 1);
    cpu.eip = vaddr_read(cpu.esp, SREG_SS, 4);
    cpu.esp += 4;
    cpu.cs.val = vaddr_read(cpu.esp, SREG_SS, 2);
    cpu.esp += 2;
    load_sreg(SREG_CS);
    cpu.eflags.val = vaddr_read(cpu.esp, SREG_SS, 4);
    cpu.esp += 4;
    print_asm_0("iret", data_size == 32 ? "d" : "", 1);
    return 1;
}