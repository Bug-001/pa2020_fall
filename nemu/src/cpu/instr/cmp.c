#include "cpu/instr.h"
// #include "cpu/alu.h"

static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    uint32_t opr_src_temp = sign_ext(opr_src.val, opr_dest.data_size);
    alu_sub(opr_src_temp, opr_dest.val, opr_dest.data_size);
}

// make_instr_func(cmp_r2rm_b);    // 0x38
// make_instr_func(cmp_r2rm_v);    // 0x39
// make_instr_func(cmp_rm2r_b);    // 0x3A
// make_instr_func(cmp_rm2r_v);    // 0x3B
// make_instr_func(cmp_i2a_b);     // 0x3C
// make_instr_func(cmp_i2a_v);     // 0x3D

// make_instr_func(cmp_i2rm_b);    // 0x80
// make_instr_func(cmp_i2rm_v);     // 0x81
// make_instr_func(cmp_i2rm_bv);    // 0x83

make_instr_impl_2op(cmp, r, rm, b)
make_instr_impl_2op(cmp, r, rm, v)
make_instr_impl_2op(cmp, rm, r, b)
make_instr_impl_2op(cmp, rm, r, v)
make_instr_impl_2op(cmp, i, a, b)
make_instr_impl_2op(cmp, i, a, v)
make_instr_impl_2op(cmp, i, rm, b)
make_instr_impl_2op(cmp, i, rm, v)
make_instr_impl_2op(cmp, i, rm, bv)