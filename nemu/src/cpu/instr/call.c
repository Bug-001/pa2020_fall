#include "cpu/instr.h"
#include "cpu/modrm.h"

static int call_near_(bool indirect, uint_32 eip)
{
    // push(eIP);
    int len = 1;
    cpu.esp -= data_size / 8;
    decode_data_size_v
    
    opr_dest.type = OPR_MEM;
    opr_dest.addr = cpu.esp;
    // opr_dest.val = cpu.eip + 1 + data_size / 8;
    opr_dest.val = eip;
    operand_write(&opr_dest);
    
    if(!indirect)
    {
        // eIP = (eIP + rel) & (0xFFFFFFFF >> (32 - data_size))
        opr_src.type = OPR_IMM;
    	opr_src.sreg = SREG_CS;
    	opr_src.addr = cpu.eip + 1;
    	len += opr_src.data_size / 8;
        operand_read(&opr_src);
        cpu.eip = (cpu.eip + opr_src.val) & (0xFFFFFFFF >> (32 - data_size));
        print_asm_1("call", "", len, &opr_src);
    }
    else
    {
        // eIP = r/m & (0xFFFFFFFF >> (32 - data_size))
        len += modrm_rm(cpu.eip + 1, &opr_src);
        operand_read(&opr_src);
        cpu.eip = opr_src.val & (0xFFFFFFFF >> (32 - data_size));
        print_asm_0("call", "", len);
    }
    
    assert(len == 1 + data_size / 8);
    cpu.eip += len;
    
    

    return 0;
}

make_instr_func(call_near)
{
    return call_near_(0, eip);
}

make_instr_func(call_near_indirect)
{
    return call_near_(1, eip);
}