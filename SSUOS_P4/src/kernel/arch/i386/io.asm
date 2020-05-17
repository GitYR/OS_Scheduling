[SECTION .text]
[GLOBAL inb]
inb:
		push	ebp
		mov		ebp, esp

		xor		eax, eax
		mov		dx, word[ebp+8]
		in		al, dx

		pop		ebp
		ret
[GLOBAL	outb]   
outb:  
		push	ebp
		mov		ebp, esp

		mov		al, byte [ebp+12]
		mov		dx, word [ebp+8] 
		out		dx, al

		pop		ebp
		ret

[GLOBAL inl]
inl:
		push	ebp
		mov		ebp, esp
		push	edx

		mov		dx, word [ebp+8]
		xor		eax, eax

		in		eax, dx
		pop		edx
		mov		esp, ebp
		pop		ebp
		ret

[GLOBAL outl]
outl:
		push	ebp
		mov		ebp, esp
		push	edx
		push	eax

		mov		dx, word [ebp+8]
		mov		eax, dword [ebp+12]
		out		dx, eax

		pop		eax
		pop		edx
		mov		esp, ebp
		pop		ebp
		ret

[GLOBAL iowait]
iowait:
		push	ax

		xor		ax, ax
		out		0x80, al

		pop		ax
		ret

