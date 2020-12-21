#include "cpu/cpu.h"
#include "memory/memory.h"

#ifdef IA32_PAGE
// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{

#ifndef TLB_ENABLED
    printf("laddr = 0x%08x, Page Translate!\n", laddr);
    fflush(stdout);
    
	uint32_t dir = laddr >> 22; // 高10位
	uint32_t page = (laddr & 0x3FFFFF) >> 12; // 中间10位
	uint32_t offset = laddr & 0xFFF;
	
	printf("cpu.cr3.base = 0x%05x\n", cpu.cr3.base);
	fflush(stdout);
	
	PDE* page_dir = (void*)(get_mem_addr() + (cpu.cr3.base << 12));
	page_dir += dir;
	
	printf("page_dir = 0x%08x\n", page_dir->val);
	fflush(stdout);
	
	assert(page_dir->present == 1);
	PTE* page_table = (void*)(get_mem_addr() + (page_dir->page_frame << 12));
	page_table += page;
	assert(page_table->present == 1);
	
	printf("Page Translate OK, paddr = 0x%08x\n", (page_table->page_frame << 12) + offset);
	fflush(stdout);
	
	return (page_table->page_frame << 12) + offset;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif

}
#endif
