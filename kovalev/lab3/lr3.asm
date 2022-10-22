DOSSEG
.MODEL small

;;       / 15 - 2*i, при  a>b
;; f1 = <
;;       \ 3*i + 4, при  a<=b
;;
;;       / 7 - 4*i, при  a>b
;; f3 = <
;;       \ 8 - 6*i, при  a<=b
;;
;;       / max(i1, 10 - i2), при  k<0
;; f2 = <
;;       \ |i1 - i2|, при  k>=0

a EQU 1
b EQU 2
k EQU 3
i EQU 1

.STACK

.DATA
    f1  dw  0
    f3  dw  0
    f2  dw  0

.CODE
    mov ax, i                   ; ax = i
    shl ax, 1                   ; ax = 2*i

    mov cx, a
    cmp cx, b
    jle less1

    neg ax                      ; ax = -2*i
    mov dx, ax                  ; dx = -2*i
    shl dx, 1                   ; dx = -4*i
    add ax, 15                  ; ax = 15 - 2*i
    add dx, 7                   ; dx = 7 - 4*i
    jmp finish1

less1:
    add ax, i                   ; ax = 3*i
    mov dx, ax                  ; dx = 3*i
    shl dx, 1                   ; dx = 6*i
    add ax, 4                   ; ax = 3*i + 4
    neg dx                      ; dx = -6*i
    add dx, 8                   ; dx = 8 - 6*i

finish1:
    mov [f1], ax
    mov [f3], dx

    neg dx                      ; dx = -i2

    mov cx, k
    cmp cx, 0
    jge greater2

    add dx, 10                  ; dx = 10 - i2
    cmp ax, dx
    jg finish2
    mov ax, dx
    jmp finish2

greater2:
    add ax, dx                  ; ax = i1 - i2
    jns finish2
    neg ax

finish2:
    mov [f1], ax
END
