#ifndef __INSTR_CMP_H__
#define __INSTR_CMP_H__

make_instr_func(cmp_r2rm_b); // 0x38
make_instr_func(mov_r2rm_v);
make_instr_func(mov_rm2r_b);
make_instr_func(mov_rm2r_v);
make_instr_func(mov_i2rm_b);
make_instr_func(mov_i2rm_v);
make_instr_func(mov_i2r_b);
make_instr_func(mov_i2r_v);
make_instr_func(mov_o2a_b);
make_instr_func(mov_o2a_v);
make_instr_func(mov_a2o_b);
make_instr_func(mov_a2o_v);
make_instr_func(mov_zrm82r_v);
make_instr_func(mov_zrm162r_l);
make_instr_func(mov_srm82r_v);
make_instr_func(mov_srm162r_l);

make_instr_func(cmp_r2rm_b); // 0x38
make_instr_func(mov_r2rm_v); // 0x39
make_instr_func(cmp_rm2r_b); // 0x3A
make_instr_func(cmp_rm2r_v); // 0x3B

#endif
