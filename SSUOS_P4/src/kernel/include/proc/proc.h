#ifndef		__PROC_H__
#define		__PROC_H__

#include <list.h>

#define PROC_NUM_MAX 16
#define RQ_NQS 25
#define RQ_PPQ 4

typedef int pid_t;

/* it assigns the number between zero to last element's index number. */
enum p_state {
	PROC_UNUSED, 
	PROC_RUN,    
	PROC_STOP,   
	PROC_ZOMBIE, 
	PROC_BLOCK, 
};

#pragma pack(push, 1)

struct proc_option
{
	unsigned priority;
};

struct process
{
	pid_t pid;		// process id
	void *stack;	// stack for esp
	void *pd;	    //  
	enum p_state state;
	struct process* parent; // current process's parent
	int simple_lock;	
	int child_pid; // save the child process's id
	int exit_status; 
	unsigned member;
	unsigned long long time_sleep;

	unsigned priority;	
	unsigned time_slice; // time quantum
	unsigned long long time_used;

	struct list_elem elem_all;	
	struct list_elem elem_stat;	
};

#pragma pack(pop)

extern struct list runq[RQ_NQS]; // it is declared in proc.c
extern struct process *cur_process; // "
extern unsigned long proc_ticks;

typedef void proc_func(void* aux);
proc_func print_pid;	
proc_func idle;	

void schedule(void);
struct process* sched_find_set();

void init_proc(void);
void proc_free(void);
pid_t proc_create(proc_func func, struct proc_option *priority, void* aux);
void recalculate_priority(void);
void proc_wake(void);
void proc_sleep(unsigned ticks);	
void proc_block(void);
void proc_unblock(struct process* proc);
void proc_print_data(void);

#endif
