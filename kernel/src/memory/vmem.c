#include "common.h"
#include "memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)
#define NR_PT ((SCR_SIZE + PT_SIZE - 1) / PT_SIZE) // number of page tables to cover the vmem
#define NR_VPT ((SCR_SIZE + PAGE_SIZE - 1) / PAGE_SIZE)

PDE *get_updir();
PTE vmem_table[NR_PTE] align_to_page;

void create_video_mapping()
{
	/* create an identical mapping from virtual memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memeory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */
    PDE* pdir = get_updir();
    pdir[VMEM_ADDR / PT_SIZE].val = make_pde(va_to_pa(vmem_table));
    uint32_t pframe_idx = VMEM_ADDR >> 12;
    PTE* ptable = vmem_table + (pframe_idx & 0x3ff);
    for(int cnt = 0; cnt < NR_VPT; ++cnt)
    {
        ptable->val = make_pte(pframe_idx << 12);
        ++pframe_idx;
        ++ptable;
    }
}

void video_mapping_write_test()
{
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for (i = 0; i < SCR_SIZE / 4; i++)
	{
		buf[i] = i;
	}
}

void video_mapping_read_test()
{
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for (i = 0; i < SCR_SIZE / 4; i++)
	{
		assert(buf[i] == i);
	}
}

void video_mapping_clear()
{
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}
