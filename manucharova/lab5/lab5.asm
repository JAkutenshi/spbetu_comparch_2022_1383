AStack SEGMENT STACK
    db 1024 DUP(?)
AStack ENDS

DATA SEGMENT
    KEEP_CS dw 0
    KEEP_IP dw 0
    crlf db 0dh, 0ah, '$'
    mes db 'Processing completed$'
    buf db 20
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

SUBR_INT PROC FAR
    PUSH AX 
    push DX
    push bx
    push cx

    mov dx, offset buf
    mov ah, 0ah
    int 21h
    mov dx, offset crlf
    mov ah, 09h
    int 21h
    
    mov dx, offset buf
    xor ah, ah
    lea bx, buf+2
    xor cx, cx
    mov cl, buf+1
    add bx,cx
    mov byte ptr [bx], '$'
    add dx, 2
    mov ah, 9h
    int 21h

    mov dx, offset crlf
    mov ah, 09h
    int 21h
    
    mov ah, 9h
    mov dx, offset mes
    int 21h
    pop cx
    pop bx
    pop dx
    POP AX 
    MOV AL, 20H
    OUT 20H,AL
    IRET
SUBR_INT ENDP


Main PROC FAR
    push ds 
    xor ax, ax 
    push ax
    mov ax, DATA
    mov ds, ax

    mov ah, 35h
    mov al, 60h
    int 21h
    mov KEEP_IP, bx
    mov KEEP_CS, es 

    PUSH DS
    MOV DX, OFFSET SUBR_INT 
    MOV AX, SEG SUBR_INT
    MOV DS, AX 
    MOV AH, 25H 
    MOV AL, 60H 
    INT 21H 
    POP DS
    int 60h
;Срабатывает прерывание

    CLI
    PUSH DS
    MOV DX, KEEP_IP
    MOV AX, KEEP_CS
    MOV DS, AX
    MOV AH, 25H
    MOV AL, 60H
    INT 21H 
    POP DS
    STI
    ret

Main ENDP
CODE ENDS
    END Main