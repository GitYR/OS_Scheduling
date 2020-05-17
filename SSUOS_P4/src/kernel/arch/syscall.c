#include <syscall.h>
#include <do_syscall.h>
#include <proc/proc.h>


#define syscall0(SYS_NUM) ({				\
		int ret;							\
		__asm__ __volatile(					\
				"pushl %[num]\n\t"			\
				"int $0x30\n\t"				\
				"addl %%esp, 4"				\
				:							\
				: [num] "g" (SYS_NUM)		\
				);							\
		ret;								\
		})

#define syscall1(SYS_NUM, ARG0) ({				\
		int ret;								\
		__asm__ __volatile(						\
				"pushl %[arg0] \n\t"			\
				"pushl %[num] \n\t"				\
				"int $0x30\n\t"					\
				"addl %%esp, 8"					\
				:								\
				: [num] "g" (SYS_NUM),			\
				[arg0] "g" (ARG0)				\
				);								\
		ret;									\
		})

#define syscall2(SYS_NUM, ARG0, ARG1) ({		\
		int ret;								\
		__asm__ __volatile(						\
				"pushl %[arg1] \n\t"			\
				"pushl %[arg0] \n\t"			\
				"pushl %[num] \n\t"				\
				"int $0x30\n\t"					\
				"addl %%esp, 12"				\
				:								\
				: [num] "g" (SYS_NUM),			\
				[arg0] "g" (ARG0),				\
				[arg1] "g" (ARG1)				\
				);								\
		ret;									\
		})

#define syscall3(SYS_NUM, ARG0, ARG1, ARG2) ({	\
		int ret;								\
		__asm__ __volatile(						\
				"pushl %[arg2] \n\t"			\
				"pushl %[arg1] \n\t"			\
				"pushl %[arg0] \n\t"			\
				"pushl %[num] \n\t"				\
				"int $0x30\n\t"					\
				"addl %%esp, 16"				\
				:								\
				: [num] "g" (SYS_NUM),			\
				[arg0] "g" (ARG0),				\
				[arg1] "g" (ARG1),				\
				[arg2] "g" (ARG2)				\
				);								\
		ret;									\
		})

int syscall_tbl[SYS_NUM][2];

#define REGSYS(NUM, FUNC, ARG) \
	syscall_tbl[NUM][0] = (int)FUNC; \
syscall_tbl[NUM][1] = ARG; 


void init_syscall(void)
{
	REGSYS(SYS_FORK, do_fork, 2);
	REGSYS(SYS_EXIT, do_exit, 1);
	REGSYS(SYS_WAIT, do_wait, 1);
	REGSYS(SYS_SSUREAD, do_ssuread, 0);
	REGSYS(SYS_SHUTDOWN, do_shutdown, 0);
}

void exit(int status)
{
	syscall1(SYS_EXIT, status);
}

pid_t fork(proc_func func, void* aux)
{
	return syscall2(SYS_FORK, func, aux);
}

pid_t wait(int *status)
{
	return syscall1(SYS_WAIT, status);
}

int ssuread()
{
	return syscall0(SYS_SSUREAD);
}

void shutdown(void)
{
	syscall0(SYS_SHUTDOWN);
}
