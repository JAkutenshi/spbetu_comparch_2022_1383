AStack    SEGMENT  STACK
          DW 12 DUP('!')   
AStack    ENDS

DATA SEGMENT
a dw 0
b dw 0
i dw 0
k dw 0
i1 dw 0
i2 dw 0
res dw 0 
DATA ENDS

ASSUME CS:CODE, SS:AStack, DS:DATA

CODE SEGMENT
Main PROC FAR   
    push DS
    sub AX,AX
    push AX
    mov AX, DATA
    mov DS, AX

    mov ax,a
    cmp ax,b
    jg A_Great_B

    mov dx,i
    mov i1,dx
    sal i1,1
    mov dx,i
    add i1,dx

   
    mov dx,i
    mov i2,dx
    sal i2,1
    sal i2,1
    add dx,i
    add dx,i
    add dx,-10
    add i2,dx
    jmp FINAL

    A_Great_B:
        mov dx,i
        mov i1,dx
        sal i1,1
        neg i1
        add i1,15

        mov dx,i
        mov i1,dx
        sal i2,1
        sal i2,1
        add i2,3
        neg i2

    FINAL:
        mov ax,i1
        mov bx,i2
        cmp ax,bx
        jge NOT_SWITCH

        mov cx,ax
        mov ax,bx
        mov bx,cx

        NOT_SWITCH:
            mov cx,k
            cmp cx,0
            jne MX
            mov ax,bx
        MX:
            mov res,ax
Main ENDP
CODE ENDS
END Main