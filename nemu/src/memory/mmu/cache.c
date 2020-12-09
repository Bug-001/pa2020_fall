#include "memory/mmu/cache.h"

#include <time.h>
#include <stdlib.h>

#ifdef CACHE_ENABLED

extern uint32_t hw_mem_read(paddr_t paddr, size_t len);
extern void hw_mem_write(paddr_t paddr, size_t len, uint32_t data);

uint64_t hw_mem_access_time_cache = 0;
uint64_t hw_mem_access_time_no_cache = 0;

typedef uint8_t Block[BLOCK_SIZE];

typedef struct CacheLine
{
    uint8_t valid_bit : 1;
    uint32_t tag : 14;
    Block data;
}Line;

typedef Line LineSet[8];

LineSet cache[NR_CACHE_SET];

static inline uint32_t get_tag(uint32_t addr)
{
    return (addr >> 13) & 0x3FFFF; // 14 bits
}

static inline uint32_t get_set_index(uint32_t addr)
{
    return (addr >> 6) & 0x7F; // 7 bits
}

static inline uint32_t get_inblock_addr(uint32_t addr)
{
    return addr & 0x3F; // 6 bits
}

// init the cache
void init_cache()
{
    for(int i = 0; i < NR_CACHE_SET; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            cache[i][j].valid_bit = 0;
        }
    }
}

static void load_block(paddr_t paddr, Line* line)
{
    paddr_t baddr = paddr & (0xFFFFFFFF << 6);
    for(int j = 0; j < BLOCK_SIZE; j += 4){
        uint32_t temp = hw_mem_read(baddr + j, 4);
        memcpy(line->data + j, &temp, 4);
    }
    line->tag = get_tag(paddr);
    line->valid_bit = 1;
}

static uint32_t read_line(uint32_t inblock_addr, Line* line, size_t len)
{
    uint32_t ret = 0;
    memcpy(&ret, line->data + inblock_addr, len);
    return ret;
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{
    assert(len == 1 || len == 2 || len == 4);
    hw_mem_access_time_no_cache += MISS_ACCESS_TIME;
    uint32_t set_index = get_set_index(paddr);
    uint32_t tag = get_tag(paddr);
    uint32_t inblock_addr = get_inblock_addr(paddr);
    Line* ls = cache[set_index];
    for(int i = 0; i < 8; ++i)
    {
        if(ls[i].valid_bit == 1 && ls[i].tag == tag)
        {
            // HIT
            // Write through
            hw_mem_access_time_cache += MISS_ACCESS_TIME;
            memcpy(ls[i].data + inblock_addr, &data, len);
            hw_mem_write(paddr, len, data);
            return;
        }
    }
    // MISS
    // Write not allocate
    hw_mem_access_time_cache += MISS_ACCESS_TIME;
    hw_mem_write(paddr, len, data);
    return;
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
    assert(len == 1 || len == 2 || len == 4);
    hw_mem_access_time_no_cache += MISS_ACCESS_TIME;
    uint32_t set_index = get_set_index(paddr);
    uint32_t tag = get_tag(paddr);
    uint32_t inblock_addr = get_inblock_addr(paddr);
    Line* ls = cache[set_index];
    for(int i = 0; i < 8; ++i)
    {
        if(ls[i].valid_bit == 1 && ls[i].tag == tag)
        {
            // HIT
            hw_mem_access_time_cache += HIT_ACCESS_TIME;
            return read_line(inblock_addr, ls + i, len);
        }
    }
    // MISS
    hw_mem_access_time_cache += MISS_ACCESS_TIME;
    for(int i = 0; i < 8; ++i)
    {
        if(ls[i].valid_bit == 0)
        {
            load_block(paddr, ls + i);
            return read_line(inblock_addr, ls + i, len);
        }
    }
    // cache set full
    srand((unsigned)time(NULL));
    int i = rand() % 8;
    load_block(paddr, ls + i);
    return read_line(inblock_addr, ls + i, len);
}

#endif