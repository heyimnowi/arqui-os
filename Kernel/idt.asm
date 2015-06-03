GLOBAL _irq00handler
GLOBAL _irq01handler
GLOBAL _sti
GLOBAL _cli
GLOBAL _in_io
GLOBAL _out_io
GLOBAL picMasterMask
GLOBAL picSlaveMask

EXTERN keyboardHandler
EXTERN timertickHandler
EXTERN syscallHandler

%macro pushaq 0
    push rax      ;save current rax
    push rbx      ;save current rbx
    push rcx      ;save current rcx
    push rdx      ;save current rdx
    push rbp      ;save current rbp
    push rdi       ;save current rdi
    push rsi       ;save current rsi
    push r8        ;save current r8
    push r9        ;save current r9
    push r10      ;save current r10
    push r11      ;save current r11
    push r12      ;save current r12
    push r13      ;save current r13
    push r14      ;save current r14
    push r15      ;save current r15
%endmacro

%macro popaq 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro END_INT 0
	mov al, 20h ; Acknowledge interruption was treated
	out 20h, al ; and PIC can recieve the next one

	popaq
	iretq
%endmacro

section .text

; Disable interruptions
_cli:
	cli
	ret

; Enable interruptions
_sti:
	sti
	ret

; I/O operations
; writes rsi value into io position [rdi]
_out_io:
	push rbp
	mov rbp, rsp

	mov rdx, rdi
	mov rax, rsi
	out dx, al	; writes al content into dx (i/o)

	mov rsp, rbp
	pop rbp
	ret

; reads from io position rdi and writes into [rsi]
_in_io:
	push rbp
	mov rbp, rsp

	mov rdx, rdi
	in al, dx		; puts what's in dx (i/o) into al reg
	mov [rsi], al

	mov rsp, rbp
	pop rbp
	ret



picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, si
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, si  ; ax = mascara de 16 bits
    out		0A1h, al
    pop     rbp
    retn

; Timer tick
_irq00handler:
	pushaq

	call timertickHandler

	END_INT

; Keyboard
_irq01handler:
	pushaq
	
	in al, 60h

	mov rdi, rax
	call keyboardHandler

	in al, 61h
	or al, 80h
	out 61h, al
	and al, 7Fh
	out 61h, al

	END_INT

; System call
; recieves the system call code in rax
; and parameters in rdi, rsi, rdx, r10, r8 and r9
; We won't be using more than 3 params
; TODO: es necesario almacenar los registros?
_int80handler:
	push rbp
	mov rbp, rsp

	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, rax
	call syscallHandler
	
	mov rsp, rbp
	pop rbp
	iretq
