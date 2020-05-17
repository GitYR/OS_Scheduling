#ifndef __PAGING_H__
#define __PAGING_H__

#include <type.h>
#include <proc/proc.h>

#define CR0_FLAG_PG			0x80000000
#define CR0_FLAG_PE			0x00000001

#define PAGE_FLAG_PRESENT	0x01	
#define PAGE_FLAG_RW		0x02	
#define PAGE_FLAG_USER		0x04
#define PAGE_FLAG_WRITE     0x08
#define PAGE_FLAG_CACHE     0x10
#define PAGE_FLAG_ACCESS    0x20
#define PAGE_FLAG_AVAIL     0x40
#define PAGE_FLAG_DIRTY     0x40
#define PAGE_FLAG_SIZE      0x80
#define PAGE_FLAG_PTA       0x80
#define PAGE_FLAG_GLOB      0x100
#define PAGE_ADDR_AVAIL     0x200
#define PAGE_ADDR_BASE      0x1000

#define PAGE_MASK_BASE      0xFFFFF000
#define PAGE_MASK_PDE       0xFFC00000
#define PAGE_MASK_PTE       0x003FF000
#define PAGE_OFFSET_PDE	    22
#define PAGE_OFFSET_PTE	    12

#define PAGE_SIZE			4096
#define PAGE_TBL_SIZE		4096
#define PAGE_DIR_SIZE		4096

#define KERNEL_ADDR			0x00100000
#define KERNEL_HEAP			0x00400000

static inline uint32_t pg_no(const uint32_t *page){
	return (uint32_t)page >> PAGE_OFFSET_PTE;
}

void init_paging();
uint32_t* pd_create (pid_t pid);
uint32_t pde_idx_addr(uint32_t* addr);
uint32_t pte_idx_addr(uint32_t* addr);

#endif
