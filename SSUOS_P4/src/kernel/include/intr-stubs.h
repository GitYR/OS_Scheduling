#ifndef _INTR_STUBS_H_
#define _INTR_STUBS_H_

#define INTR_MAX   256

typedef void intr_stub_func (void);
extern intr_stub_func *intr_stubs[INTR_MAX];

void intr_exit (void);

#endif 
