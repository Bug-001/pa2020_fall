#ifndef __ALU_H__
#define __ALU_H__

#include <cpu-ref/alu_ref.h>

// enable NEMU_REF_ALU to use reference implementation
// #define NEMU_REF_ALU

// // flag-setting functions
// void set_SF(uint32_t result, size_t data_size);
// void set_ZF(uint32_t result, size_t data_size);
// void set_PF(uint32_t result, size_t data_size);

// // Core functions
// // add, adc, sub, sbb
// uint32_t adder(uint32_t X, uint32_t Y, bool sub, bool useCF, size_t data_size);
// // and, or, xor
// uint32_t gate(uint32_t X, uint32_t Y, int logic, size_t data_size);
// // shl, sal, shr, sar
// uint32_t shift(uint32_t operand, uint32_t count, int shift_mode, size_t data_size);

// dest + src
uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size);
// dest + src + CF
uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size);
// dest - src
uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size);
// dest - src - CF
uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size);
// dest & src
uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size);
// dest ^ src
uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size);
// dest | src
uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size);
// dest << src
uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size);
// dest >> src
uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size);
uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size);
uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size);

// dest * src
uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size);
int64_t alu_imul(int32_t src, int32_t dest, size_t data_size);
// dest / src
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size);
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size);
//uint32_t alu_mod(uint32_t src, uint32_t dest);
uint32_t alu_mod(uint64_t src, uint64_t dest);
int32_t alu_imod(int64_t src, int64_t dest);

// sign extend
#define sign(x) ((uint32_t)(x) >> 31)
//#define sign_ext(x) ((int32_t)((int8_t)(x)))

inline uint32_t sign_ext(uint32_t x, size_t data_size)
{
        // (int32_t) can sign-extend x, while (int8_t) or (int16_t) make the sign bit of x exposed to sign-extending.
        assert(data_size == 16 || data_size == 8 || data_size == 32);
        switch (data_size)
        {
        case 8:
                return (int32_t)((int8_t)(x & 0xff));
        case 16:
                return (int32_t)((int16_t)(x & 0xffff));
        default:
                return (int32_t)x;
        }
}

inline uint64_t sign_ext_64(uint32_t x, size_t data_size)
{
        assert(data_size == 16 || data_size == 8 || data_size == 32);
        switch (data_size)
        {
        case 8:
                return (int64_t)((int8_t)(x & 0xff));
        case 16:
                return (int64_t)((int16_t)(x & 0xffff));
        default:
                return (int64_t)((int32_t)x);
        }
}

#endif
