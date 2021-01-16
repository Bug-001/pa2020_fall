#include "cpu/instr.h"

static int instr_execute_1op()
{
    operand_read(&opr_src);
    opr_src.val = alu_mul(opr_src.val, 0xFFFFFFFF, data_size);
    operand_write(&opr_src);
}

make_instr_impl_1op(neg, rm, b)
make_instr_impl_1op(neg, rm, v)