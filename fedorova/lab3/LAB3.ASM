ind EQU 2
n1 EQU 500
n2 EQU -50
AStack SEGMENT STACK
DW 12 DUP(?)
AStack ENDS
DATA SEGMENT
a DW 2
b DW 1
i DW -1
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
    cmp cx,b
    jle f1_b
f1_a:
    mov ax, i
    ;add ax, i
    shl ax,1
    mov dx,ax
    mov ax, 15

    sub ax, dx
    mov i1, ax
    push i1
    jmp f2_a
f1_b:
    mov ax, i
    shl ax,1
    add ax, i
    ;add ax, i
    ;add ax, i
    add ax, 4
    mov i1, ax
    push i1
    jmp f2_b
f2_a:
    mov ax, i
    add ax, i
    ;add ax, i
    ;add ax,i
    shl ax, 1
    add ax, 3
    mov dx,ax
    mov ax, 0
    sub ax, dx
    mov i2, ax
    push i2
    jmp f3
f2_b:
    mov ax, i
    ;add ax, i
    ;add ax, i
    ;add ax, i
    ;add ax, i
    ;add ax, i
    shl ax, 1
    add ax, i
    shl ax, 1
    sub ax, 10
    mov i2, ax
    push i2
f3:
    pop ax;i2
    pop dx;i1
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

