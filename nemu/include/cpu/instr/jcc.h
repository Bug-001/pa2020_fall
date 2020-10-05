#ifndef __INSTR_JCC_H__
#define __INSTR_JCC_H__

make_instr_func(je_short_);     // 0x74
make_instr_func(ja_short_);     // 0x77
make_instr_func(jae_short_);    // 0x73
make_instr_func(jb_short_);     // 0x72
make_instr_func(jecxz_short_);  // 0xE3
make_instr_func(jg_short_);     // 0x7F
make_instr_func(jge_short_);    // 0x7D
make_instr_func(jl_short_);     // 0x7C
make_instr_func(jle_short_);    // 0x7E
make_instr_func(jna_short_);    // 0x76
make_instr_func(jne_short_);    // 0x75
make_instr_func(jno_short_);    // 0x71
make_instr_func(jnp_short_);    // 0x7B
make_instr_func(jns_short_);    // 0x79
make_instr_func(jo_short_);     // 0x70
make_instr_func(jp_short_);     // 0x7A
make_instr_func(js_short_);     // 0x78

// 0x0F
make_instr_func(je_near);       // 0x84
make_instr_func(ja_near);       // 0x87
make_instr_func(jae_near);      // 0x83
make_instr_func(jb_near);       // 0x82
make_instr_func(jg_near);       // 0x8F
make_instr_func(jge_near);      // 0x8D
make_instr_func(jl_near);       // 0x8C
make_instr_func(jle_near);      // 0x8E
make_instr_func(jna_near);      // 0x86
make_instr_func(jne_near);      // 0x85
make_instr_func(jno_near);      // 0x81
make_instr_func(jnp_near);      // 0x8B
make_instr_func(jns_near);      // 0x89
make_instr_func(jo_near);       // 0x80
make_instr_func(jp_near);       // 0x8A
make_instr_func(js_near);       // 0x88

#endif
