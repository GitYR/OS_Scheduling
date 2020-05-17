#include <mem/mm.h>

extern unsigned long getMemSize();
unsigned long nGetMemSize();

static unsigned long MEM_SIZE;

void detect_mem()
{
	MEM_SIZE = nGetMemSize();
	return;
}

unsigned long nGetMemSize()
{
	unsigned long *pAddr = (unsigned long *)0x20000; 
	unsigned long tmp;
	while (1) {
		pAddr += (4*1024*1024);
		tmp = *pAddr;
		*pAddr = 0x12345678;
		if(*pAddr != 0x12345678) {
			pAddr -= (4*1024*1024);
			while (1) {
				pAddr += (4*1024);
				tmp = *pAddr;
				*pAddr = 0x87654321;
				if(*pAddr != 0x87654321)
					break;
				*pAddr = tmp;
			}
			break;
		}
		*pAddr = tmp;
	}         
  
	return (unsigned long)pAddr;
}

unsigned long mem_size()
{
	return MEM_SIZE;
}
