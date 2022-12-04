
EOFLine  EQU  '$'        

AStack    SEGMENT  STACK
          DW 2048 DUP('!')    
AStack    ENDS


DATA SEGMENT
    test  DB 'laba done $'
    KEEP_CS DW 0 ; для хранения сегмента
    KEEP_IP DW 0 ; и смещения вектора прерывания
DATA      ENDS


CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

    MY_INT PROC far
            push ax
            push dx
            ;
            mov dx,offset test
            mov   AH,9
            int   21h   
            ;
            pop dx
            pop ax

            mov al,20h
            out 20h,al
            iret
    MY_INT ENDP
        
        
    Main PROC FAR
        push ds
	    sub ax, ax
	    push ax
        mov ax, DATA
        mov ds, ax

        MOV AH, 35H ; функция получения вектора
        MOV AL, 1CH ; номер вектора
        INT 21H
        MOV KEEP_IP, BX ; запоминание смещения
        MOV KEEP_CS, ES ; и сегмента вектора прерывания

        PUSH DS
        MOV DX, OFFSET MY_INT ; смещение для процедуры в DX
        MOV AX, SEG MY_INT ; сегмент процедуры
        MOV DS, AX ; помещаем в DS
        MOV AH, 25H ; функция установки вектора
        MOV AL, 1cH ; номер вектора
        INT 21H ; меняем прерывание
        POP DS
        
	    mov cx, 0020h 
	    mov ah, 86h
	    int 15h
        CLI
        PUSH DS
        MOV DX, KEEP_IP
        MOV AX, KEEP_CS
        MOV DS, AX
        MOV AH, 25H
        MOV AL, 1CH
        INT 21H ; восстанавливаем старый вектор прерывания
        POP DS
        STI
        MOV AH, 4CH
    	INT 21H
    Main ENDP

CODE ENDS
    END Main
