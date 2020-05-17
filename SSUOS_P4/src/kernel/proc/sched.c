#include <list.h>
#include <proc/sched.h>
#include <mem/malloc.h>
#include <proc/proc.h>
#include <proc/switch.h>
#include <interrupt.h>

_Bool check;
extern struct list plist;
extern struct list rlist;
extern struct list runq[RQ_NQS];

extern struct process procs[PROC_NUM_MAX];
extern struct process *idle_process;
struct process *latest;

bool more_prio(const struct list_elem *a, const struct list_elem *b,void *aux);
int scheduling; 					// interrupt.c

struct process* get_next_proc(void) 
{
	int i;
	bool found = false;
	struct process *next = NULL;
	struct list_elem *elem;

	check = 0;

	if(cur_process != idle_process) // if scheduling process is not an idle process
		return idle_process;

	for(elem = list_begin(&plist); elem != list_end(&plist); elem = list_next(elem))
	{
		struct process * p = list_entry(elem,struct process,elem_all);
		
		if(p->state == PROC_RUN && p->pid != 0)
		{
			printk("#= %d p= %4d c= %4d u= %4d ", p->pid, p->priority, p->time_slice, p->time_used);
			check = 1;
		}
	}

	if(check)
		printk("\n");

	for(i = 0; i < RQ_NQS; i++)
	{
		for(elem = list_begin(&runq[i]); elem != list_end(&runq[i]); elem = list_next(elem))
		{
			struct process * p = list_entry(elem,struct process,elem_stat);

			if(p->state == PROC_RUN)
			{
				return p;
			}
		}
	}

	return next;
}

void schedule(void)
{
	struct process *cur;
	struct process *next;
	struct list_elem * elem;

	intr_disable(); // stop a timer_handler
	
	proc_wake(); 

	next = get_next_proc();
	if(next->state == PROC_RUN && next != idle_process)
		printk("Selected # =  %2d\n", next->pid);
	cur = cur_process;
	cur_process = next;
	cur_process->time_slice = 0;

	switch_process(cur, next);
	intr_enable();  // restart a timer_handler
}
