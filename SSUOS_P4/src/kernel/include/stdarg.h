#ifndef __STDARG_H__
#define __STDARG_H__

typedef char			*va_list;
	
#define _ADDRESSOF(v)	( &(v) )
#define _INTSIZEOF(n)	( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
	
#define va_start(ap,v)	( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define va_arg(ap,t)	( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)		( ap = (va_list)0 )

int strlen(const char *string);
static char *number(char * str, int num, int base, int size, int precision, int type);
static int skip_atoi(const char **s);
int vsprintk(char *buf, const char *fmt, va_list args);

#endif 