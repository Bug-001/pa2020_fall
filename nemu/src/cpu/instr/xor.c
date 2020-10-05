#include "cpu/instr.h"

static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_dest.val = alu_xor(opr_src.val, opr_dest.val, data_size);
    operand_write(&opr_dest);
}

fc_make_instr_impls(xor)