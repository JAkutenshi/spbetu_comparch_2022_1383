; Стек  программы 
AStack    SEGMENT  STACK 
          DW 12 DUP(?)
AStack    ENDS

; Данные программы 
    DATA      SEGMENT

    a      DW    -2
    b      DW    5
    i      DW    1
    k      DW    -1 
    i1     DW    0
    i2     DW    0
    res    DW    0
    DATA      ENDS 
 
; Код программы 
CODE      SEGMENT 
          ASSUME CS:CODE, DS:DATA, SS:AStack 
 
; Головная процедура 
Main      PROC  FAR 
    push  DS
    sub   AX,AX 
    push  AX
    mov   AX,DATA 
    mov   DS,AX 
 
i_1_0:
    mov cx, a
    mov dx, b
    cmp dx, cx
    jge i_1_2; if(b>=a)

i_1_1:
    mov ax, i
    shl ax, 1; 2i
    shl ax, 1; 4i
    neg ax; -4i
    add ax, 7; -4i+7
    mov i1, ax
    jmp i_2_0

i_1_2:
    mov ax, i
    shl ax, 1; 2i
    add ax, i; 3i
    shl ax, 1; 6i
    neg ax; -6i
    add ax, 8
    mov i1, ax; -6i+8

i_2_0:
    cmp dx, cx
    jge i_2_2; if(b>=a)
    
i_2_1:
    mov ax, i
    shl ax, 1; 2i
    sub ax, 2; 2i-2
    jmp i_2_end

i_2_2:
    mov ax, i
    shl ax, 1; 2i
    add ax, i; 3i
    neg ax; -3i
    add ax, 2; 2-3i

i_2_end:
    mov i2, ax

res_0:
    mov cx, k
    mov dx, 0
    cmp cx, dx
    jge res_2; if(k>=0)

res_1:
    mov ax, i1
    mov bx, i2
    sub ax, bx; i1-i2
    cmp ax, 0
    jge res_1_1; if(i1-i2>=0)

res_1_abs:
    neg ax;|i1-i2|

res_1_1:
    cmp ax, 2
    jge res_1_end; if(|i1-i2|>=2)

    mov res, ax;|i1-i2|
    push ax
    jmp en

res_1_end:
    mov res, 2
    push [res]
    jmp en

res_2:
    mov ax, i2
    neg ax; -i2
    mov bx, -6
    cmp ax, bx
    jle res_2_2; if(-i2<=-6)

res_2_1:
    mov res, ax
    push ax
    jmp en

res_2_2:
    mov res, bx
    push bx
    jmp en
    
en:
    ret

Main      ENDP 
CODE      ENDS 
          END Main 
