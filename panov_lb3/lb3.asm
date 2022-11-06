dosseg
.MODEL small

;		/ 7 - 4*i , при a>b
;f3 = <
;		\ 8 -6*i , при a<=b
;
;		/ 20 - 4*i , при a>b
;f5 = <
;		\ -(6*i - 6), при a<=b
;
;
;		/ |i1 + i2|, при k=0
;f3 = <
;		\ min(i1,i2), при k/=0


a EQU 1
b EQU 1
k EQU 1
i EQU 2

.STACK


.DATA
    f1  dw  0
    f2  dw  0
    res  dw  0

.CODE
    mov ax, i                   ; ax = i
    shl ax, 1                   ; ax = 2*i
    


    mov cx, a
    cmp cx, b
    jle less
    
    ;ax отвечает за результат f3 
    ;dx отвечает за результат f5 

; a>b
    neg ax                     ; -2i
    shl ax, 1                  ; ax = -4i 
    mov dx, ax                 ; dx = -4i
    add ax, 7                  ; ax = -4i +7
    add dx, 20                 ; dx = -4i +20
    jmp finish1


; a<=b
less:
    add ax, i                  ; ax = 3i
    shl ax, 1                  ; ax = 6i
    neg ax                     ; ax = -6i
    mov dx, ax                 ; dx = -6i
    add ax, 8                  ; ax = -6i + 8
    add dx, 6                  ; dx = -6i + 6


finish1:
   mov [f1], ax                ;i1
    mov [f2], dx                ;i2

    mov cx, k
    cmp cx, 0
    je zer0

;k != 0

    cmp ax, dx
    jle finish2                    ; if i1 < i2
    mov dx, ax                     ; i1 = i2
    jmp finish2


zer0:
    add ax, dx                     ; i1 + i2
    cmp ax, 0  
    jge finish2                    ; if i1 + i2 <= 0
    neg ax
    jmp finish2


    

finish2:
    mov [res], ax
END