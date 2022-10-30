;            / 7 - 4*i , при a>b
;  (f1)f3 = <
;            \ 8 -6*i , при a<=b

;            / -(6*i - 4) , при a>b
;  (f2)f4 = <
;            \ 3*(i+2) , при a<=b

;            / max(i1,10-i2), при k<0
;  (f3)f2 = <
;            \ |i1 - i2| , при k>=0

.Model small
a EQU -4
b EQU -7
i EQU 3
k EQU 1

.STACK 
DW 12 DUP(?)

.data
f1 DW 0
f2 DW 0
f3 DW 0

.CODE
    mov cx, i

    mov ax, a
    mov bx, b
    cmp ax, bx
    jle less

    shl cx, 1
    mov dx, cx

    shl cx, 1
    neg cx
    add cx, 7

    add dx, i
    shl dx, 1
    sub dx, 4
    neg dx

    jmp final1
    
less:
    mov dx, cx

    shl cx, 1
    add cx, i
    shl cx, 1
    neg cx
    add cx, 8

    add dx, 2
    mov ax, dx
    shl dx, 1
    add dx, ax

final1:
    mov [f1], cx
    mov [f2], dx

    neg dx
    mov bx, k
    cmp bx, 0
    jge greater

    add dx, 10
    cmp cx, dx
    jg final2
    xchg cx, dx
    jmp final2

greater:
    add cx, dx
    jns final2
    neg cx

final2:
    mov [f3], cx
END