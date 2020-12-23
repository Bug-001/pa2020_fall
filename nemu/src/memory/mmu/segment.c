#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
    assert(cpu.segReg[sreg].base == 0);
    // assert(cpu.segReg[sreg].limit == 0xFFFFF);
    if(cpu.segReg[sreg].limit != 0xFFFFF)
    {
        printf("0x%08x\n", cpu.segReg[sreg].limit == 0xFFFFF);
        assert(0);
    }
	return cpu.segReg[sreg].base + offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	 uint32_t pdesc = cpu.gdtr.base + sizeof(SegDesc) * cpu.segReg[sreg].index;
	 SegDesc desc;
	 desc.val[0] = laddr_read(pdesc, 4);
	 desc.val[1] = laddr_read(pdesc + 4, 4);
	 fflush(stdout);
	 
	 assert(desc.present == 1);
	 assert(desc.granularity == 1);
	 cpu.segReg[sreg].base = desc.base_15_0 + (desc.base_23_16 << 16) + (desc.base_31_24 << 24);
	 assert(cpu.segReg[sreg].base == 0);
	 cpu.segReg[sreg].limit = desc.limit_15_0 + (desc.limit_19_16 << 16);
	 assert(cpu.segReg[sreg].limit == 0xFFFFF);
	 cpu.segReg[sreg].type = desc.type + (desc.segment_type << 4);
	 cpu.segReg[sreg].privilege_level = desc.privilege_level;
	 cpu.segReg[sreg].soft_use = desc.soft_use;
}
