AStack  SEGMENT STACK
    DB 1024 DUP(?)
AStack  ENDS

DATA    SEGMENT
    KEEP_CS DW 0 
    KEEP_IP DW 0 
    delay_time DB 1
    delay_count DB 0
    time_int db 0, 0, 0   ; Часы, минуты, секунды
    time_str DB 12 DUP(0)  ; Время в строковом виде
DATA    ENDS

CODE    SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack
    

WriteMsg  PROC  NEAR
          mov ah, 9
          int 21h 
          ret
WriteMsg  ENDP

Delay PROC NEAR
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

GetTimeStr PROC NEAR 
	; Запись в time_str строки формата hh:mm:ss
       
        push cx
        push es
        push di
        push dx
        
        ; Настраиваем di на time_str
        mov ax, ds 
        mov es, ax 
        mov di, offset time_str
                
        ; Получаем время
	mov ah, 2Ch
	int 21h

	mov time_int, ch
	mov time_int[1], cl
	mov time_int[2], dh

        mov cl, 0Ah ; Делитель для получения отдельных десятичных цифр числа
        mov bx, 0

        for_time:
                mov ah, 0
                mov al, time_int[bx]
                div cl ; ah - старший разряд числа, al - младший
                
                add ah, '0' ; Перевод чисел в символы
                add al, '0'
                stosw 

                mov al, ':'
                stosb

                inc bx
                cmp bx, 3
                jne for_time
        dec di
        mov ax, 0A0Dh 
        stosw
        mov al, '$'
        stosb
        pop dx
        pop di
        pop es
	pop cx
        ret
GetTimeStr ENDP

INT_HANDLER  PROC FAR
        mov ax, seg DATA
        mov ds, ax

        mov dx, offset time_str
        mov cx, 4
	printing_msg:
		call GetTimeStr               
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
