#include "cpu/instr.h"

// static void instr_execute_2op()
// {
//     operand_read(&opr_src);
//     operand_read(&opr_dest);
//     uint32_t opr_src_temp = sign_ext(opr_src.val, opr_src.data_size);
//     opr_dest.val = alu_or(opr_src_temp, opr_dest.val, opr_dest.data_size);
//     operand_write(&opr_dest);
// }

fc_instr_execute(or)

fc_make_instr_impls(or)