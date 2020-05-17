        .text

/* Main interrupt entry point.

   An internal or external interrupt starts in one of the
   intrNN_stub routines, which push the 'struct intr_frame'
   frame_pointer, error_code, and vec_no members on the stack,
   then jump here.

   We save the rest of the 'struct intr_frame' members to the
   stack, set up some registers as needed by the kernel, and then
   call intr_handler(), which actually handles the interrupt.

   We "fall through" to intr_exit to return from the interrupt.
*/
.func intr_entry
intr_entry:
	/* Save caller`s registers. */
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushal
        
	/* Set up kernel environment. */
	cld			/* String instructions go upward. */
	//mov $CODE_SEGMENT, %eax	/* Initialize segment registers. */
	//mov %eax, %ds
	//mov %eax, %es
	leal 56(%esp), %ebp	/* Set up frame pointer. */

	/* Call interrupt handler. */
	pushl %esp
.globl intr_common
	call intr_common
	addl $4, %esp
.endfunc

/* Interrupt exit.

   Restores the caller`s registers, discards extra data on the
   stack, and returns to the caller.

   This is a separate function because it is called directly when
   we launch a new user process (see start_process() in
   userprog/process.c). */
.globl intr_exit
.func intr_exit
intr_exit:
        /* Restore caller`s registers. */
	popal
	popl %gs
	popl %fs
	popl %es
	popl %ds

        /* Discard 'struct intr_frame' vec_no, error_code,
           frame_pointer members. */
	addl $12, %esp

        /* Return to caller. */
	iret
.endfunc

/* Interrupt stubs.

   This defines 256 fragments of code, named 'intr00_stub'
   through 'intrff_stub', each of which is used as the entry
   point for the corresponding interrupt vector.  It also puts
   the address of each of these functions in the correct spot in
   'intr_stubs', an array of function pointers.

   Most of the stubs do this:

        1. Push %ebp on the stack (frame_pointer in 'struct intr_frame').

        2. Push 0 on the stack (error_code).

        3. Push the interrupt number on the stack (vec_no).

   The CPU pushes an extra "error code" on the stack for a few
   interrupts.  Because we want %ebp to be where the error code
   is, we follow a different path:

        1. Push a duplicate copy of the error code on the stack.

        2. Replace the original copy of the error code by %ebp.

        3. Push the interrupt number on the stack. */

	.data
.globl intr_stubs
intr_stubs:

/* This implements steps 1 and 2, described above, in the common
   case where we just push a 0 error code.
*/
#define zero                                \
	pushl %ebp;                             \
	pushl $0

/* This implements steps 1 and 2, described above, in the case
   where the CPU already pushed an error code.
*/
#define REAL                                    \
        pushl (%esp);                           \
        movl %ebp, 4(%esp)

/* Emits a stub for interrupt vector NUMBER.
   TYPE is 'zero', for the case where we push a 0 error code,
   or 'REAL', if the CPU pushes an error code for us.
*/
#define STUB(NUMBER, TYPE)                      \
	.text;                                  \
.func intr##NUMBER##_stub;			\
intr##NUMBER##_stub:                            \
	TYPE;                                   \
	push $0x##NUMBER;                       \
        jmp intr_entry;                         \
.endfunc;					\
                                                \
	.data;                                  \
	.long intr##NUMBER##_stub;

STUB(00, zero) STUB(01, zero) STUB(02, zero) STUB(03, zero)
STUB(04, zero) STUB(05, zero) STUB(06, zero) STUB(07, zero)
STUB(08, REAL) STUB(09, zero) STUB(0a, REAL) STUB(0b, REAL)
STUB(0c, zero) STUB(0d, REAL) STUB(0e, REAL) STUB(0f, zero)

STUB(10, zero) STUB(11, REAL) STUB(12, zero) STUB(13, zero)
STUB(14, zero) STUB(15, zero) STUB(16, zero) STUB(17, zero)
STUB(18, REAL) STUB(19, zero) STUB(1a, REAL) STUB(1b, REAL)
STUB(1c, zero) STUB(1d, REAL) STUB(1e, REAL) STUB(1f, zero)

STUB(20, zero) STUB(21, zero) STUB(22, zero) STUB(23, zero)
STUB(24, zero) STUB(25, zero) STUB(26, zero) STUB(27, zero)
STUB(28, zero) STUB(29, zero) STUB(2a, zero) STUB(2b, zero)
STUB(2c, zero) STUB(2d, zero) STUB(2e, zero) STUB(2f, zero)

STUB(30, zero) STUB(31, zero) STUB(32, zero) STUB(33, zero)
STUB(34, zero) STUB(35, zero) STUB(36, zero) STUB(37, zero)
STUB(38, zero) STUB(39, zero) STUB(3a, zero) STUB(3b, zero)
STUB(3c, zero) STUB(3d, zero) STUB(3e, zero) STUB(3f, zero)

STUB(40, zero) STUB(41, zero) STUB(42, zero) STUB(43, zero)
STUB(44, zero) STUB(45, zero) STUB(46, zero) STUB(47, zero)
STUB(48, zero) STUB(49, zero) STUB(4a, zero) STUB(4b, zero)
STUB(4c, zero) STUB(4d, zero) STUB(4e, zero) STUB(4f, zero)

STUB(50, zero) STUB(51, zero) STUB(52, zero) STUB(53, zero)
STUB(54, zero) STUB(55, zero) STUB(56, zero) STUB(57, zero)
STUB(58, zero) STUB(59, zero) STUB(5a, zero) STUB(5b, zero)
STUB(5c, zero) STUB(5d, zero) STUB(5e, zero) STUB(5f, zero)

STUB(60, zero) STUB(61, zero) STUB(62, zero) STUB(63, zero)
STUB(64, zero) STUB(65, zero) STUB(66, zero) STUB(67, zero)
STUB(68, zero) STUB(69, zero) STUB(6a, zero) STUB(6b, zero)
STUB(6c, zero) STUB(6d, zero) STUB(6e, zero) STUB(6f, zero)

STUB(70, zero) STUB(71, zero) STUB(72, zero) STUB(73, zero)
STUB(74, zero) STUB(75, zero) STUB(76, zero) STUB(77, zero)
STUB(78, zero) STUB(79, zero) STUB(7a, zero) STUB(7b, zero)
STUB(7c, zero) STUB(7d, zero) STUB(7e, zero) STUB(7f, zero)

