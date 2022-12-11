AStack SEGMENT STACK
    db 1024 DUP(?)
AStack ENDS

DATA SEGMENT
    KEEP_CS dw 0
    KEEP_IP dw 0
    crlf db 0dh, 0ah, '$'
    
    mes db  'Processing completed$'
    number db 83, 0, 0, 0
    arr db 83 dup (?)
     
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

SUBR_INT PROC FAR
    PUSH AX 
    push DX
    push bx
    push cx

    mov dx, offset number
    mov ah, 0ah
    int 21h
    mov dx, offset number
    xor ah, ah
    lea bx, number
    xor cx, cx
    mov cl, number[1]
    add bx,3
    ; mov byte ptr [bx], '$'
    ;--------------------------
    mov dx, offset number
    xor bx, bx
    mov bh, number[3]
    cmp bh, 0dh
    je pr1
        mov bl, number[2]
        sub bl, 30h
        xor ax, ax
        mov al, bl
        mov cl, 10
        mul cl
        sub bh, 30h
        add al, bh
        mov bl, al
        jmp cont
    pr1:
        mov bl, number[2]
        sub bl, 30h
    cont:
    xor cx, cx
    mov dx, offset arr
    mov si, 0
    ;---------------------------
    loop1:
        mov ah, 01h
        int 21h
        mov arr[si], al
        add cl, 1
        inc si
        cmp cl, bl
        jne loop1
    
    mov arr[si], '$'
    mov si,0
    mov dx, offset crlf
    mov ah, 09h
    int 21h

    show:
        mov ah, 02h
        mov dl, arr[si]
        int 21h
        inc si
        loop show

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