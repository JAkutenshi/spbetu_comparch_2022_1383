a EQU -3
b EQU 2
i EQU 2
k EQU 0
AStack SEGMENT STACK
	DW 12 DUP(?)
AStack ENDS

DATA SEGMENT

	res DW 0
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:AStack

Main PROC FAR
	push ds
	sub ax, ax
	push ax

	mov ax, i
	shl ax, 1
	shl ax, 1
	mov bx, ax

	mov cx, a
	cmp cx, b
	jle fless

	neg ax
	add ax, 7
	push ax ;i1

	mov ax, bx
	neg ax
	add ax, 5
	push ax ;i2
	jmp f3
fless:
	mov ax, bx
	add ax, i
	add ax, i
	neg ax
	add ax, 8
	push ax

	mov ax, bx
	neg ax
	add ax, i
	add ax, 10
	push ax

f3:
	pop cx ;i1
	add cx, 0
	cmp cx, 0
	jns i1abs ; |i1| = |i1|
	neg cx
i1abs:
	mov ax, k
	cmp ax, 0
	jne f3v2
	pop bx
	cmp cx, 6
	jl finish
	mov cx, 6
	jmp finish

f3v2:
	pop dx ;i2
	add dx, 0
	cmp dx, 0
	jns i2abs ;|i2| = |i2|
	neg dx
i2abs:
	add cx, dx

finish:
	mov [res], cx
	push cx
	pop cx
	ret
Main ENDP
CODE ENDS
	END Main

