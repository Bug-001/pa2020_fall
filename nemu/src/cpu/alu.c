#include "cpu/cpu.h"

void printb(uint32_t n, size_t data_size)
{
    for(int i = data_size - 1; i >= 0; --i)
    {
        printf("%d", (n >> i) & 1);
        if(i % 4 == 0) printf(" ");
    }
}

void set_SF(uint32_t result, size_t data_size)
{
    result = sign_ext(result & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.SF = sign(result);
}

void set_ZF(uint32_t result, size_t data_size)
{
    result &= (0xFFFFFFFF >> (32 - data_size));
    cpu.eflags.ZF = (result == 0);
}

void set_PF(uint32_t result, size_t data_size)
{
    bool pf = 1;
    for(uint8_t i = 8; i > 0; --i)
    {
        pf ^= (result & 1);
        result >>= 1;
    }
    cpu.eflags.PF = pf;
}

uint32_t adder(uint32_t X, uint32_t Y, bool sub, bool useCF, size_t data_size)
{
    // sub == 0, useCF == 0 -> C == 0      == sub == sub + 0
    // sub == 0, useCF == 1 -> C ==     CF ==        sub + CF
    // sub == 1, useCF == 0 -> C == 1      == sub == sub + 0
    // sub == 1, useCF == 1 -> C == 1 - CF ==        sub - CF
    cpu.eflags.CF = useCF ? cpu.eflags.CF : 0;
    uint32_t C = sub ? sub - cpu.eflags.CF : sub + cpu.eflags.CF;
    uint32_t lastC = C;
    X = sign_ext(X & (0xFFFFFFFF >> (32 - data_size)), data_size);
    Y = sign_ext(Y & (0xFFFFFFFF >> (32 - data_size)), data_size);
    Y = sub ? ~Y : Y;
    // FA Core
    uint32_t result = 0;
    for(int i = data_size; i > 0; --i)
    {
        result >>= 1;
        uint32_t x = X & 1;
        uint32_t y = Y & 1;
        result += ((x ^ y ^ C) << 31);
        lastC = C;
        C = ((x & y) | (x & C) | (y & C)) & 1;
        X >>= 1;
        Y >>= 1;
    }
    result >>= (32 - data_size);
    // CF
    cpu.eflags.CF = sub ^ C;
    // PF
    set_PF(result, data_size);
    // AF
    // ZF
    cpu.eflags.ZF = (result == 0);
    // SF
    cpu.eflags.SF = sign(sign_ext(result, data_size));
    // OF
    cpu.eflags.OF = C ^ lastC;
    // return
    return result;
}

uint32_t gate(uint32_t X, uint32_t Y, int logic, size_t data_size)
{
    uint32_t result;
    switch(logic)
    {
        case 0:
            result = X & Y; // and
        case 1:
            result = X | Y; // or
        default:
            result = X ^ Y; // xor
    }
    result &= (0xFFFFFFFF >> (32 - data_size));
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_SF(result, data_size);
	set_ZF(result, data_size);
	set_PF(result, data_size);
	return result;
}

uint32_t shift(uint32_t src, uint32_t count, int shift_mode, size_t data_size)
{
    // SAL = 0
    // SAR = 1
    // SHL = 2
    // SHR = 3
    uint32_t result = src;
    count &= 0x1F;
    if(shift_mode % 2)  // Right shift: SAR SHR
    {
        result >>= (count - 1);
        cpu.eflags.CF = result & 1;
        result >>= 1;
        cpu.eflags.OF = count == 1 ? sign(sign_ext(result, data_size)) ^ cpu.eflags.CF : cpu.eflags.OF;
    }
    else                //  Left shift: SAL SHL
    {
        result <<= (count - 1);
        cpu.eflags.CF = sign(sign_ext(result, data_size));
        result <<= 1;
        cpu.eflags.OF = shift_mode == 1 ? 0 : sign(sign_ext(src, data_size));
    }
    set_ZF(result, data_size);
    set_SF(result, data_size);
    set_PF(result, data_size);
    return result;
}

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
    return adder(dest, src, 0, 0, data_size);
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
    return adder(dest, src, 0, 1, data_size);
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
    return adder(dest, src, 1, 0, data_size);
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	return adder(dest, src, 1, 1, data_size);
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
    return src & dest;
    // return gate(dest, src, 0, data_size);
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
    return gate(dest, src, 2, data_size);
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
    return gate(dest, src, 1, data_size);
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	return shift(src, dest, 2, data_size);
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	return shift(src, dest, 3, data_size);
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	return shift(src, dest, 1, data_size);
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	return shift(src, dest, 0, data_size);
#endif
}
