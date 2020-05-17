#ifndef _SWITCH_H_
#define _SWITCH_H_

#include <proc/proc.h>
#include <type.h>

void switch_process(struct process *cur, struct process *next);

#endif 
