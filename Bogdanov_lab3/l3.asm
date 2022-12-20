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

    mov dx,i
    mov i1,dx
    sal i1,1
    mov ax,a
    cmp ax,b
    jg A_Great_B


    add i1,dx
    add i1,4

   
    mov dx,i1
    mov i2,dx
    sal i2,1
    sub i2,18
    jmp FINAL

    A_Great_B:
      
        sal i1,1
        neg i1
        add i1,15

        mov dx,i1
        mov i2,dx
        sal i2,1
        sub i2,33

    FINAL:
        mov ax,i1
        mov bx,i2
        cmp ax,i2
        jge NOT_SWITCH

       XCHG ax,cx

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
