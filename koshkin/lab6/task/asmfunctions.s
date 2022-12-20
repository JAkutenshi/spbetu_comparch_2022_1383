.global asmfunc1
asmfunc1:
    push rbp 
    mov rbp, rsp 
    push rdi
    push rax 

    sub rax, rax
mainloop:
    mov eax, DWORD PTR [rdi]
    add eax, ecx 
    inc QWORD PTR [rdx + rax*4]
    add rdi, 4
    dec esi
    cmp esi, 0
    jne mainloop 

    pop rax
    pop rdi
    mov rsp, rbp 
    pop rbp 
    ret

.global asmfunc2
# rcx - tmp
# rsi - result 
# rdi - borders 
# edx - NInt 
# r8d - arrange
# r9d - -Xmin
asmfunc2:
    push rbp 
    mov rbp, rsp 
    push rdi
    push rax

    mov r12d, r9d
    cmp r12d, 0 
    jge L0 
    neg r12d
L0:
    and r12d, 0x00000001
    mov r10d, edx
    mov rdx, 0
    mov r11d, 0
    cmp r11d, r10d
    je last
    # checking first border
    mov eax, DWORD PTR [rdi]
    add eax, r9d
    cmp eax, 0
    jne L1 
    mov DWORD PTR [rsi], -1;
    add rsi, 8
    add r11d, 1
L1:
    mov eax, DWORD PTR [rdi + r11*4]
    cmp r11d, r10d 
    je last
    add eax, r9d
L2:
    cmp edx, r8d
    je finish
    mov ebx, DWORD PTR [rcx + rdx*4]
    cmp edx, eax 
    je L3 
    add DWORD PTR [rsi], ebx 
    inc edx
    cmp r12d, 1
    jne L21 
    add DWORD PTR [rsi + 4], ebx
    mov r12d, 0
    jmp L2
L21:
    mov r12d, 1
    jmp L2
L3:
    add rsi, 8
    add r11d, 1
    add DWORD PTR [rsi], ebx 
    inc rdx
    cmp r12d, 1
    jne L31 
    add DWORD PTR [rsi + 4], ebx
    mov r12d, 0
    jmp L1 
L31:
    mov r12d, 1 
    jmp L1
last:
    add eax, r8d 
    inc eax 
    jmp L2
finish:
    pop rax
    pop rdi
    mov rsp, rbp 
    pop rbp
     
    ret



