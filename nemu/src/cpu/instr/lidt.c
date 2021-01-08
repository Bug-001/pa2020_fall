#include "cpu/instr.h"

make_instr_func(lidt)
{
    int len = 1;
#ifdef IA32_INTR
	opr_src.data_size = data_size;
	len += modrm_rm(eip + 1, &opr_src);
	print_asm_1("lidt", "", len + 1, &opr_src); 
	if(cpu.cr0.pg == 1)
	{
	    cpu.idtr.limit = laddr_read(opr_src.addr, 2);
        cpu.idtr.base = laddr_read(opr_src.addr + 2, 4);
	}
	else
	{
	    cpu.idtr.limit = paddr_read(opr_src.addr, 2);
        cpu.idtr.base = paddr_read(opr_src.addr + 2, 4);
	}
#else
    assert(0);
#endif
    return len;
}
