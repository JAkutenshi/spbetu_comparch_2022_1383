.global asm_function

# rdi <-- left_borders_arr
# rsi <-- rand_nums_arr
# rdx <-- result_arr
# rcx <-- NumRandDat
# r8 <-- Nint
# r9 <-- interval_sum_array
asm_function:
    push rax
    
sorting_out_numbers:
    lodsd

    push rcx

    mov rcx, r8
    jmp finding_interval
interval_found:
    pop rcx

    cmp r10, 0
    jl next_number

    incq [rdx][r10 * 4 - 4]
    add [r9][r10 * 4 - 4], eax

next_number:
    loop sorting_out_numbers

    pop rax
    ret


# eax <-- random_number
# r10 --> index of interval + 1
finding_interval:
    mov r10, -1 # interval index
    mov r11d, -1 # distance to interval
    mov r12, 0  # first flag
sorting_out_intervals:

    mov ebx, eax
    sub ebx, [rdi][rcx * 4 - 4]
    cmp ebx, 0
    jl next_iteration

if_first_iter:
    cmpq r12, 0
    jne not_first_iter
    movq r10, rcx
    mov r11d, ebx
    movq r12, 1
    jmp next_iteration
not_first_iter:

    cmp r11d, ebx
    jle next_iteration

    movq r10, rcx
    mov r11d, ebx


next_iteration:
    loop sorting_out_intervals

    jmp interval_found
