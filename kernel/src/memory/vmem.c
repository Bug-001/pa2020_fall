#include "common.h"
#include "memory.h"
#include <string.h>

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)
#define NR_PT ((SCR_SIZE + PT_SIZE - 1) / PT_SIZE) // number of page tables to cover the vmem

PDE *get_updir();

void create_video_mapping()
{
	/* create an identical mapping from virtual memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memeory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */
    PDE* pdir = get_updir();
    assert(pdir[VMEM_ARRD / PT_SIZE].present == 1);
    PTE* ptable = pdir[VMEM_ARRD / PT_SIZE].pframe_idx << 12;
    uint32_t pframe_idx = VMEM_ADDR >> 12;
    pdir[VMEM_ADDR / PT_SIZE].val = make_pde(vmem_table);
    for(int cnt = 0; cnt < NR_PT; ++cnt){
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
