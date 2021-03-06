#include "cpu/cpu.h"
#include <stdlib.h>

void printb(int64_t n, size_t data_size)
{
    for(int i = data_size - 1; i >= 0; --i)
    {
        printf("%lld", (n >> i) & 1);
        if(i % 4 == 0) printf(" ");
    }
}

static void set_SF(uint32_t result, size_t data_size)
{
    result = sign_ext(result & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.SF = sign(result);
}

static void set_ZF(uint32_t result, size_t data_size)
{
    result &= (0xFFFFFFFF >> (32 - data_size));
    cpu.eflags.ZF = (result == 0);
}

static void set_PF(uint32_t result, size_t data_size)
{
    bool pf = 1;
    for(uint8_t i = 8; i > 0; --i)
    {
        pf ^= (result & 1);
        result >>= 1;
    }
    cpu.eflags.PF = pf;
}

static uint32_t adder(uint32_t X, uint32_t Y, bool sub, bool useCF, size_t data_size)
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
    cpu.eflags.CF = sub ^ C;
    set_PF(result, data_size);
    cpu.eflags.ZF = (result == 0);
    cpu.eflags.SF = sign(sign_ext(result, data_size));
    cpu.eflags.OF = C ^ lastC;
    return result;
}

static uint32_t gate(uint32_t X, uint32_t Y, int logic, size_t data_size)
{
    uint32_t result;
    switch(logic)
    {
        case 0:
            result = X & Y; // and
            break;
        case 1:
            result = X | Y; // or
            break;
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

static uint32_t shift(uint32_t operand, uint32_t count, int shift_mode, size_t data_size)
{
    // SAL = 00
    // SAR = 01
    // SHL = 10
    // SHR = 11
    operand &= (0xFFFFFFFF >> (32 - data_size));
    uint32_t result = operand;
    count &= 0x1F;
    if(count == 0)
    {
        return result;
    }
    shift_mode &= 3;
    if(shift_mode & 1)  // Right shift: SAR SHR
    {
        if(shift_mode >> 1) // SHR
        {
            result >>= (count - 1);
            cpu.eflags.CF = result & 1;
            result >>= 1;
        }
        else                // SAR
        {
            int32_t temp = sign_ext(result, data_size);
            temp >>= (count - 1);
            cpu.eflags.CF = temp & 1;
            // temp >>= 2;
            temp >>= 1;
            result = temp;
        }
    }
    else                //  Left shift: SAL SHL
    {
        result <<= (count - 1);
        cpu.eflags.CF = sign(sign_ext(result, data_size));
        result <<= 1;
    }
    result &= (0xFFFFFFFF >> (32 - data_size));
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
    uint64_t src64 = src & (0xFFFFFFFF >> (32 - data_size));
    uint64_t dest64 = dest & (0xFFFFFFFF >> (32 - data_size));
	uint64_t res = src64 * dest64;
	cpu.eflags.CF = res >> data_size ? 1 : 0;
	cpu.eflags.OF = res >> data_size ? 1 : 0;
	return res;
	// return res & (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size));
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
//  static int count = 0;
	int64_t src64 = sign_ext_64(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	int64_t dest64 = sign_ext_64(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
  	int64_t res = src64 * dest64;
// 	count++;
// 	if(count > 10) exit(-1);
// 	printf("src=%d, dest=%d\n", src, dest);
// 	printb(res,64); printf("\n");
// 	printb(res & (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size)),64); printf("\n\n");
	return res;
	// return res & (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size));
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
    src &= (0xFFFFFFFF >> (32 - data_size));
    dest &= (0xFFFFFFFF >> (32 - data_size));
    uint32_t res = dest / src;
    return res;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
    int32_t res = dest / src;
    return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
    uint32_t res = dest % src; 
    return res;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
    int32_t res = dest % src;
    return res;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
    return gate(dest, src, 0, data_size);
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
	return shift(dest, src, 2, data_size);
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	return shift(dest, src, 3, data_size);
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	return shift(dest, src, 1, data_size);
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	return shift(dest, src, 0, data_size);
#endif
}
