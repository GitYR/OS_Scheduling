#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define HLT()  __asm__ __volatile("hlt");

#include <type.h>

#define INTR_MAX	256
#define TIMER_MAX	30
#define REFRESH_FPS	20
#define CODE_SEGMENT	0x08

enum intr_level
{
	INTR_OFF,
	INTR_ON 
};

enum intr_level intr_get_level (void);
enum intr_level intr_set_level (enum intr_level);
enum intr_level intr_enable (void);
enum intr_level intr_disable (void);

#pragma pack(push, 1)

struct intr_frame
{
	uint32_t edi; 
	uint32_t esi; 
	uint32_t ebp; 
	uint32_t esp_dummy; 
	uint32_t ebx; 
	uint32_t edx; 
	uint32_t ecx; 
	uint32_t eax; 
	uint16_t gs, :16;
	uint16_t fs, :16;
	uint16_t es, :16;
	uint16_t ds, :16;

	uint32_t vec_no;
    uint32_t error_code; 

	void *frame_pointer;

	void (*eip) (void);
	uint16_t cs, :16;
	uint32_t eflags;
	void *esp; 
	uint16_t ss, :16; 
};

#pragma pack(pop)

typedef void intr_handler_func (struct intr_frame *);
bool intr_context (void);
void do_sched_on_return(void);

int init_intr(void);
void reg_handler(unsigned short idx, intr_handler_func *handler);
unsigned long get_ticks(void);

#ifndef __ASSEMBLER__
#endif

#endif
