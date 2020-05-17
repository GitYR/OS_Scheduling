#include <ssulib.h>
#include <device/io.h>
#include <syscall.h>

int strncmp(char* b1, char* b2, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		char c = b1[i] - b2[i];
		if(c)
			return c;
		if(b1[i] == 0)
			return 0;
	}
	return 0;
}

char getchar()
{
	return ssuread();
}

int getToken(char* buf, int len)
{
	char* stopper = " \t\n";
	int off = 0;
	while(1)
	{
		char c = -1;
		char *p;
		while(c == -1)
		{
			c = ssuread();
		}

		p = stopper;
		while(*p != 0)
		{
			if(*p == c)
			{
				buf[off++] = 0;
				return off;
			}
			p++;
		}

		buf[off++] = c;
		if(off >= len)
		{
			return off;
		}
	}
}
