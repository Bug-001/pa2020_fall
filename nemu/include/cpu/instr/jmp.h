#ifndef __INSTR_JMP_H__
#define __INSTR_JMP_H__

make_instr_func(jmp_near);      // 0xE9
make_instr_func(jmp_far);      // 0xEA
make_instr_func(jmp_short_);    // 0xEB
make_instr_func(jmp_near_indirect);  // 0xFF-4

#endif
