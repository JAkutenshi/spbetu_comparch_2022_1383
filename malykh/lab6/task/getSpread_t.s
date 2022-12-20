.global getSpread_t

getSpread_t:
    push rax 
    and rax, 0
    sub rcx, 1

loadNum:
    mov eax, [rdi]  # Берем число из rand_arr
    add rdi, 4      
    dec rdx         # Уменьшаем счётчик непросмотренных чисел в rand_arr
    push rcx        # Сохраняем Nint, т.к он будет счетчиком.

findInterval:
    cmp eax, [rsi][rcx * 4] 
    jge writeRes    
    loop findInterval

writeRes:
    incq [r8][rcx * 4]
    cmp eax, [r9][rcx * 4]
    jle recovery
    mov [r9][rcx * 4], eax
recovery:
    pop rcx            # восстанавлием счетчик оставшихся элементов в left_borders
    cmp rdx, 0
    jne loadNum
pop rax
.end
