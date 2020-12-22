#include "cpu/instr.h"

#ifdef IA32_INTR
make_instr_func(lidt)
{
	int len = 1;
	opr_src.data_size = data_size;
	len += modrm_rm(eip + 1, &opr_src);
	print_asm_1("lidt", "", len + 1, &opr_src); 
	cpu.idtr.limit = paddr_read(opr_src.addr, 2);
    cpu.idtr.base = paddr_read(opr_src.addr + 2, 4);
    return len;
}
#endif