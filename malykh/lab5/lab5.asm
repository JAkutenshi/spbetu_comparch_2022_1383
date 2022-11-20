AStack  SEGMENT STACK
    DB 1024 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0 
    KEEP_IP DW 0 
    message DB 'Hello, World!', 13, 10, '$'
    delay_time DB 1
    delay_count DB 0
DATA    ENDS

CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack
    

WriteMsg  PROC  NEAR
          mov ah, 9
          int 21h 
          ret
WriteMsg  ENDP

Delay Proc NEAR
	; Секундная задержка
	push cx
	push dx
	mov cx, 0fh
	mov dx, 4240h
	mov ah, 86h
	int 15h
	pop dx
	pop cx
	ret
Delay ENDP

INT_HANDLER  PROC FAR
        mov ax, seg DATA
        mov ds, ax
	mov dx, offset message

        mov cx, 4
	printing_msg:
		call WriteMsg
                cmp cx, 1
                je end_loop
                delay_cycle:
			call Delay
        		inc delay_count
                        mov al, delay_count
                        cmp al, delay_time
        		jl delay_cycle
        	shl delay_time, 1
                and delay_count, 0
		loop printing_msg
        
        end_loop:
	mov al, 20H
	out 20H, al
	iret
INT_HANDLER ENDP

Main PROC FAR
   mov  ah, 35h   ; функция получения вектора
   mov  al, 60h   ; номер вектора
   int  21h
   mov KEEP_IP, bx  ; запоминание смещения
   mov KEEP_CS, es  ; и сегмента
      
   push ds
   mov dx, offset INT_HANDLER ; смещение для процедуры в DX
   mov ax, seg INT_HANDLER    ; сегмент процедуры
   mov ds, ax         ; помещаем в DS
    
   mov ah, 25h ;функция установки вектора
   mov al, 60h ;номер вектора
   int 21h ;меняем прерывание
   pop ds 
   int 60h
 
   cli
   push ds
   mov dx, KEEP_IP
   mov ax, KEEP_CS
   mov ds, ax
   mov ah, 25h
   mov al, 60h
   int 21h          ; восстанавливаем вектор
   pop ds
   sti
   mov ah, 4ch
   int 21h 
   ret
 	   
Main ENDP
CODE ENDS
END Main
