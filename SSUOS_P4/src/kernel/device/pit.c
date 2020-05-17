
#include <device/pit.h>
#include <device/io.h>
#include <interrupt.h>

void init_pit(void)  
{
	enum intr_level old_level = intr_disable();
	outb(PIT_COMMAND, (PIT_COUNTER0 | PIT_RW_LMBYTE | PIT_MODE2 | PIT_BINARY) );
	outb(PIT_CHANNEL0, (PIT_HZ/PIT_FRQ_HZ)%0xff);
	outb(PIT_CHANNEL0, (PIT_HZ/PIT_FRQ_HZ)>>8);
	intr_set_level (old_level);
}
