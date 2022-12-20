AStack SEGMENT STACK
    dw 16 DUP(?)
AStack ENDS

DATA SEGMENT
    a dw 6
    b dw 4
    i dw 3
    k dw 3
    func1 dw 0
    func2 dw 0
    func3 dw 0
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:AStack

Main PROC FAR
    push ds
    sub ax, ax
    push ax
    mov ax, DATA
    mov ds, ax
;--------------------------
    mov ax, a
    mov cx, i
    cmp ax, b
    jg vet1 ; a > b
    shl cx, 1
    add cx, i
    add cx, 6
    mov func1, cx
    sub cx, 9
    mov dx, 9
    sub dx, cx
    mov func2, dx
    jmp cont1
vet1:
    shl cx, 1
    add cx, i
    shl cx, 1
    sub cx, 4
    neg cx
    mov func1, cx
    sub cx, 12
    mov func2, cx
cont1:
    mov ax, func1
    mov bx, func2
    mov cx, k
    cmp cx, 0
    je vet2
    cmp ax, bx
    jl lower
    mov ax, bx
    jmp finish
lower:
    jmp finish
vet2:
    add ax, bx
    cmp ax, 0
    jle negative
    jmp finish
negative:
    neg ax
finish:
    mov func3, ax
    mov ax, func1
    mov bx, func2
    mov cx, func3
    ret
Main ENDP
CODE ENDS
END Main