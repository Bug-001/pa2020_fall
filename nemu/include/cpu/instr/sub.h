#ifndef __INSTR_SUB_H__
#define __INSTR_SUB_H__

// make_instr_func(sub_r2rm_b);    // 0x28
// make_instr_func(sub_r2rm_v);    // 0x29
// make_instr_func(sub_rm2r_b);    // 0x2A
// make_instr_func(sub_rm2r_v);    // 0x2B
// make_instr_func(sub_i2a_b);     // 0x2C
// make_instr_func(sub_i2a_v);     // 0x2D

// make_instr_func(sub_i2rm_b);    // 0x80
// make_instr_func(sub_i2rm_v);    // 0x81
// make_instr_func(sub_i2rm_bv);   // 0x83

fc_make_instr_funcs(sub)

#endif
