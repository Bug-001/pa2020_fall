#include "cpu/instr.h"
#include "cpu/modrm.h"

static int call_near_(bool indirect, uint32_t eip)
{
    OPERAND opr_push, opr_call;
    int len = 1;
    opr_push.data_size = opr_call.data_size = data_size;
    
    if(!indirect)
    {
        // eIP = (eIP + rel) & (0xFFFFFFFF >> (32 - data_size))
        opr_call.type = OPR_IMM;
    	opr_call.sreg = SREG_CS;
    	opr_call.addr = cpu.eip + 1;
    	operand_read(&opr_call);
    	len += opr_call.data_size / 8;
    	print_asm_1("call", "", len, &opr_call);
        cpu.eip = (cpu.eip + len + opr_call.val) & (0xFFFFFFFF >> (32 - data_size));
    }
    else
    {
        // eIP = r/m & (0xFFFFFFFF >> (32 - data_size))
        len += modrm_rm(eip + 1, &opr_call);
        operand_read(&opr_call);
        print_asm_1("call", "", len, &opr_call);
        cpu.eip = opr_call.val & (0xFFFFFFFF >> (32 - data_size));
    }

    // push(eIP);
    cpu.esp -= data_size / 8;
    opr_push.sreg = SREG_DS;
    opr_push.type = OPR_MEM;
    opr_push.addr = cpu.esp;
    opr_push.val = eip + len;
    operand_write(&opr_push);
    
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