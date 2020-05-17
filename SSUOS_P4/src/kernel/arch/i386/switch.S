//ARG address from ebp - 함수 호출 시 인자의 주소 오프셋
.set ARG_CUR, 8
.set ARG_NEXT, 12

.global switch_process

.func switch_process
switch_process:

	//save register
	pushl %ebp
	movl %esp, %ebp

	pushl %eax
	pushl %ebx
	pushl %ecx
	pushl %edx
	pushl %esi
	pushl %edi

	//offset of stack in struct process - process 구조체 시작주소에서 stack 필드 주소까지의 오프셋
.global process_stack_ofs
	mov process_stack_ofs, %edx
	mov process_stack_ofs, %ebx
	addl $4, %ebx

	//save stack
	movl ARG_CUR(%ebp), %eax
	movl %esp, (%eax, %edx, 1)
	
	//load stack
	movl ARG_NEXT(%ebp), %eax
	
	movl (%eax, %edx, 1), %esp
	movl (%eax, %ebx, 1), %ecx
	movl %ecx, %cr3

	//load register - 스택이 바뀌었으므로, 로드하는 레지스터는 바뀐 프로세스의 레지스터 값
	popl %edi		
	popl %esi
	popl %edx
	popl %ecx
	popl %ebx
	popl %eax

	popl %ebp

	ret

