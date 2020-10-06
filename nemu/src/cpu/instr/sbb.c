#include "cpu/instr.h"

static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_src_temp = sign_ext(opr_src.val, opr_dest.data_size);
    opr_dest.val = alu_sbb(opr_src_temp, opr_dest.val, opr_dest.data_size);
    operand_write(&opr_dest);
}

fc_make_instr_impls(sbb)
