#include <synch.h>
#include <interrupt.h>
#include <proc/proc.h>
#include <device/console.h>

#ifndef ASSERT
#define ASSERT(COND) ;
#endif

void sema_init(struct semaphore *sema, unsigned value)
{
	ASSERT (sema != NULL);

	sema->value = value;
	list_init(&sema->waiters);
}

void sema_down (struct semaphore *sema) 
{
	enum intr_level old_level;

	ASSERT (sema != NULL);
	ASSERT (!intr_context ());

	old_level = intr_disable ();
	while (sema->value == 0) 
	{
		list_push_back (&sema->waiters, &cur_process->elem_stat);
		proc_block ();
	}
	sema->value--;
	intr_set_level (old_level);
}

bool sema_try_down (struct semaphore *sema) 
{
	enum intr_level old_level;

	bool success;

	ASSERT (sema != NULL);

	old_level = intr_disable ();
	if (sema->value > 0) 
	{
		sema->value--;
		success = true; 
	}
	else
		success = false;
	intr_set_level (old_level);

	return success;
}

void sema_up (struct semaphore *sema) 
{
	enum intr_level old_level;

	ASSERT (sema != NULL);

	old_level = intr_disable ();
	if (!list_empty (&sema->waiters)) 
		proc_unblock (list_entry (list_pop_front (&sema->waiters),
					struct process, elem_stat));
	sema->value++;
	intr_set_level (old_level);
}
static void sema_test_helper (void *sema_);

void sema_self_test (void) 
{
	static struct semaphore sema[2];
	int i;

	printk ("Testing semaphores...");
	sema_init (&sema[0], 0);
	sema_init (&sema[1], 0);
	proc_create (sema_test_helper, NULL, &sema);
	for (i = 0; i < 10; i++) 
	{
		sema_up (&sema[0]);
		sema_down (&sema[1]);
	}
	printk ("done.\n");
}

static void sema_test_helper (void *sema_) 
{
	struct semaphore *sema = sema_;
	int i;
	cur_process -> priority = 100;

	for (i = 0; i < 10; i++) 
	{
		sema_down (&sema[0]);
		sema_up (&sema[1]);
	}
}

void lock_init (struct lock *lock)
{
	ASSERT (lock != NULL);

	lock->holder = NULL;
	sema_init (&lock->semaphore, 1);
}

void lock_acquire (struct lock *lock)
{
	ASSERT (lock != NULL);
	ASSERT (!intr_context ());
	ASSERT (!lock_held_by_current_thread (lock));

	sema_down (&lock->semaphore);
	lock->holder = cur_process;
}

bool lock_try_acquire (struct lock *lock)
{
	bool success;

	ASSERT (lock != NULL);
	ASSERT (!lock_held_by_current_thread (lock));

	success = sema_try_down (&lock->semaphore);
	if (success)
		lock->holder = cur_process;
	return success;
}

void lock_release (struct lock *lock) 
{
	ASSERT (lock != NULL);
	ASSERT (lock_held_by_current_thread (lock));

	lock->holder = NULL;
	sema_up (&lock->semaphore);
}

bool lock_held_by_current_thread (const struct lock *lock) 
{
	ASSERT (lock != NULL);

	return lock->holder == cur_process;
}


