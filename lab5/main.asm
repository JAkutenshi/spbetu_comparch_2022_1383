DATA SEGMENT
    KEEP_CS dw 0
    KEEP_IP dw 0
DATA ENDS

AStack SEGMENT STACK
    db 1024 DUP (?)
AStack ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

SUBR_INT PROC FAR 
    push ax 
    push cx
    push bx
    push dx
    
    ; getting time 
    mov ah, 02h
    int 1Ah

    sub bx, bx

    ; printing time 
    mov bx, cx
    shr bx, 1
    shr bx, 1
    shr bx, 1
    shr bx, 1
    and bx, 0F0Fh
    and cx, 0F0Fh
    add bx, 3030h
    add cx, 3030h

    mov dl, bh
    int 21h
    mov dl, ch
    int 21h
    mov dl, ':'
    int 21h
    mov dl, bl
    int 21h
    mov dl, cl 
    int 21h

    pop dx
    pop bx 
    pop cx
    pop ax
    mov al, 20h
    out 20h, al
    iret
SUBR_INT ENDP

Main PROC FAR
    ; initializing 
    push ds 
    sub ax, ax 
    push ax 
    mov ax, DATA
    mov ds, ax 
    
    ; saving previous interrupt 
    mov ah, 35h
    mov al, 60h
    int 21h
    mov KEEP_IP, bx
    mov KEEP_CS, es 

    ; setting new interrupt address
    push ds 
    mov dx, offset SUBR_INT
    mov ax, seg SUBR_INT
    mov ds, ax 
    mov ah, 25h
    mov al, 60h 
    int 21h
    pop ds

    ; calling new interrupt
    int 60h

    ; restore previous interrupt
    cli
    push ds 
    mov dx, KEEP_IP
    mov ax, KEEP_CS 
    mov ds, ax
    mov ah, 25h 
    mov al, 60h
    int 21h
    pop ds
    sti 
    ret 
Main ENDP
CODE ENDS
    END Main