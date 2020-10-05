#include "cpu/instr.h"

static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    alu_and(opr_src.val, opr_dest.val);
}

// make_instr_func(test_i2a_b);    // 0xA8
// make_instr_func(test_i2a_v);    // 0xA9

// make_instr_func(test_i2rm_b);   // 0xF6
// make_instr_func(test_i2rm_v);   // 0xF7

// make_instr_func(test_r2rm_b);   // 0x84
// make_instr_func(test_r2rm_v);   // 0x85

make_instr_impl_2op(test, i, a, b)
make_instr_impl_2op(test, i, a, v)

make_instr_impl_2op(test, i, rm, b)
make_instr_impl_2op(test, i, rm, v)

make_instr_impl_2op(test, r, rm, b)
make_instr_impl_2op(test, r, rm, v)