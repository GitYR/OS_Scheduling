#ifndef		__PIT_H__
#define		__PIT_H__

#define PIT_CHANNEL0	0x40
#define PIT_CHANNEL1	0x41
#define PIT_CHANNEL2	0x42
#define PIT_COMMAND		0x43

#define	PIT_COUNTER0	0x00
#define PIT_COUNTER1	0x40
#define	PIT_COUNTER2	0x80
#define	PIT_READBACK	0xA0

#define	PIT_RW_COUNTER_LATCH	0x00
#define	PIT_RW_LBYTE			0x10
#define PIT_RW_MBYTE			0x20
#define	PIT_RW_LMBYTE			0x30

#define	PIT_MODE0		Ox00
#define	PIT_MODE1		0x02
#define	PIT_MODE2		0x04
#define PIT_MODE3		0x06
#define	PIT_MODE4		0x08
#define	PIT_MODE5		0x0A

#define	PIT_BINARY		0x00
#define	PIT_BCD			0x01

#define	PIT_HZ			1193181 
#define	PIT_FRQ_HZ 		1000

void init_pit(void);

#endif
