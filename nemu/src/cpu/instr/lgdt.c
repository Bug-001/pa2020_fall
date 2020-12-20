#include "cpu/instr.h"

static void instr_execute_1op()
{
    operand_read(&opr_src);
    cpu.gdtr.limit = paddr_read(opr_src.val, 2);
    cpu.gdtr.base = paddr_read(opr_src.val + 2, 4);
    printf("limit = %08x\n", cpu.gdtr.limit);
    printf("base = %08x\n", cpu.gdtr.base);
}

make_instr_func(lgdt)                                                                 
{                                                                                                                           
	int len = 1;                                                                                                            
	opr_src.data_size = data_size;                                                                                     
	len += modrm_rm(eip + 1, &opr_src);
	print_asm_1("lgdt", "", len + 1, &opr_src); 
	instr_execute_1op();                                                                                                    
	return len;                                                                                                             
}