.global funcAsm1
funcAsm1:                       # rdi -- int* arr
    push rbp                    # rsi -- int64* tmp
    mov rbp, rsp                # edx -- int (Xmax - Xmin)
                                # ecx -- int NumRanDat
                                # r8d -- int Xmin
    push rdi
    push rax
arrLoop:
    mov eax, DWORD PTR [rdi]
    sub eax, r8d
    cmp eax, 0
    jl skip
    cmp eax, edx
    jg skip
    inc QWORD PTR [rsi + rax * 8]
skip:
    add rdi, 4
    loop arrLoop

    pop rax
    pop rdi
    mov rsp, rbp
    pop rbp
    ret

.global funcAsm2
funcAsm2:                       # rdi -- int64* tmp
    push rbp                    # rsi -- int* borders
    mov rbp, rsp                # rdx -- int* results
    push r11                    # ecx -- int (Xmax - Xmin)
    push rbx                    # r8d -- int NInt
                                # r9d -- int Xmin
                                # r10d -- int Xmax
    mov r10, QWORD PTR [rbp + 2 * 8]

    push rax
    push rcx
    push rdi

    xor rax, rax
suffixLoop:
    add rax, QWORD PTR [rdi]
    mov QWORD PTR [rdi], rax
    add rdi, 8
    loop suffixLoop

    pop rdi
    push rdi

    push rdx
    push rsi

    mov eax, DWORD PTR [rsi]
    sub eax, r9d
    mov rax, QWORD PTR [rdi + rax * 8]
    mov DWORD PTR [rdx], eax
    add rdx, 4

    mov ecx, r8d
    sub rcx, 2
resultsLoop:
    mov eax, DWORD PTR [rsi]
    sub eax, r9d
    mov rbx, QWORD PTR [rdi + rax * 8]

    mov eax, DWORD PTR [rsi + 4]
    cmp eax, r10d
    jle skip2
    dec eax
skip2:
    sub eax, r9d
    mov r11, QWORD PTR [rdi + rax * 8]

    sub r11, rbx
    mov DWORD PTR [rdx], r11d

    add rdx, 4
    add rsi, 4
    loop resultsLoop

    pop rsi
    pop rdx

    pop rdi
    pop rcx
    pop rax

    pop rbx
    pop r11
    mov rsp, rbp
    pop rbp
    ret
