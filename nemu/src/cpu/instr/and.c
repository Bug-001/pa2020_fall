#include "cpu/instr.h"
#include "cpu/alu.h"

static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    uint32_t opr_src_temp = sign_ext(opr_src.val, 32);
    printf("opr_src.val == %x\n", opr_src.val);
    printf("opr_src_temp == %x\n", opr_src_temp);
    fflush(stdout);
    // uint32_t opr_src_temp = sign_ext(opr_src.val, opr_dest.data_size);
    opr_dest.val = alu_and(opr_src_temp, opr_dest.val, opr_dest.data_size);
    operand_write(&opr_dest);
}

fc_make_instr_impls(and)