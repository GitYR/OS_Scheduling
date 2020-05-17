#ifndef __LIB_STDDEF_H
#define __LIB_STDDEF_H

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *) 0)->MEMBER)

typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;

#endif 