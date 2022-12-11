ASSUME CS:CODE, DS:DATA, SS:AStack

DATA SEGMENT

KEEP_CS DW 0 ; для хранения сегмента
KEEP_IP DW 0 ; и смещения прерывания

message db 'hello $'
end_message db 'end!$'

DATA ENDS

AStack SEGMENT STACK
DW 512 DUP('0')
AStack ENDS

CODE SEGMENT

ASSUME CS:CODE, DS:DATA, SS:Astack



sep PROC
	push ax
	push dx

	mov dl, ':'
	mov ah, 02h
	int 21h

	pop ax
	pop dx
	ret
sep ENDP


get_time PROC
	push ax
	push bx
	push dx

	aam   
	mov bx, ax
	mov ah, 02h

	mov dl, bh
	add dl, '0'
	int 21h

	mov dl, bl
	add dl, '0'
	int 21h

	pop ax
	pop bx
	pop dx
	ret
get_time ENDP


print_time PROC
	push ax
	push cx
	push dx

	mov ah, 2ch
	int 21h

	mov al, ch
	call get_time
	call sep
	mov al, cl
	call get_time
	call sep
	mov al, dh
	call get_time

	pop ax
	pop cx
	pop dx

	ret
print_time ENDP





WRITE PROC FAR 

	push ax
	push bx
	push cx
	push dx

	mov dx, offset message

	mov ah, 09h

output:
	int 21h
	loop output

	mov ah, 0
	int 1Ah
	add bx, dx

delay:
	mov ah, 0
	int 1Ah
	cmp bx, dx
	jg delay

	call print_time
	

	pop ax
	pop bx
	pop cx
	pop dx

	mov al, 20h
	out 20h, al
	iret
WRITE ENDP




MAIN PROC FAR
push DS
sub AX, AX
push AX
mov AX, DATA
mov DS, AX

mov AX, 3523h
int 21h
mov KEEP_IP, BX
mov KEEP_CS, ES

push DS
mov bx, 30h
mov cx, 05h
mov DX, OFFSET WRITE
mov AX, SEG WRITE
mov DS, AX
mov AH, 25h
mov AL, 23h
int 21H
pop DS

read:
mov AH, 0
int 16h
cmp AL, 3
je do
jmp read

do:
int 23h


cli
push DS
mov DX, KEEP_IP
mov AX, KEEP_CS
mov DS, AX
mov AX, 2523h
int 21h
pop DS
sti

ret FAR

MAIN ENDP
CODE ENDS
END MAIN
