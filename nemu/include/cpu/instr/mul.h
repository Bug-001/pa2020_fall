#ifndef __INSTR_MUL_H__
#define __INSTR_MUL_H__

make_instr_func(mul_rm2a_b);    // 0xF6-4
make_instr_func(mul_rm2a_v);    // 0xF7-4

make_instr_func(imul_rm2r_v);   // 0x0F 0xAF
make_instr_func(imul_rm2a_b);   // 0xF6-5
make_instr_func(imul_rm2a_v);   // 0xF7-5
make_instr_func(imul_irm2r_v);  // 0x69
make_instr_func(imul_i8rm2r_v); // 0x6B

#endif
