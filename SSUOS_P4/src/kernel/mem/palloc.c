#include <mem/palloc.h>
#include <bitmap.h>
#include <type.h>
#include <round.h>
#include <mem/mm.h>
#include <synch.h>
#include <device/console.h>
#include <mem/paging.h>

struct pool
{
	struct lock lock;  
	struct bitmap *used_map; 
	uint32_t *base; 
};

static struct pool mem_pool;

static void init_pool (struct pool *, void *base, size_t page_cnt,
		const char *name);

void init_palloc (void) 
{
	uint32_t *free_start = (uint32_t*)KERNEL_ADDR;
	uint32_t *free_end = (uint32_t*)mem_size();
	size_t free_pages = ((unsigned int)free_end - (unsigned int)free_start) / PAGE_SIZE;

	init_pool (&mem_pool, free_start, free_pages, "memory pool"); 
}

uint32_t * palloc_get_multiple (size_t page_cnt)
{
	struct pool *pool = &mem_pool;  
	void *pages;
	size_t page_idx;

	if (page_cnt == 0)
		return NULL;

	lock_acquire (&pool->lock);  
	page_idx = bitmap_scan_and_flip (pool->used_map, 0, page_cnt, false);
	lock_release (&pool->lock);  

	if (page_idx != BITMAP_ERROR)
		pages = pool->base + PAGE_SIZE * page_idx/sizeof(uint32_t);
	else 
		pages = NULL;

	if (pages != NULL) 
	{
		memset (pages, 0, PAGE_SIZE * page_cnt);
	}

	return (uint32_t*)pages; 
}

uint32_t * palloc_get_page (void) 
{
	return palloc_get_multiple (1);
}

void palloc_free_multiple (void *pages, size_t page_cnt) 
{
	struct pool *pool;
	size_t page_idx;

	if (pages == NULL || page_cnt == 0)
		return;

	pool = &mem_pool;

	page_idx = pg_no (pages) - pg_no (pool->base); 

	bitmap_set_multiple (pool->used_map, page_idx, page_cnt, false);
}

void palloc_free_page (void *page) 
{
	palloc_free_multiple (page, 1);
}

static void init_pool (struct pool *p, void *base, size_t page_cnt, const char *name) 
{
	size_t bm_pages = DIV_ROUND_UP (bitmap_buf_size (page_cnt), PAGE_SIZE);
	if (bm_pages > page_cnt) 
		printk("Not enough memory in %s for bitmap.", name);
	page_cnt -= bm_pages;  

	printk ("%u pages available in %s.\n", page_cnt, name);

	lock_init (&p->lock);  
	p->used_map = bitmap_create_in_buf (page_cnt, base, bm_pages * PAGE_SIZE); 
	p->base = base + bm_pages * PAGE_SIZE; 
}