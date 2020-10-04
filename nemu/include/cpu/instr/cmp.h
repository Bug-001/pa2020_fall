#ifndef __INSTR_CMP_H__
#define __INSTR_CMP_H__

make_instr_func(cmp_r2rm_b);    // 0x38
make_instr_func(mov_r2rm_v);    // 0x39
make_instr_func(cmp_rm2r_b);    // 0x3A
make_instr_func(cmp_rm2r_v);    // 0x3B
make_instr_func(cmp_i2a_b);     // 0x3C
make_instr_func(cmp_i2a_v);     // 0x3D
make_instr_func(cmp_i2rm_b);    // 0x80
make_instr_func(cmp_i2rm_v);    // 0x81, 0x83


#endif
