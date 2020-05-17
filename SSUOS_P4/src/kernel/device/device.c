#include <device/console.h>
#include <device/device.h>
#include <device/io.h>

void dev_shutdown(void)
{
	const char s[] = "Shutdown";
	const char *p;
	printk ("Powering off...\n");

	for (p = s; *p != '\0'; p++)
		outb (0x8900, *p);

	asm volatile ("cli; hlt" : : : "memory");

	printk ("still running...\n");
	for (;;);
}
