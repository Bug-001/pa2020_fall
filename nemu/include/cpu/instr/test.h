#ifndef __INSTR_TEST_H__
#define __INSTR_TEST_H__

make_instr_func(test_i2a_b);    // 0xA8
make_instr_func(test_i2a_v);    // 0xA9

make_instr_func(test_i2rm_b);   // 0xF6
make_instr_func(test_i2rm_v);   // 0xF7

make_instr_func(test_r2rm_b);   // 0x84
make_instr_func(test_r2rm_v);   // 0x85

#endif
