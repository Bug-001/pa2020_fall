#include "cpu/instr.h"

static void instr_execute_1op()
{
    operand_read(&opr_src);
    ++opr_src.val;
    operand_write(&opr_src);
}

make_instr_impl_2op(inc_rm_b)
make_instr_impl_2op(inc_rm_v)
make_instr_impl_2op(inc_r_v)