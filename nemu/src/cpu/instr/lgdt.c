#include "cpu/instr.h"

make_instr_func(lgdt)
{
    int pa = paddr_read(eip + 2, 4);
    cpu.gdtr.base = paddr_read(pa, 4);
    cpu.gdtr.limit = paddr_read(pa + 4, 2);
    return 6;
}