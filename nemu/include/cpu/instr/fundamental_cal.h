#include "cpu/instr.h"

#define fc_make_instr_impls(inst_name) \
    make_instr_impl_2op(inst_name, r, rm, b) \
    make_instr_impl_2op(inst_name, r, rm, v) \
    make_instr_impl_2op(inst_name, rm, r, b) \
    make_instr_impl_2op(inst_name, rm, r, v) \
    make_instr_impl_2op(inst_name, i, a, b) \
    make_instr_impl_2op(inst_name, i, a, v) \
    make_instr_impl_2op(inst_name, i, rm, b) \
    make_instr_impl_2op(inst_name, i, rm, v) \
    make_instr_impl_2op(inst_name, i, rm, bv)


#define fc_make_instr_funcs(inst_name) \
    make_instr_func(concat(inst_name, _r2rm_b)); \
    make_instr_func(concat(inst_name, _r2rm_v)); \
    make_instr_func(concat(inst_name, _rm2r_b)); \
    make_instr_func(concat(inst_name, _rm2r_v)); \
    make_instr_func(concat(inst_name, _i2a_b));  \
    make_instr_func(concat(inst_name, _i2a_v)); \
    make_instr_func(concat(inst_name, _i2rm_b)); \
    make_instr_func(concat(inst_name, _i2rm_v)); \
    make_instr_func(concat(inst_name, _i2rm_bv));

#define fc_instr_execute(inst_name) \
    static void instr_execute_2op() \
    { \
        operand_read(&opr_src); \
        operand_read(&opr_dest); \
        uint32_t opr_src_temp = sign_ext(opr_src.val, opr_src.data_size); \
        opr_dest.val = concat(alu_, inst_name)(opr_src_temp, opr_dest.val, opr_dest.data_size); \
        operand_write(&opr_dest); \
    }
