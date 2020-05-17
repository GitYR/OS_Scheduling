#ifndef THREADS_LOADER_H
#define THREADS_LOADER_H

#define LOADER_BASE 0x7c00     
#define LOADER_END  0x7e00      

#define LOADER_KERN_BASE 0x20000

#define LOADER_PHYS_BASE 0xc0000000 

#define LOADER_SIG (LOADER_END - LOADER_SIG_LEN)   
#define LOADER_PARTS (LOADER_SIG - LOADER_PARTS_LEN)   
#define LOADER_ARGS (LOADER_PARTS - LOADER_ARGS_LEN)   
#define LOADER_ARG_CNT (LOADER_ARGS - LOADER_ARG_CNT_LEN) 

#define LOADER_SIG_LEN 2
#define LOADER_PARTS_LEN 64
#define LOADER_ARGS_LEN 128
#define LOADER_ARG_CNT_LEN 4

#define SEL_NULL        0x00   
#define SEL_KCSEG       0x08   
#define SEL_KDSEG       0x10   

#ifndef __ASSEMBLER__
#include <stdint.h>

extern uint32_t init_ram_pages;
#endif

#endif 
