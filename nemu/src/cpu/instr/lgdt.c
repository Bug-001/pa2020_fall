#include "cpu/instr.h"

make_instr_func(lgdt)
{
    int base = paddr_read(eip + 1, 4);
    int limit = paddr_read(eip + 5, 2);
    cpu.gdtr.base = base;
    cpu.gdtr.limit = limit;
    return 7;
}