AStack SEGMENT STACK
	DW 12 DUP(?)
AStack ENDS

DATA SEGMENT
	a DW 3
	b DW 0
	i DW 4
	k DW -5
	i1 DW 0
	i2 DW 0
	res DW 0
DATA ENDS

CODE SEGMENT
	ASSUME cs:CODE, ds:DATA, ss:AStack

Main PROC FAR
	push ds
	AND ax, 0
	push ax
    mov ax, DATA
    mov ds, ax

	; Calculate i1
	mov ax, a
	cmp ax, b

	jle @F
		; if a > b: i1 = -(4i + 3)
		mov ax, i
		sal ax, 1
		sal ax, 1
		add ax, 3 
		neg ax
		mov i1, ax
		jmp I2_a_GREATER_b
	@@:
		; if a <= b: i1 = 6i - 10
		mov ax, i
		sal ax, 1
		mov i1, ax ; i1 = 2i
		sal ax, 1 
		sub ax, 10
		add i1, ax 
	
	; Calculating i2
	; if a <= b: i2 = 9 - 3(i - 1) = -3i + 12
	mov ax, i 
	mov i2, ax
	sal ax, 1 
	add ax, i2
	neg ax
	add ax, 12
	mov i2, ax
	jmp RES_CALC

	I2_a_GREATER_b:
		; if a > b: i2 = - (6i + 8)   
		mov ax, i
		sal ax, 1
		mov i2, ax
		sal ax, 1
		add ax, i2
		add ax, 8
		neg ax
		mov i2, ax

	; Calculating res
	RES_CALC:
		cmp k, 0
		je ABS_CALC
			; if k != 0:  res = min(i1, i2)
			cmp i1, ax ; Compare i1 and i2
			jg @f 
				; if i1 < i2
				mov ax, i1
			@@:
				mov res, ax
				jmp PROG_END
		ABS_CALC:
			; if k == 0: res = |i1 + i2|
			mov res, ax ; res = i2
			mov ax, i1 
			add res, ax 
			cmp res, 0
			jge PROG_END
				; if res is negative
				neg res 
	PROG_END:
		ret		
Main ENDP
CODE ENDS
END Main
