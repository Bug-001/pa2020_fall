#include "cpu/instr.h"

make_instr_func(jmp_near)
{
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip + 1;

    operand_read(&rel);

    int offset = sign_ext(rel.val, data_size);
    // thank Ting Xu from CS'17 for finding this bug
    print_asm_1("jmp", "", 1 + data_size / 8, &rel);

    cpu.eip += offset;

    return 1 + data_size / 8;
}

make_instr_func(jmp_short_)
{
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = 8;
    rel.addr = eip + 1;

    operand_read(&rel);

    int offset = sign_ext(rel.val, rel.data_size);
    print_asm_1("jmp", "", 1 + rel.data_size / 8, &rel);

    cpu.eip += offset;

    return 1 + rel.data_size / 8;
}

make_instr_func(jmp_near_indirect)
{
    OPERAND ind;
    
    // ind.type = OPR_IMM;
    // ind.sreg = SREG_CS;
    ind.data_size = 32;
    // ind.addr = eip + 1;
    int len = modrm_rm(eip + 1, &ind);
    operand_read(&ind);
    print_asm_1("jmp", "", 1 + len, &ind);
    
    cpu.eip = ind.val;
    
    return 0;
}
