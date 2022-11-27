AStack  SEGMENT STACK
    DB 512 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0    
    KEEP_IP DW 0
DATA    ENDS

CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

hours proc near
	mov al, ch
	call output
	ret
hours ENDP

minutes proc near
	mov al, cl
	call output
	ret
minutes ENDP

seconds proc near
	mov al, dh
	call output
	ret
seconds ENDP

output proc near
	push dx
	aam 
	add ax,3030h 
	mov dl,ah 
	mov dh,al 
	mov ah,02 
	int 21h 
	mov dl,dh 
	int 21h
	pop dx
	ret
output endp

stun PROC  NEAR
        push ax
	push cx
	push dx
	mov cx,0fh
	mov dx,8480H
	mov ax,8600h
        int 15h 
	pop dx
	pop cx
	pop ax
          ret
stun ENDP

TIME PROC FAR
	mov cx, 5
	mov ax, 2
        first:
        	mov bx, cx 
		push ax
		push cx
		push dx
		push bx
		mov ah, 2ch
		int 21h
		call hours
		mov dl,':'	;вывод ':'
		int 21h
		call minutes
		mov dl,':'	;вывод ':'
		int 21h
		call seconds
		mov dl,' '
    		int 21h
		pop bx
		pop dx
		pop cx
		pop ax
        	mov cx, ax
        	second:
        		call stun
			sub cx,1
			cmp cx,0
			jg second 
     
        	mov cx,bx       
		sub cx,1
		cmp cx,0
		jg first 
	mov al, 20h
	out 20h, al
	iret
TIME ENDP

MAIN PROC FAR
	push ds
	sub ax, ax
	push ax
	mov ax, DATA
	mov ds, ax
	mov ax, 3523h 
	int 21h
	mov KEEP_IP, bx 
	mov KEEP_CS, es    
	push ds
	mov dx, OFFSET TIME 
	mov ax, SEG TIME 
	mov ds, ax 
	mov ah, 25h 
	mov al, 23h 
	int 21h
	pop ds
	read:
    		mov ah, 0
		int 16h
		cmp al, 3
		jnz read
	int 23h

    	cli
    	push ds
    	mov dx, KEEP_IP
    	mov ax, KEEP_CS
    	mov ds, ax
    	mov ah, 25h
    	mov al, 23h
    	int 21h
    	pop ds
    	sti
	mov ah, 4ch
	int 21h    
MAIN ENDP
CODE ENDS
	END MAIN