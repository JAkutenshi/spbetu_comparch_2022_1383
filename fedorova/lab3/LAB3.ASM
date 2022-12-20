ind EQU 2
n1 EQU 500
n2 EQU -50
AStack SEGMENT STACK
DW 12 DUP(?)
AStack ENDS
DATA SEGMENT
a DW 2
b DW 2
i DW -3
k DW 0
i1 DW ?
i2 DW ?
res DW ?
DATA ENDS
CODE SEGMENT
ASSUME CS:CODE, DS:DATA, SS:AStack

       ;/ 15-2*i , ĐżŃĐž a>b
;f1 = <
       ;\ 3*i+4 , ĐżŃĐž a<=b

       ;/ - (4*i+3) , ĐżŃĐž a>b
;f2 = <
       ;\ 6*i -10 , ĐżŃĐž a<=b

       ;/ min(i1,i2), ĐżŃĐž k=0
;f3 = <
       ;\ max(i1,i2), ĐżŃĐž k/=0


Main PROC FAR
    push DS
    sub AX,AX
    push AX
    mov AX,DATA
    mov DS,AX
    mov cx,a
f1:
    mov ax, i
    shl ax,1
    cmp cx,b
    jle f1_b
f1_a:
    mov i1, 15
    sub i1, ax
    shl ax, 1
    add ax, 3
    neg ax
    mov i2, ax
    ;push i2
    jmp f3
f1_b:
    add ax, i
    add i1, 4
    add i1, ax
    shl ax, 1
    sub ax, 10
    mov i2, ax

f3:
    mov ax,i2
    mov dx,i1
    mov cx, k
    cmp cx,0
    jcxz f3_null
    cmp ax,dx
    jl res_sec
    mov res, ax
    jmp print
f3_null:
    cmp ax,dx
    jg res_sec
    mov res, ax
    jmp print
res_sec:
    mov res, dx
print:
    push res
    pop dx
    ret
Main ENDP
CODE ENDS
END Main

