#include "memory/mmu/cache.h"

#define BLOCK_SIZE 0x40
#define NR_CACHE_SET 0x80

typedef uint8_t Block[BLOCK_SIZE];

struct CacheLine
{
    uint8_t valid_bit : 1;
    uint32_t tag : 14;
    Block data;
};

typedef struct CacheLine CacheSet[8];

CacheSet cache[NR_CACHE_SET];

static inline uint32_t get_tag(uint32_t addr)
{
    return (addr >> 13) & 0x3FFFF; // 14 bits
}

static inline uint32_t get_cache_set_index(uint32_t addr)
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
            //cache[i][j].valid_bit = 0;
        }
    }
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{
    printf("cache: implement me in PA 3-1\n");
    fflush(stdout);
    assert(0);
	// implement me in PA 3-1
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
    printf("cache: implement me in PA 3-1\n");
    fflush(stdout);
    assert(0);
	// implement me in PA 3-1
	return 0;
}

