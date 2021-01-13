#include "cpu/instr.h"
#include "device/port_io.h"

static int out(int size)
{
    OPERAND DX, A;
    DX.type = OPR_REG;
    DX.addr = REG_DX;
    DX.data_size = 16;
    A.type = OPR_REG;
    A.addr = REG_EAX;
    A.data_size = size;
    
    print_asm_2("out", "", &DX, &A);
    
    operand_read(&A);
    operand_read(&DX);
    pio_write(DX.val, size, A.val);
    
    return 1;
}

make_instr_func(out_b)
{
    return out(8);
}

make_instr_func(out_v)
{
    return out(data_size);
}
