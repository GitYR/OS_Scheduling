#ifndef __SYNCH_H__
#define __SYNCH_H__

#include <list.h>
#include <type.h>


struct semaphore 
  {
      unsigned value;
      struct list waiters;
  };

void sema_init (struct semaphore *, unsigned value);
void sema_down (struct semaphore *);
bool sema_try_down (struct semaphore *);
void sema_up (struct semaphore *);
void sema_self_test (void);

struct lock 
  {
      struct process *holder;      
      struct semaphore semaphore; 
  };

void lock_init (struct lock *);
void lock_acquire (struct lock *);
bool lock_try_acquire (struct lock *);
void lock_release (struct lock *);
bool lock_held_by_current_process (const struct lock *);

struct condition 
  {
      struct list waiters; 
  };

void cond_init (struct condition *);
void cond_wait (struct condition *, struct lock *);
void cond_signal (struct condition *, struct lock *);
void cond_broadcast (struct condition *, struct lock *);

#define barrier() asm volatile ("" : : : "memory")

#endif 

