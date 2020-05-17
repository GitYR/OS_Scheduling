#include <device/io.h>
#include <mem/mm.h>
#include <mem/paging.h>
#include <device/console.h>
#include <proc/proc.h>
#include <interrupt.h>
#include <mem/palloc.h>
#include <ssulib.h>

uint32_t *PID0_PAGE_DIR;

intr_handler_func pf_handler;

uint32_t scale_up(uint32_t base, uint32_t size)
{
	uint32_t mask = ~(size-1);
	if(base & mask != 0)
		base = base & mask + size;
	return base;
}

uint32_t scale_down(uint32_t base, uint32_t size)
{
	uint32_t mask = ~(size-1);
	if(base & mask != 0)
		base = base & mask - size;
	return base;
}

void init_paging()
{
	uint32_t *page_dir = palloc_get_page();
	uint32_t *page_tbl = palloc_get_page();
	PID0_PAGE_DIR = page_dir;

	int NUM_PT, NUM_PE;
	uint32_t cr0_paging_set;
	int i;

	NUM_PE = mem_size() / PAGE_SIZE;
	NUM_PT = NUM_PE / 1024;

	printk("-PE=%d, PT=%d\n", NUM_PE, NUM_PT);
	printk("-page dir=%x page tbl=%x\n", page_dir, page_tbl);

	page_dir[0] = (uint32_t)page_tbl | PAGE_FLAG_RW | PAGE_FLAG_PRESENT;
	
	NUM_PE = KERNEL_HEAP / PAGE_SIZE;

	for ( i = 0; i < NUM_PE; i++ ) {
		page_tbl[i] = (PAGE_SIZE * i)
			| PAGE_FLAG_RW
			| PAGE_FLAG_PRESENT;
	}

	cr0_paging_set = read_cr0() | CR0_FLAG_PG;	

	write_cr3( (unsigned)page_dir );		
	write_cr0( cr0_paging_set );         

	reg_handler(14, pf_handler);
}

void memcpy_hard(void* from, void* to, uint32_t len)
{
	write_cr0( read_cr0() & ~CR0_FLAG_PG);

	memcpy(from, to, len);

	write_cr0( read_cr0() | CR0_FLAG_PG);
}

uint32_t* get_cur_pd()
{
	return (uint32_t*)read_cr3();
}

uint32_t pde_idx_addr(uint32_t* addr)
{
	uint32_t ret = ((uint32_t)addr & PAGE_MASK_PDE) >> PAGE_OFFSET_PDE;
	return ret;
}

uint32_t pte_idx_addr(uint32_t* addr)
{
	uint32_t ret = ((uint32_t)addr & PAGE_MASK_PTE) >> PAGE_OFFSET_PTE;
	return ret;
}

uint32_t* pt_pde(uint32_t pde)
{
	uint32_t * ret = (uint32_t*)(pde & PAGE_MASK_BASE);
	return ret;
}

uint32_t* pt_addr(uint32_t* addr)
{
	uint32_t idx = pde_idx_addr(addr);
	uint32_t* pd = get_cur_pd();
	return pt_pde(pd[idx]);
}

uint32_t* pg_addr(uint32_t* addr)
{
	uint32_t *pt = pt_addr(addr);
	uint32_t idx = pte_idx_addr(addr);
	uint32_t *ret = (uint32_t*)(pt[idx] & PAGE_MASK_BASE);
	return ret;
}

uint32_t pt_copy(uint32_t *pd, uint32_t *dest_pd, uint32_t idx, uint32_t* start, uint32_t* end, bool share)
{
	uint32_t *pt = pt_pde(pd[idx]);
	uint32_t *new_pt;
	uint32_t *pte_s = start;
	uint32_t *pte_e = end;
	uint32_t s, e, i;
	uint32_t size = PAGE_SIZE;

	new_pt = palloc_get_page();
	dest_pd[idx] = (uint32_t)new_pt | (pd[idx] & ~PAGE_MASK_BASE & ~PAGE_FLAG_ACCESS);

	if(start == end)
		return 0;

	pte_s = (uint32_t*)scale_down((uint32_t)pte_s, size);
	pte_e = (uint32_t*)scale_up((uint32_t)pte_e, size);

	s = pte_idx_addr(pte_s);
	e = pte_idx_addr(pte_e);

	if(e == 0 && start != end)
		e = PAGE_TBL_SIZE/sizeof(uint32_t);

	for(i = s; i<e; i++)
	{
		if(pt[i] & PAGE_FLAG_PRESENT)
		{
			if(!share)
			{
				uint32_t* pg = palloc_get_page();
				new_pt[i] = (uint32_t)pg | (pt[i] & ~PAGE_MASK_BASE & ~PAGE_FLAG_ACCESS);
				memcpy_hard((void*)(pt[i] & PAGE_MASK_BASE), (void*)pg, PAGE_SIZE);
			}
			else
				new_pt[i] = pt[i];
		}
	}
	return dest_pd[idx];
}

void pd_copy(uint32_t* from, uint32_t* to, uint32_t* start, uint32_t* end, bool share)
{
	uint32_t *pde_s = start;
	uint32_t *pde_e = end;
	uint32_t s, e, i;
	uint32_t size = PAGE_SIZE * PAGE_TBL_SIZE/sizeof(uint32_t);

	pde_s = (uint32_t*)scale_down((uint32_t)pde_s, size);
	pde_e = (uint32_t*)scale_up((uint32_t)pde_e, size);

	s = pde_idx_addr(pde_s);
	e = pde_idx_addr(pde_e);

	for(i = s; i<e; i++)
	{
		if(from[i] & PAGE_FLAG_PRESENT)
			pt_copy(from, to, i, start, end, share);
	}
}

uint32_t* pd_create (pid_t pid)
{
	uint32_t *pd = palloc_get_page();
	pd_copy(PID0_PAGE_DIR, pd, (uint32_t*)0, (uint32_t*)KERNEL_HEAP, true);
	return pd;
}

void pf_handler(struct intr_frame *iframe)
{
	void *fault_addr;

	asm ("movl %%cr2, %0" : "=r" (fault_addr));

	printk("Page fault : %X\n",fault_addr);
	while(1)
		;
}
