#ifndef __KDB_H__
#define __KDB_H__

#include <type.h>
#include <interrupt.h>

#define KBDMAPSIZE 	86

#define KEY_ESC		0x1B
#define KEY_RSHIFT	0x02
#define KEY_PRTSCN	0x03
#define KEY_LALT	0x04
#define KEY_SPACE	0x05
#define KEY_CAPS	0x06
#define KEY_F1		0X07
#define KEY_F2		0x08
#define KEY_F3		0x09
#define KEY_F4		0x0A
#define KEY_F5		0x0B
#define KEY_F6		0x0C
#define KEY_F7		0x0D
#define KEY_F8		0x0E
#define KEY_F9		0x0F
#define KEY_F10		0x10
#define KEY_F11		0x11
#define KEY_F12		0x12
#define KEY_BSPACE	0x13
#define KEY_TAB		0x14

typedef struct Key_Status_Struct {
	BOOL ShiftFlag; 	
	BOOL CapslockFlag;
	BOOL NumlockFLag;
	BOOL ScrolllockFlag;

	BOOL ExtentedFlag;
	int PauseFlag;
} Key_Status;

void UpdateKeyStat(BYTE);
BOOL ConvertScancodeToASCII(BYTE, BYTE *);
void init_kbd(void);
void kbd_handler(struct intr_frame *iframe);

char kbd_read_char();
#endif
