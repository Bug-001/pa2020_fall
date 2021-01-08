#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
    // Push EFLAGS, CS, and EIP
	cpu.esp -= 4;
	vaddr_write(cpu.esp, SREG_SS, 4, cpu.eflags.val);
	cpu.esp -= 4;
	vaddr_write(cpu.esp, SREG_SS, 4, cpu.cs);
	cpu.esp -= 4;
	vaddr_write(cpu.esp, SREG_SS, 4, cpu.eip);
	
	// Find the IDT entry using 'intr_no'
	uint32_t pdesc = cpu.idtr.base + intr_no * sizeof(GateDesc);
	GateDesc desc;
	desc.val[0] = laddr_read(pdesc, 4);
	desc.val[1] = laddr_read(pdesc + 4, 4);
	assert(desc.present == 1);
	assert(desc.pad0 == 0);
	assert(desc.privilege_level >= (cpu.cs & 0x3));
	
	// Clear IF if it is an interrupt
	if(desc.type == INTR_GATE) cpu.eflags.IF = 0;
	
	// Set EIP to the entry of the interrupt handler
	cpu.eip = (desc.offset_31_16 << 16) + desc.offset_15_0;
	cpu.cs = desc.selector;
	load_sreg(SREG_CS);
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
