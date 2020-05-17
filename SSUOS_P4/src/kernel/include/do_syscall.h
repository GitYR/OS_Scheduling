#ifndef	   __DO_SYSCALL_H__
#define	   __DO_SYSCALL_H__

pid_t do_fork(proc_func func, void* aux);
void do_exit(int status);
pid_t do_wait(int *status);
int do_ssuread(int type, char* buf, int len);
void do_shutdown(void);

#endif
