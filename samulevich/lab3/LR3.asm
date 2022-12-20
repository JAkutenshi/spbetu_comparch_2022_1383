EOFLine EQU '$'
ASSUME CS: CODE, DS:DATA, SS:AStack
DATA SEGMENT
a DW 1h
b DW 1h
i DW -1h
k DW 1h
i1 DW ?
i2 DW ?
i3 DW ?
x DW ?
HELLO DB 'Assembler is the best!', 0AH, 0DH,EOFLine
DATA ENDS

AStack SEGMENT STACK
DW 12 DUP('0')
AStack ENDS

CODE SEGMENT

Main PROC FAR

push DS
sub AX,AX
push AX
mov AX, DATA
mov DS, AX


mov BX, a
mov CL, 1
mov AX, i
sal AX, CL


cmp BX, b
jle Less

sub AX, 2
mov i2, AX

add AX, 2
sal AX, CL
neg AX
add AX, 7
mov i1, AX

jmp Eif

Less:
add AX, i
mov x, AX

sal AX, CL
neg AX
add AX, 8
mov i1, AX

mov AX, x
neg AX
add AX, 2
mov i2, AX

Eif:


mov BX, k

cmp BX, 0
jl Less1

mov AX, i2
neg AX

cmp AX, -6
jl Less2
mov i3, AX
jmp Eif2

Less2:
mov i3, -6

Eif2:

jmp Eif1

Less1:
mov AX, i1
sub AX, i2

cmp AX, 0
jl Less3

jmp Eif3

Less3:
neg AX

Eif3:

cmp AX, 2
jl Less4
mov i3, 2
jmp Eif4

Less4:
mov i3, AX

Eif4:
Eif1:

mov DX, OFFSET HELLO
mov AH,9
int 21h
ret

Main ENDP
CODE ENDS
END Main