#include "cpu/instr.h"
#include "cpu/modrm.h"

static int call_near_(bool indirect)
{
    // push(eIP);
    int len = 1;
    cpu.esp -= data_size / 8;
    decode_data_size_v
    if(!indirect)
    {
        // eIP = (eIP + rel) & (0xFFFFFFFF >> (32 - data_size))
        opr_src.type = OPR_IMM;
    	opr_src.sreg = SREG_CS;
    	opr_src.addr = cpu.eip + 1;
    	len += opr_src.data_size / 8;
        operand_read(&opr_src);
        cpu.eip = (cpu.eip + opr_src.val) & (0xFFFFFFFF >> (32 - data_size));
    }
    else
    {
        // eIP = r/m & (0xFFFFFFFF >> (32 - data_size))
        len += modrm_rm(cpu.eip + 1, &opr_src);
        operand_read(&opr_src);
        cpu.eip = opr_src.val & (0xFFFFFFFF >> (32 - data_size));
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