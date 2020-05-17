#include <interrupt.h>
#include <device/console.h>
#include <device/block.h>
#include <type.h>
#include <device/kbd.h>
#include <device/io.h>
#include <device/pit.h>
#include <stdarg.h>
#include <ssulib.h>
#include <mem/paging.h>
#include <proc/proc.h>
#include <mem/mm.h>
#include <syscall.h>
#include <device/kbd.h>

#include <synch.h>
#include <mem/palloc.h>

extern struct process *cur_process;

void main_init(void);
void print_contributors(void);

const char* VERSION = "0.1.02";
const char* AUTHOR = "OSLAB";
const char* MODIFIER = "You";

void ssuos_main(void)
{
	main_init(); // init_proc() 

	idle(NULL); // schedule() -> get_next_proc()
	
	return;
}

void main_init(void)
{
	intr_disable();

	init_console();

	print_contributors();

	detect_mem();
	printk("%s", "Memory Detecting\n");

	init_pit();	
	printk("%s", "PIT Initialization\n");

	init_syscall();
	printk("%s", "System call Initialization\n"); 

	init_intr();
	printk("%s", "Interrupt Initialization\n"); 

	init_kbd();

	init_palloc();
	printk("%s" "Palloc Initialization\n");

	init_paging();
	printk("%s", "Paging Initialization\n"); 

	init_proc();
	printk("%s", "Process Initialization\n");

	intr_enable();

	printk("========== initialization complete ==========\n\n");


#ifdef SCREEN_SCROLL
	refreshScreen();
#endif
}

void print_contributors(void)
{
	printk("%s", "SSUOS main start!!!!\n");
	printk("          ______    ______   __    __         ______    ______  \n");
	printk("         /      \\  /      \\ /  |  /  |       /      \\  /      \\ \n");
	printk("        /$$$$$$  |/$$$$$$  |$$ |  $$ |      /$$$$$$  |/$$$$$$  |\n");
	printk("        $$ \\__$$/ $$ \\__$$/ $$ |  $$ |      $$ |  $$ |$$ \\__$$/ \n");
	printk("        $$      \\ $$      \\ $$ |  $$ |      $$ |  $$ |$$      \\ \n");
	printk("         $$$$$$  | $$$$$$  |$$ |  $$ |      $$ |  $$ | $$$$$$  |\n");
	printk("        /  \\__$$ |/  \\__$$ |$$ \\__$$ |      $$ \\__$$ |/  \\__$$ |\n");
	printk("        $$    $$/ $$    $$/ $$    $$/       $$    $$/ $$    $$/ \n");
	printk("         $$$$$$/   $$$$$$/   $$$$$$/         $$$$$$/   $$$$$$/  \n");
	printk("\n");
	printk("****************Made by OSLAB in SoongSil University*********************\n");
	printk("\n");
	printk("contributors : Yunkyu Lee  , Minwoo Jang  , Sanghun Choi , Eunseok Choi\n");
	printk("               Hyunho Ji   , Giwook Kang  , Kisu Kim     , Seonguk Lee \n");
	printk("               Gibeom Byeon, Jeonghwan Lee, Kyoungmin Kim, Myungjoon Shon\n");
	printk("               Jinwoo Lee, Hansol Lee, Mhanwoo Heo\n");
	printk("\n");
	printk("************************  Professor. Jiman Hong  ************************\n");
	printk("                                                                  \n");
}
