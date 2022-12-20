AStack SEGMENT STACK
    db 1024 DUP(?)
AStack ENDS

DATA SEGMENT
    inter_msg DB ?,?,':',?,?,':',?,?,0DH,'$'
    KEEP_CS dw 0
    KEEP_IP dw 0
    crlf db 0dh, 0ah, '$'
    mes1 db 'Hello World!',0dh, 0ah,'$'
    mes2 db 'Completion of processing$'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack


Time_to_string PROC NEAR
    mov bl, 10h
    mov ah, 0
    div bl
    add al, '0'
    add ah, '0'
    ret
Time_to_string ENDP

SUBR_INT PROC FAR
    PUSH AX
    push DX
    push bx
    push cx

    mov dx, offset mes1
    mov cx, 3
    print_msg1:
        mov ah, 9h
        int 21h
        loop print_msg1

    MOV     CX, 0FH
    MOV     DX, 4240H
    MOV     AH, 86H
    INT     15H
;время

    mov ah, 02h
    int 1ah

    mov al, ch
    call Time_to_string
    mov inter_msg, al
    mov inter_msg + 1, ah

    mov al, cl
    call Time_to_string
    mov inter_msg + 3, al
    mov inter_msg + 4, ah

    mov al, dh
    call Time_to_string
    mov inter_msg + 6, al
    mov inter_msg + 7, ah

    mov dx, offset inter_msg
    mov ah, 9h
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
    MOV AL, 60h
    INT 21H
    POP DS


    loop1:
        mov ah, 00h
        int 16h
        cmp ah, 01h
        jne loop1
        mov ah, 25h
        int 60h


    CLI
    PUSH DS
    MOV DX, KEEP_IP
    MOV AX, KEEP_CS
    MOV DS, AX
    MOV AH, 25H
    MOV AL, 60h
    INT 21H
    POP DS
    STI
    ret

Main ENDP
CODE ENDS
    END Main