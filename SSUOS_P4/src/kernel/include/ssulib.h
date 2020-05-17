#ifndef __SSULIB_H__
#define __SSULIB_H__

#include <type.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *) 0)->MEMBER)

#define BUFSIZ 512

void memcpy(void* from, void* to, uint32_t len);
int strncmp(char* b1, char* b2, int len);
char getchar(void);
int getToken(char* buf, int len);
#endif
