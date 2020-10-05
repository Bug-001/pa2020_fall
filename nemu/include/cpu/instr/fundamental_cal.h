#include "cpu/instr.h"

#define fc_make_instr_impls(name)               
    make_instr_impl_2op(name, r, rm, b)         \
    make_instr_impl_2op(name, r, rm, v)         \
    make_instr_impl_2op(name, rm, r, b)         \
    make_instr_impl_2op(name, rm, r, v)         \
    make_instr_impl_2op(name, i, a, b)          \
    make_instr_impl_2op(name, i, a, v)          \
    make_instr_impl_2op(name, i, rm, b)         \
    make_instr_impl_2op(name, i, rm, v)         \
    make_instr_impl_2op(name, i, rm, bv)
    
#define fc_make_instr_funcs(name)               
    make_instr_func(concat(name, _r2rm_b));     \
    make_instr_func(concat(name, _r2rm_v));     \
    make_instr_func(concat(name, _rm2r_b));     \
    make_instr_func(concat(name, _rm2r_v));     \
    make_instr_func(concat(name, _i2a_b));      \
    make_instr_func(concat(name, _i2a_v));      \
    make_instr_func(concat(name, _i2rm_b));     \
    make_instr_func(concat(name, _i2rm_v));     \
    make_instr_func(concat(name, _i2rm_bv));