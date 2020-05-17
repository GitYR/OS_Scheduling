#include <interrupt.h>
#include <device/console.h>
#include <type.h>
#include <device/pit.h>
#include <proc/sched.h>
#include <device/io.h>
#include <device/kbd.h>
#include <proc/proc.h>
#include <ssulib.h>
#include <proc/switch.h>
#include <syscall.h>

#pragma pack(push, 1)

typedef struct _ID
{
	unsigned short LowOffset;
	unsigned short CodeSelector;
	unsigned short Type;
	unsigned short HighOffset;
} _ID;

typedef struct _IDTR
{
	unsigned short Size;
	unsigned long Address;
} _IDTR;
#pragma pack(pop)

#ifndef ASSERT
#define ASSERT(CONDITION) ( (void*) 0)
#endif

static unsigned long ticks;
intr_handler_func *handlers[INTR_MAX];
bool sched_on_return;
static bool in_external_intr;  
_ID     *idt;
extern int scheduling;
unsigned long proc_ticks;

typedef void intr_stub_func (void);
void default_handler(struct intr_frame *iframe);
void timer_handler(struct intr_frame *iframe);
void syscall_handler(struct intr_frame *iframe);
void intr_exit (void);
extern intr_stub_func *intr_stubs[INTR_MAX];

int init_intr(void)
{
	int i;
	_IDTR   IDTR;
	ticks = 0;
	in_external_intr = false;
	sched_on_return = false;
	enum intr_level old_level = intr_disable();

	__asm__ __volatile("sidt %0"::"m" (IDTR));
	printk("idtr size : %d address : 0x%x\n", IDTR.Size, IDTR.Address);
	idt = (_ID *)IDTR.Address;

	for(i = 0; i < INTR_MAX; i++)
	{
		idt[i].LowOffset = (unsigned short)((unsigned long)intr_stubs[i] & 0xffff);
		idt[i].CodeSelector = (unsigned short)CODE_SEGMENT;
		idt[i].Type = (unsigned short)0x8e00;     
		idt[i].HighOffset = (unsigned short)(((unsigned long)intr_stubs[i] >> 16) & 0xffff);

		handlers[i] = default_handler;
	}

	reg_handler(32, timer_handler);
	printk("%s", "Timer Handler Registration\n");
	printk("%s", "Keyboard Handler Registration\n");

	reg_handler(0x30, syscall_handler);
	printk("%s", "System Call Handler Registration\n");

	intr_set_level (old_level);
	return 1;
}

void intr_common(struct intr_frame *iframe)
{
	in_external_intr = iframe->vec_no >= 0x20 && iframe->vec_no < 0x30;

	if(in_external_intr)
	{
		ASSERT (intr_get_level () == INTR_OFF);
		sched_on_return = false;
	}

	if(handlers[iframe->vec_no] != NULL)
		handlers[iframe->vec_no](iframe);
	else
		default_handler(iframe);

	if(in_external_intr)
	{
		ASSERT (iframe->vec_no >= 0x20 && iframe->vec_no < 0x30);
		in_external_intr = false;
		outb(0x20, 0x20);

		if(iframe->vec_no >= 0x28)
			outb(0xa0, 0x20);

		if(sched_on_return)
			schedule();
	}
}

void do_sched_on_return(void)
{
	ASSERT (intr_context ());
	sched_on_return = true; // to execute scheduling on external interrupt
}

void reg_handler(unsigned short idx, intr_handler_func *handler) 
{
	enum intr_level old_level = intr_disable();
	handlers[idx] = handler;

	intr_set_level (old_level);
	return;
}

#define FLAG_MBS  0x00000002
#define FLAG_IF   0x00000200

enum intr_level intr_get_level (void) 
{
	uint32_t flags;
	asm volatile ("pushfl; popl %0" : "=g" (flags));
	return flags & FLAG_IF ? INTR_ON : INTR_OFF;
}

enum intr_level intr_set_level (enum intr_level level) 
{
	return level == INTR_ON ? intr_enable () : intr_disable ();
}

enum intr_level intr_enable (void) 
{
	enum intr_level old_level = intr_get_level ();
	ASSERT (!intr_context ());

	asm volatile ("sti");

	return old_level;
}

enum intr_level intr_disable (void) 
{
	enum intr_level old_level = intr_get_level ();

	asm volatile ("cli" : : : "memory");

	return old_level;
}

bool intr_context (void)
{
	return in_external_intr;
}

unsigned long get_ticks(void)
{
	return ticks;
}

void default_handler(struct intr_frame *iframe)
{
	printk("\n\nint intr %d\n\n", iframe->vec_no);
}

/*
You should modify this function...
'the tick of process' SHOULD NOT increase during context switching.
*/

void timer_handler(struct intr_frame *iframe)
{
	ticks++;	

	// Add like this.
	if(cur_process->state == PROC_RUN)
	{
		cur_process->time_slice++;
		cur_process->time_used++;
	}

	if(!(cur_process->time_slice % TIMER_MAX))
		recalculate_priority(); // move recalculate function to here

	if(cur_process->time_slice >= (TIMER_MAX*2))
		do_sched_on_return(); 

#ifdef SCREEN_SCROLL
	static unsigned long refresh_ticks = 0;
	if(++refresh_ticks >= (PIT_FRQ_HZ/REFRESH_FPS)) {
		refresh_ticks = 0;
		refreshScreen();
	}
#endif
}

void syscall_handler(struct intr_frame *iframe)
{
	long sys_num, arg_num, ret;
	int *pt;
	int i;

#define SYSCALL_ARG_MAX 3
	long arg[SYSCALL_ARG_MAX];

	pt = (int*) (((int)&iframe->ss) - 4);
	sys_num = *pt++;
	arg_num = syscall_tbl[sys_num][1];

	for(i = 0; i<arg_num; i++)
		arg[i] = *pt++;

	switch(arg_num)
	{
		case 0:
			ret = ((int(*)(void))syscall_tbl[sys_num][0])();
			break;
		case 1:
			ret = ((int(*)(int))syscall_tbl[sys_num][0])(arg[0]);
			break;
		case 2:
			ret = ((int(*)(int, int))syscall_tbl[sys_num][0])(arg[0], arg[1]);
			break;
		case 3:
			ret = ((int(*)(int, int, int))syscall_tbl[sys_num][0]) (arg[0], arg[1], arg[2]);
			break;
	}
	
	*(pt + 3) = ret;		
}
