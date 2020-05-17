[SECTION .text]

[GLOBAL read_cr0]
read_cr0:
		push ebp
		mov ebp, esp
		mov eax, cr0
        pop ebp
		retn

[GLOBAL write_cr0]
write_cr0:
		push ebp
		mov ebp, esp
		mov eax, dword[ebp+8]
		mov cr0, eax
        pop ebp
        retn

[GLOBAL read_cr3]
read_cr3:
		push ebp
		mov ebp, esp
		mov eax, cr3
        pop ebp
		retn

[GLOBAL write_cr3]
write_cr3:
		push ebp
		mov ebp, esp
		mov eax, dword[ebp+8]
        mov cr3, eax
        pop ebp
        retn
