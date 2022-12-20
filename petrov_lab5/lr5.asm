; Стек  программы 
AStack    SEGMENT  STACK 
          DW 1024 DUP(?)
AStack    ENDS

; Данные программы 
    DATA      SEGMENT
    message db 'The command is entered incorrectly, enter a number from 1 to 9$'
    KEEP_CS dw 0    
    KEEP_IP dw 0
    duration_0 db 250; изначальная длительность звучания звукового сигнала
    duration dw 0;
    DATA      ENDS 
 
; Код программы 
CODE      SEGMENT 
          ASSUME CS:CODE, DS:DATA, SS:AStack 

Interruption PROC FAR; Прерывание
    push ax                           
    push dx
    mov  dx, ax
    in   al, 61h                      
    push ax                           
    or   al, 00000011b                
    out  61h, al                     
    mov  al,  dl                      
    out  42h, al                      
    mov  cx, duration                    

; Задержка
Audio_Stop:                      
    push cx
    mov  cx, duration
    Audio_Stop_temp:
        nop                           
        loop Audio_Stop_temp         
    pop  cx
    loop Audio_Stop

    pop  ax
    and  al, 11111100b
    out  61h, al                      
    
    pop  dx                           
    pop  ax
    mov  al, 20h
   
    out  20h, al

    iret                              
Interruption ENDP
WriteMsg  PROC  NEAR
          mov   AH,9
          int   21h  
          ret
WriteMsg  ENDP

; Головная процедура 
Main      PROC  FAR 
    push ds
    xor  ax, ax
    push ax
    mov  ax, DATA
    mov  ds, ax
    mov  ah, 35h                    
    mov  al, 23h 
    int  21h                         
    mov  KEEP_CS, es              
    mov  KEEP_IP, bx 
    
    push ds                         
    mov  dx, offset Interruption 
    mov  ax, seg Interruption    
    mov  ds, ax                     
    mov  ah, 25h                    
    mov  al, 23h                    
    int  21h                        
    pop  ds
    
INPUT_CTRL:                    
    in   al, 60h                   
    cmp  al, 1dh                    ; 1d - клавиша ctrl
    jne  INPUT_CTRL            
INPUT_C:
    in   al, 60h
    cmp  al, 9dh                    ; отпускание клавиши ctrl
    je   INPUT_CTRL            
    cmp  al, 2eh                    ; 2e - клавиша c
    jne  INPUT_C
    
    sub ax, ax
    int 16h

INPUT_TIME:
    sub ax, ax
    int 16h
    cmp al, '1'
    jl ERROR
    cmp al, '9'
    jg ERROR
    sub al, 48
    mul duration_0
    mov duration, ax
    jmp OTHER

    

ERROR:
    mov dx, offset message; Вывод ошибки 
    call WriteMsg;          на экран
    jmp INPUT_TIME


    

OTHER:
    mov al, 66
    int  23h                      

    cli                             

    push ds
    mov  dx, KEEP_IP
    mov  ax, KEEP_CS
    mov  ds, ax
    mov  ah, 25h
    mov  al, 23h
    int  21h                        
    pop  ds

    sti                             

    ret

Main      ENDP 
CODE      ENDS 
          END Main
