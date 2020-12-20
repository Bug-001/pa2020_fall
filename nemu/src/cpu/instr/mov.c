#include "cpu/instr.h"

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_2op(mov, r, rm, b)
make_instr_impl_2op(mov, r, rm, v)
make_instr_impl_2op(mov, rm, r, b)
make_instr_impl_2op(mov, rm, r, v)
make_instr_impl_2op(mov, i, rm, b)
make_instr_impl_2op(mov, i, rm, v)
make_instr_impl_2op(mov, i, r, b)
make_instr_impl_2op(mov, i, r, v)
make_instr_impl_2op(mov, a, o, b)
make_instr_impl_2op(mov, a, o, v)
make_instr_impl_2op(mov, o, a, b)
make_instr_impl_2op(mov, o, a, v)

make_instr_func(mov_zrm82r_v) {
	int len = 1;
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_zrm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);

        operand_read(&rm);
        r.val = rm.val;
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm82r_v) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = data_size;
        rm.data_size = 8;
        len += modrm_r_rm(eip + 1, &r, &rm);
        
	operand_read(&rm);
        r.val = sign_ext(rm.val, 8);
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);
        operand_read(&rm);
        r.val = sign_ext(rm.val, 16);
        operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_rm2s_w)
{
    int len = 1;
    OPERAND rm, s;
    rm.data_size = 16;
    len += modrm_rm(eip + 1, &rm);
    operand_read(&rm);
    
    MODRM temp;
    temp.val = instr_fetch(eip + 1, 1);
    s.addr = temp.reg_opcode;
    s.type = OPR_SREG;
    s.val = rm.val;
    operand_write(&s);
    print_asm_2("mov", "", len, &rm, &s);
    return len;
}

make_instr_func(mov_cr2r_l)
{
    int len = 1;
    OPERAND cr, r;
    r.data_size = 32;
    len += modrm_rm(eip + 1, &r);
    
    MODRM temp;
    temp.val = instr_fetch(eip + 1, 1);
    cr.addr = temp.reg_opcode;
    cr.type = OPR_CREG;
    operand_read(&cr);
    
    r.val = cr.val;
    operand_write(&r);
    print_asm_2("mov", "", len, &rm, &s);
    return len;
}

make_instr_func(mov_r2cr_l)
{
    int len = 1;
    OPERAND cr, r;
    r.data_size = 32;
    len += modrm_rm(eip + 1, &rm);
    operand_read(&r);
    
    MODRM temp;
    temp.val = instr_fetch(eip + 1, 1);
    cr.addr = temp.reg_opcode;
    cr.type = OPR_CREG;
    cr.val = r.val;
    operand_write(&cr);
    print_asm_2("mov", "", len, &rm, &cr);
    return len;
}