	.file	"Main.c"
	.text
.Ltext0:
	.comm	Glob_x,4,4
	.comm	Glob_y,4,4
	.globl	VERSION
	.section	.rodata
.LC0:
	.string	"0.1.02"
	.data
	.align 4
	.type	VERSION, @object
	.size	VERSION, 4
VERSION:
	.long	.LC0
	.globl	AUTHOR
	.section	.rodata
.LC1:
	.string	"OSLAB"
	.data
	.align 4
	.type	AUTHOR, @object
	.size	AUTHOR, 4
AUTHOR:
	.long	.LC1
	.globl	MODIFIER
	.section	.rodata
.LC2:
	.string	"You"
	.data
	.align 4
	.type	MODIFIER, @object
	.size	MODIFIER, 4
MODIFIER:
	.long	.LC2
	.text
	.globl	ssuos_main
	.type	ssuos_main, @function
ssuos_main:
.LFB3:
	.file 1 "arch/Main.c"
	.loc 1 29 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 30 0
	call	main_init
	.loc 1 32 0
	subl	$12, %esp
	pushl	$0
	call	idle
	addl	$16, %esp
	.loc 1 34 0
	nop
	.loc 1 35 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	ssuos_main, .-ssuos_main
	.section	.rodata
.LC3:
	.string	"Memory Detecting\n"
.LC4:
	.string	"%s"
.LC5:
	.string	"PIT Initialization\n"
.LC6:
	.string	"System call Initialization\n"
.LC7:
	.string	"Interrupt Initialization\n"
.LC8:
	.string	"%sPalloc Initialization\n"
.LC9:
	.string	"Paging Initialization\n"
.LC10:
	.string	"Process Initialization\n"
	.align 4
.LC11:
	.string	"========== initialization complete ==========\n\n"
	.text
	.globl	main_init
	.type	main_init, @function
main_init:
.LFB4:
	.loc 1 38 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 39 0
	call	intr_disable
	.loc 1 41 0
	call	init_console
	.loc 1 43 0
	call	print_contributors
	.loc 1 45 0
	call	detect_mem
	.loc 1 46 0
	subl	$8, %esp
	pushl	$.LC3
	pushl	$.LC4
	call	printk
	addl	$16, %esp
	.loc 1 48 0
	call	init_pit
	.loc 1 49 0
	subl	$8, %esp
	pushl	$.LC5
	pushl	$.LC4
	call	printk
	addl	$16, %esp
	.loc 1 51 0
	call	init_syscall
	.loc 1 52 0
	subl	$8, %esp
	pushl	$.LC6
	pushl	$.LC4
	call	printk
	addl	$16, %esp
	.loc 1 54 0
	call	init_intr
	.loc 1 55 0
	subl	$8, %esp
	pushl	$.LC7
	pushl	$.LC4
	call	printk
	addl	$16, %esp
	.loc 1 57 0
	call	init_kbd
	.loc 1 59 0
	call	init_palloc
	.loc 1 60 0
	subl	$12, %esp
	pushl	$.LC8
	call	printk
	addl	$16, %esp
	.loc 1 62 0
	call	init_paging
	.loc 1 63 0
	subl	$8, %esp
	pushl	$.LC9
	pushl	$.LC4
	call	printk
	addl	$16, %esp
	.loc 1 65 0
	call	init_proc
	.loc 1 66 0
	subl	$8, %esp
	pushl	$.LC10
	pushl	$.LC4
	call	printk
	addl	$16, %esp
	.loc 1 68 0
	call	intr_enable
	.loc 1 70 0
	subl	$12, %esp
	pushl	$.LC11
	call	printk
	addl	$16, %esp
	.loc 1 76 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	main_init, .-main_init
	.section	.rodata
.LC12:
	.string	"SSUOS main start!!!!\n"
	.align 4
.LC13:
	.string	"          ______    ______   __    __         ______    ______  \n"
	.align 4
.LC14:
	.string	"         /      \\  /      \\ /  |  /  |       /      \\  /      \\ \n"
	.align 4
.LC15:
	.string	"        /$$$$$$  |/$$$$$$  |$$ |  $$ |      /$$$$$$  |/$$$$$$  |\n"
	.align 4
