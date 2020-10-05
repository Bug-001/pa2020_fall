#include "cpu/instr.h"
#include "cpu/cpu.h"

static int call_near_(bool indirect)
{
    // push(eIP);
    int len = 0;
    cpu.esp -= data_size / 8;
    decode_data_size_v
    if(!indirect)
    {
        // eIP = (eIP + rel) & (0xFFFFFFFF >> (32 - data_size))
        decode_operand_i
        operand_read(&opr_src);
        eip = (eip + opr_src.val) & (0xFFFFFFFF >> (32 - data_size));
    }
    else
    {
        // eIP = r/m & (0xFFFFFFFF >> (32 - data_size))
        decode_operand_rm
        operand_read(&opr_src);
        eip = opr_src.val & (0xFFFFFFFF >> (32 - data_size));
    }
    assert(len == 1 + data_size / 8);
    return 0;
}

make_instr_func(call_near)
{
    return call_near_(0);
}

make_instr_func(call_near_indirect)
{
    return call_near_(1);
}