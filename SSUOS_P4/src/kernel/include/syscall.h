#ifndef     __SYSCALL_H__
#define     __SYSCALL_H__

enum SYS_LIST {
	SYS_FORK = 0,
	SYS_EXIT,
	SYS_WAIT,
	SYS_SSUREAD,
	SYS_SHUTDOWN,
	SYS_NUM,
};

#include <proc/proc.h>
void init_syscall(void);

void exit(int status);
pid_t fork(proc_func func, void* aux);
pid_t wait(int *status);
int ssuread(void);
void shutdown(void);

extern int syscall_tbl[SYS_NUM][2];
#endif
