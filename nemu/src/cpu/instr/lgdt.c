#include "cpu/instr.h"

make_instr_func(lgdt)
{
	int len = 1;
	opr_src.data_size = data_size;
	len += modrm_rm(eip + 1, &opr_src);
	print_asm_1("lgdt", "", len + 1, &opr_src);
	if(cpu.cr0.pe == 1)
	{
	    cpu.gdtr.limit = laddr_read(opr_src.addr, 2);
        cpu.gdtr.base = laddr_read(opr_src.addr + 2, 4);
	}
	else
	{
	    cpu.gdtr.limit = paddr_read(opr_src.addr, 2);
        cpu.gdtr.base = paddr_read(opr_src.addr + 2, 4);
	}

    return len;
}