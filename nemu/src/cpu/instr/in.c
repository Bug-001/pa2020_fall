#include "cpu/instr.h"
#include "device/port_io.h"

static int in(int size)
{
    OPERAND DX, A;
    DX.type = OPR_REG;
    DX.addr = REG_DX;
    DX.data_size = 16;
    A.type = OPR_REG;
    A.addr = REG_EAX;
    A.data_size = size;
    
    print_asm_2("in", "", 1, &DX, &A);
    
    operand_read(&DX);
    A.val = pio_read(DX.val, size / 8);
    operand_write(&A);
    
    return 1;
}

make_instr_func(in_b)
{
    return in(8);
}

make_instr_func(in_v)
{
    return in(data_size);
}