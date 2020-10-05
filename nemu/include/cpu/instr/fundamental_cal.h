#include "cpu/instr.h"

#define fc_make_instr_impls(inst_name)               \
    make_instr_impl_2op(inst_name, r, rm, b)         \
    make_instr_impl_2op(inst_name, r, rm, v)         \
    make_instr_impl_2op(inst_name, rm, r, b)         \
    make_instr_impl_2op(inst_name, rm, r, v)         \
    make_instr_impl_2op(inst_name, i, a, b)          \
    make_instr_impl_2op(inst_name, i, a, v)          \
    make_instr_impl_2op(inst_name, i, rm, b)         \
    make_instr_impl_2op(inst_name, i, rm, v)         \
    make_instr_impl_2op(inst_inst_name, i, rm, bv)
    
#define fc_make_instr_funcs(inst_name)               \
    make_instr_func(concat(inst_name, _r2rm_b));     \
    make_instr_func(concat(inst_name, _r2rm_v));     \
    make_instr_func(concat(inst_name, _rm2r_b));     \
    make_instr_func(concat(inst_name, _rm2r_v));     \
    make_instr_func(concat(inst_name, _i2a_b));      \
    make_instr_func(concat(inst_name, _i2a_v));      \
    make_instr_func(concat(inst_name, _i2rm_b));     \
    make_instr_func(concat(inst_name, _i2rm_v));     \
    make_instr_func(concat(inst_name, _i2rm_bv));