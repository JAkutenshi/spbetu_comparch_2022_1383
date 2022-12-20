AStack SEGMENT STACK
    DW 12 DUP(?)
AStack ENDS

DATA SEGMENT
    a DW 0
    b DW 0
    i DW 0
    k DW 0
    res DW 0
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

Main PROC FAR
    push ds ; initialization
    sub ax, ax 
    push ax
    mov ax, DATA
    mov ds, ax

    mov cx, i   ;cx = i
    shl cx, 1   ;cx = 2i
    mov ax, a 
    cmp ax, b 
    jle lessb ;if a <= b

    shl cx, 1   ;cx = 4i
    mov dx, cx  ;dx = 4i
    sub dx, 5   ;dx = 4i - 5
    add cx, 3   ;cx = 4i + 3
    neg cx      ;cx = -(4i + 3)
    jmp step1   

lessb:
    add cx, i   ;cx = 3i
    mov dx, cx  ;dx = cx
    shl cx, 1   ;cx = 6i
    sub cx, 10  ;cx = 6i - 10
    sub dx, 10  ;dx = 3i - 10

step1: ;cx = f1, dx = -f2
    mov ax, k
    cmp ax, 0
    jl less0 ;if k < 0
    mov ax, -6
    cmp dx, ax
    jg first ;if dx > ax
    jmp second

less0:
    add dx, cx
    cmp dx, 0
    jge module ;if dx >= 0
    neg dx

module:
    mov ax, 2
    cmp dx, ax 
    jg second ;if dx > ax

first:
    mov res, dx
    ret

second:
    mov res, ax
    ret
Main ENDP
CODE ENDS
    END Main