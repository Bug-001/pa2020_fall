#include "cpu/instr.h"

// static void instr_execute_2op()
// {
//     operand_read(&opr_src);
//     operand_read(&opr_dest);
//     uint32_t opr_src_temp = sign_ext(opr_src.val, opr_src.data_size);
//     opr_dest.val = alu_add(opr_src_temp, opr_dest.val, opr_dest.data_size);
//     operand_write(&opr_dest);
// }

fc_instr_execute(add)

// make_instr_func(add_r2rm_b);    // 0x00
// make_instr_func(add_r2rm_v);    // 0x01
// make_instr_func(add_rm2r_b);    // 0x02
// make_instr_func(add_rm2r_v);    // 0x03
// make_instr_func(add_i2a_b);     // 0x04
// make_instr_func(add_i2a_v);     // 0x05

// make_instr_func(add_i2rm_b);    // 0x80
// make_instr_func(add_i2rm_v);    // 0x81
// make_instr_func(add_i2rm_bv);   // 0x83

// make_instr_impl_2op(add, r, rm, b)
// make_instr_impl_2op(add, r, rm, v)
// make_instr_impl_2op(add, rm, r, b)
// make_instr_impl_2op(add, rm, r, v)
// make_instr_impl_2op(add, i, a, b)
// make_instr_impl_2op(add, i, a, v)
// make_instr_impl_2op(add, i, rm, b)
// make_instr_impl_2op(add, i, rm, v)
// make_instr_impl_2op(add, i, rm, bv)

fc_make_instr_impls(add)