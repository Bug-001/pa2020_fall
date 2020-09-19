#include "cpu/cpu.h"

void printb(uint32_t n){
    printb(n/2);
    printf("%d", n%2);
}

void set_CF(uint32_t src, uint32_t ret, bool sub, size_t data_size)
{
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    ret = sign_ext(ret & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = ((ret < src) ^ sub);
}

void set_PF(uint32_t ret, size_t data_size)
{
    uint8_t pf = 1;
    for(uint8_t i = 8; i > 0; --i){
        pf ^= (ret & 1);
        ret >>= 1;
    }
    cpu.eflags.PF = pf;
}

// void set_AF()
// {
    
// }

void set_ZF(uint32_t ret, size_t data_size)
{
    ret = ret & (0xFFFFFFFF >> (32 - data_size));
    cpu.eflags.ZF = (ret == 0);
}

void set_SF(uint32_t ret, size_t data_size)
{
    ret = sign_ext(ret & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.SF = sign(ret);
}

void set_OF(uint32_t src, uint32_t dest, uint32_t ret, size_t data_size)
{
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    ret = sign_ext(ret & (0xFFFFFFFF >> (32 - data_size)), data_size);
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.OF = (sign(src) == sign(dest)) & (sign(src) ^ sign(ret));
}

uint32_t adder(uint32_t X, uint32_t Y, bool sub, bool useCF, size_t data_size){
    uint32_t C = useCF ? cpu.eflags.CF : sub;
    uint32_t lastC = C;
    X = sign_ext(X & (0xFFFFFFFF >> (32 - data_size)), data_size);
    Y = sign_ext(Y & (0xFFFFFFFF >> (32 - data_size)), data_size);
    if(sub) printf("Hi\n");
    if(sub){
        printb(X); printf(" ");
        printb(Y); printf("\n");
    } 
    if(sub) printf("Hi\n");
    Y = sub ? ~Y : Y;
    uint32_t result = 0;
    for(int i = data_size; i > 0; --i){
        result >>= 1;
        uint32_t x = X & 1;
        uint32_t y = Y & 1;
        result += ((x ^ y ^ C) << 31);
        if(sub){
            printb(result);
            printf("\n");
        } 
        lastC = C;
        C = ((x & y) | (x & C) | (y & C)) & 1;
        X >>= 1;
        Y >>= 1;
    }
    result >>= (32 - data_size);
    if(sub){
        printb(result); printf("\n");
    } 
    // CF
    cpu.eflags.CF = sub ^ C;
    // PF
    uint8_t pf = 1;
    uint32_t result_temp = result;
    for(uint8_t i = 8; i > 0; --i){
        pf ^= (result_temp & 1);
        result_temp >>= 1;
    }
    cpu.eflags.PF = pf;
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

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
    return adder(src, dest, 0, 0, data_size);
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
    return adder(src, dest, 0, 1, data_size);
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	return adder(src, dest, 1, 0, data_size);
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
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
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}
