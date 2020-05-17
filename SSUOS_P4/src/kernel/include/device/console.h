#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#pragma pack(push, 1)

typedef struct kChStruct
{
		unsigned char bCh;
		unsigned char bAtt;
} CHAR;

int Glob_x;
int Glob_y;

#pragma pack(pop)

#define SERIAL_STDOUT

void init_console(void);

void PrintCharToScreen(int x, int y, const char *pString);
void PrintChar(int x, int y, const char String);

void clrScreen(void);
void scroll(void);
int printk(const char *fmt, ...);

#ifdef SCREEN_SCROLL
void refreshScreen(void);
void scroll_screen(int offset);
void set_fallow(void);
#endif

#endif
