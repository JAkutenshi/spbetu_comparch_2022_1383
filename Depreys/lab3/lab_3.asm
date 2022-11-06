ASSUME SS:Stack, CS:Code, DS:Data

Stack    SEGMENT  STACK
          DW 12 DUP('?')
Stack    ENDS

Data SEGMENT
    a DW 2
    b DW 1
    i DW 1
    k DW -1

    i1 DW ?
    i2 DW ?
    res DW ?
Data ENDS

Code SEGMENT

f1_f2 PROC NEAR
    mov ax, a
    cmp ax, b
    jg greater

less_or_equal:

    mov ax, i ; i
    sal ax, 1 ; i*2
    add ax, i ; i*3
    add ax, 4 ; i*3 + 4 / 3*(i - 1) + 7
    mov i1, ax ; i1 = i*3 + 4

    sub ax, 16 ; 3*(i - 1) - 9
    neg ax ; 9 - 3*(i - 1)
    jmp f1_f2_end

greater:

    mov ax, i ; i
    sal ax, 1 ; 2*i
    mov bx, ax
    sub ax, 15 ; 2*i - 15
    neg ax ; 15 - 2*i
    mov i1, ax ; i1 = 15 - 2*i

    mov ax, bx ; 2*i
    sal ax,1 ; 4*i
    add ax, bx ; 6*i
    add ax, 8 ; 6*i + 8
    neg ax ; -(6*i + 8)
    
f1_f2_end:
    mov i2, ax
    ret
f1_f2 ENDP


f3 PROC NEAR
    mov ax, k
    cmp ax, 0
    jl k_less_zero

k_not_less_zero:

    mov ax, i1 ; i1
    cmp ax, 0 ; i1 >= 0 ?
    jge i1_not_below_zero_k_upper

i1_below_zero_k_upper:

    neg ax ; -(i1)

i1_not_below_zero_k_upper:

    cmp ax, 6 ; |i1| >= 6 ?
    jg abs_i1_more_six


abs_i1_lower_six:

    mov ax, 6

abs_i1_more_six:

    jmp f3_end

k_less_zero:

    mov ax, i1 ; i1
    cmp ax, 0 ; i1 >= 0 ?
    jge i1_not_below_zero_k_lower

i1_below_zero_k_lower:

    neg ax ; -(i1)

i1_not_below_zero_k_lower:

    mov bx, i2 ; i2
    cmp bx, 0 ; i1 >= 0 ?
    jge i2_not_below_zero

i2_below_zero:

    neg bx ; -(i2)

i2_not_below_zero:

    add ax, bx ; (|i1| + |i2|)

f3_end:

    mov res, ax
    ret

f3 ENDP

main PROC FAR
    push  ds
    sub   ax,ax
    push  ax

    mov ax, Data
    mov ds, ax

    call f1_f2
    call f3


    ret
main ENDP

Code ENDS

END main