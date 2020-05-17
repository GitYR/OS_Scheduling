org	0x7c00   

KER_SIZ		equ		0x80

[BITS 16]

START:   
		jmp		BOOT1_LOAD ;BOOT1_LOAD로 점프

BOOT1_LOAD:
		mov     ax, 0x0900 
        mov     es, ax
        mov     bx, 0x0

		;0x13 인터럽트는 DISK I/O, 64비트책 p136 참조
        mov     ah, 2		;0x13 인터럽트 호출시 ah에 저장된 값에 따라 수행되는 결과가 다름. 2는 섹터 읽기
        mov     al, 0x4		;al 읽을 섹터 수를 지정 1~128 사이의 값을 지정 가능
        mov     ch, 0		;실린더 번호 cl의 상위 2비트까지 사용가능 하여 표현
        mov     cl, 2		;읽기 시작할 섹터의 번호 1~18 사이의 값, 1에는 부트로더가 있으니 2이상부터
        mov     dh, 0		;읽기 시작할 헤드 번호 1~15 값
        mov     dl, 0x80	;드라이브 번호. 0x00 - 플로피; 0x80 - 첫 번째 하드, 0x81 - 두 번째 하드

        int     0x13		;0x13 인터럽트 호출
        jc      BOOT1_LOAD	;Carry 플래그 발생시(=Error) 다시 시도
         
KERNEL_LOAD:
		mov     ax, 0x1000	; 디스크에 있는 커널 이미지를 0X10000 번지에 올리기 위해 ax에 0x1000 저장(segment 레지스터는 주소 연산시 16비트 더해짐)
        mov     es, ax		; 세그먼트 레지스터에는 직접 주소 값을 대입 못 하고 범용 레지스터를 통해서만 입력 가능(인텔 설계, cpu 회로와 관련)
        mov     bx, 0x0		; bx 초기화

        mov     ah, 2		;READ
        mov     al, KER_SIZ	;SECTOR COUNT
        mov     ch, 0		;CYLINDER NUMBER
        mov     cl, 0x6		;SECTOR SEEK
        mov     dh, 0       ;HEAD
        mov     dl, 0x80    ;HARD DRIVE

        int     0x13
        jc      KERNEL_LOAD

jmp		0x0900:0x0000

times 	510-($-$$) db 0x00
dw	0xaa55