.LC16:
	.string	"        $$ \\__$$/ $$ \\__$$/ $$ |  $$ |      $$ |  $$ |$$ \\__$$/ \n"
	.align 4
.LC17:
	.string	"        $$      \\ $$      \\ $$ |  $$ |      $$ |  $$ |$$      \\ \n"
	.align 4
.LC18:
	.string	"         $$$$$$  | $$$$$$  |$$ |  $$ |      $$ |  $$ | $$$$$$  |\n"
	.align 4
.LC19:
	.string	"        /  \\__$$ |/  \\__$$ |$$ \\__$$ |      $$ \\__$$ |/  \\__$$ |\n"
	.align 4
.LC20:
	.string	"        $$    $$/ $$    $$/ $$    $$/       $$    $$/ $$    $$/ \n"
	.align 4
.LC21:
	.string	"         $$$$$$/   $$$$$$/   $$$$$$/         $$$$$$/   $$$$$$/  \n"
.LC22:
	.string	"\n"
	.align 4
.LC23:
	.string	"****************Made by OSLAB in SoongSil University*********************\n"
	.align 4
.LC24:
	.string	"contributors : Yunkyu Lee  , Minwoo Jang  , Sanghun Choi , Eunseok Choi\n"
	.align 4
.LC25:
	.string	"               Hyunho Ji   , Giwook Kang  , Kisu Kim     , Seonguk Lee \n"
	.align 4
.LC26:
	.string	"               Gibeom Byeon, Jeonghwan Lee, Kyoungmin Kim, Myungjoon Shon\n"
	.align 4
.LC27:
	.string	"               Jinwoo Lee, Hansol Lee, Mhanwoo Heo\n"
	.align 4
.LC28:
	.string	"************************  Professor. Jiman Hong  ************************\n"
	.align 4
.LC29:
	.string	"                                                                  \n"
	.text
	.globl	print_contributors
	.type	print_contributors, @function
