a EQU -3
b EQU -8
k EQU 0
i EQU 45

;i1
; / -(6*i - 4) , при a>b
; f4 = <
; \ 3*(i+2) , при a<=b

;i2
; / 20 - 4*i , при a>b
; f5 = <
; \ -(6*I - 6), при a<=b

;res
; /|i1| + |i2|, при k<0
; f7 = <
; \ max(6, |i1|), при k>=0

AStack SEGMENT STACK
DW 12 DUP(?)
AStack ENDS

DATA SEGMENT
    i1 dw 0
    i2 dw 0
    res dw 0
DATA ENDS

CODE SEGMENT
ASSUME CS : CODE, DS : DATA, SS : AStack
; Головная процедура
Main PROC FAR
push DS
sub AX, AX
push AX
mov AX, DATA
mov DS, AX

mov AX, a
mov BX, b
CMP AX,BX
JG a_bigger_b
JLE b_bigger_a

a_bigger_b:
    mov ax,i
    mov cx, -6
    mul cx
    add ax, 4
    mov i1,ax

    mov ax,i
    mov cx, -4
    mul cx
    add ax, 20
    mov i2,ax
    jmp con2

b_bigger_a:
    mov ax,i
    mov cx, 3
    mul cx
    add ax, 6
    mov i1,ax

    mov ax,i
    mov cx, -6
    mul cx
    add ax, 6
    mov i2,ax

con2:
mov AX, k
mov BX, 0
CMP AX,BX
JGE k_big
JL k_small

k_small:
    mov ax, i1
    test ax, ax
    jns cont1
    neg ax
    jmp cont1

cont1:
    mov i1,ax
    mov ax, i2
    test ax, ax
    jns cont2
    neg ax
    jmp cont2

cont2:
    add ax,i1
    mov res,ax
    ret

k_big:
    mov ax, i1
    test ax, ax
    jns cont3
    neg ax
    jmp cont3

cont3:
    mov bx,6
    CMP bx,ax
    JAE a1
    mov res,ax
    ret
a1:
    mov res, 6
    ret

Main ENDP
CODE ENDS
END Main