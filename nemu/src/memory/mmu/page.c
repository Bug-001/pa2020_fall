#include "cpu/cpu.h"
#include "memory/memory.h"

extern bool verbose;

#ifdef IA32_PAGE
// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	uint32_t dir = laddr >> 22; // 高10位
	uint32_t page = (laddr & 0x3FFFFF) >> 12; // 中间10位
	uint32_t offset = laddr & 0xFFF;
	PDE* page_dir = (void*)(get_mem_addr() + (cpu.cr3.base << 12));
	page_dir += dir;
	if(page_dir->present != 1)
	{
	    printf("page_dir->present != 1, laddr = 0x%08x\n", laddr);
	    fflush(stdout);
	    assert(page_dir->present == 1);
	}
	if(verbose){
	    printf("page_frame = 0x%x\n", page_dir->page_frame);
	    fflush(stdout);
	}
	PTE* page_table = (void*)(get_mem_addr() + (page_dir->page_frame << 12));
	page_table += page;
	if(verbose){
	    printf("page_table = 0x%x\n", (void *)page_table - (void *)get_mem_addr());
	    fflush(stdout);
	}
	assert(page_table->present == 1);
	if(page_table->present != 1)
	{
	    printf("page_table->present != 1, laddr = 0x%08x\n", laddr);
	    fflush(stdout);
	    assert(page_table->present == 1);
	}
	return (page_table->page_frame << 12) + offset;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif

}
#endif