print_contributors:
.LFB5:
	.loc 1 79 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 80 0
	subl	$8, %esp
	pushl	$.LC12
	pushl	$.LC4
	call	printk
	addl	$16, %esp
	.loc 1 81 0
	subl	$12, %esp
	pushl	$.LC13
	call	printk
	addl	$16, %esp
	.loc 1 82 0
	subl	$12, %esp
	pushl	$.LC14
	call	printk
	addl	$16, %esp
	.loc 1 83 0
	subl	$12, %esp
	pushl	$.LC15
	call	printk
	addl	$16, %esp
	.loc 1 84 0
	subl	$12, %esp
	pushl	$.LC16
	call	printk
	addl	$16, %esp
	.loc 1 85 0
	subl	$12, %esp
	pushl	$.LC17
	call	printk
	addl	$16, %esp
	.loc 1 86 0
	subl	$12, %esp
	pushl	$.LC18
	call	printk
	addl	$16, %esp
	.loc 1 87 0
	subl	$12, %esp
	pushl	$.LC19
	call	printk
	addl	$16, %esp
	.loc 1 88 0
	subl	$12, %esp
	pushl	$.LC20
	call	printk
	addl	$16, %esp
	.loc 1 89 0
	subl	$12, %esp
	pushl	$.LC21
	call	printk
	addl	$16, %esp
	.loc 1 90 0
	subl	$12, %esp
	pushl	$.LC22
	call	printk
	addl	$16, %esp
	.loc 1 91 0
	subl	$12, %esp
	pushl	$.LC23
	call	printk
	addl	$16, %esp
	.loc 1 92 0
	subl	$12, %esp
	pushl	$.LC22
	call	printk
	addl	$16, %esp
	.loc 1 93 0
	subl	$12, %esp
	pushl	$.LC24
	call	printk
	addl	$16, %esp
	.loc 1 94 0
	subl	$12, %esp
	pushl	$.LC25
	call	printk
	addl	$16, %esp
	.loc 1 95 0
	subl	$12, %esp
	pushl	$.LC26
	call	printk
	addl	$16, %esp
	.loc 1 96 0
	subl	$12, %esp
	pushl	$.LC27
	call	printk
	addl	$16, %esp
	.loc 1 97 0
	subl	$12, %esp
	pushl	$.LC22
	call	printk
	addl	$16, %esp
	.loc 1 98 0
	subl	$12, %esp
	pushl	$.LC28
	call	printk
	addl	$16, %esp
	.loc 1 99 0
	subl	$12, %esp
	pushl	$.LC29
	call	printk
	addl	$16, %esp
	.loc 1 100 0
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	print_contributors, .-print_contributors
.Letext0:
	.file 2 "./include/device/console.h"
	.file 3 "./include/syscall.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x129
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF22
	.byte	0xc
	.long	.LASF23
	.long	.LASF24
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF1
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF7
	.uleb128 0x4
	.long	.LASF25
	.byte	0x4
	.long	0x33
	.byte	0x3
	.byte	0x4
	.long	0x99
	.uleb128 0x5
	.long	.LASF8
	.byte	0
	.uleb128 0x5
	.long	.LASF9
	.byte	0x1
	.uleb128 0x5
	.long	.LASF10
	.byte	0x2
	.uleb128 0x5
	.long	.LASF11
	.byte	0x3
	.uleb128 0x5
	.long	.LASF12
	.byte	0x4
	.uleb128 0x5
	.long	.LASF13
	.byte	0x5
	.byte	0
	.uleb128 0x6
	.long	.LASF14
	.byte	0x1
	.byte	0x1c
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x6
	.long	.LASF15
	.byte	0x1
	.byte	0x25
	.long	.LFB4
	.long	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x6
	.long	.LASF16
	.byte	0x1
	.byte	0x4e
	.long	.LFB5
	.long	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x7
	.long	.LASF17
	.byte	0x2
	.byte	0xc
	.long	0x4f
	.uleb128 0x5
	.byte	0x3
	.long	Glob_x
	.uleb128 0x7
	.long	.LASF18
	.byte	0x2
	.byte	0xd
	.long	0x4f
	.uleb128 0x5
	.byte	0x3
	.long	Glob_y
	.uleb128 0x7
	.long	.LASF19
	.byte	0x1
	.byte	0x18
	.long	0xff
	.uleb128 0x5
	.byte	0x3
	.long	VERSION
	.uleb128 0x8
	.byte	0x4
	.long	0x105
	.uleb128 0x9
	.long	0x2c
	.uleb128 0x7
	.long	.LASF20
	.byte	0x1
	.byte	0x19
	.long	0xff
	.uleb128 0x5
	.byte	0x3
	.long	AUTHOR
	.uleb128 0x7
	.long	.LASF21
	.byte	0x1
	.byte	0x1a
	.long	0xff
	.uleb128 0x5
	.byte	0x3
	.long	MODIFIER
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF3:
	.string	"long long int"
.LASF2:
	.string	"unsigned int"
.LASF0:
	.string	"unsigned char"
.LASF14:
	.string	"ssuos_main"
.LASF7:
	.string	"long long unsigned int"
.LASF18:
	.string	"Glob_y"
.LASF23:
	.string	"arch/Main.c"
.LASF12:
	.string	"SYS_SHUTDOWN"
.LASF11:
	.string	"SYS_SSUREAD"
.LASF19:
	.string	"VERSION"
.LASF1:
	.string	"char"
.LASF20:
	.string	"AUTHOR"
.LASF15:
	.string	"main_init"
.LASF25:
	.string	"SYS_LIST"
.LASF8:
	.string	"SYS_FORK"
.LASF22:
	.string	"GNU C11 5.4.0 20160609 -m32 -mtune=generic -march=i686 -g -O0 -ffreestanding -fno-stack-protector"
.LASF9:
	.string	"SYS_EXIT"
.LASF6:
	.string	"short unsigned int"
.LASF4:
	.string	"signed char"
.LASF16:
	.string	"print_contributors"
.LASF10:
	.string	"SYS_WAIT"
.LASF5:
	.string	"short int"
.LASF21:
	.string	"MODIFIER"
.LASF13:
	.string	"SYS_NUM"
.LASF17:
	.string	"Glob_x"
.LASF24:
	.string	"/home/cyr/\353\260\224\355\203\225\355\231\224\353\251\264/SSUOS_P4/src/kernel"
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
