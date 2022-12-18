.MODEL FLAT
.CODE
public func2
func2 proc PROC C boards : dword, intervals : dword, distribution : dword, difference : dword, Nint : dword, X_min : dword

push eax
push ebx
push ecx
push edx
push edi
push esi
mov ecx, difference
mov ebx, Nint
dec ebx
mov eax, difference
add eax, X_min
dec eax
mov esi, distribution
mov edi, boards
mov edx, 0
func:
    cmp eax, [edi+ebx*4]
    jl temp
    dec ecx
    add edx, [esi+ecx*4]
    inc ecx
    dec eax
loop func
temp:
    mov edi, intervals
    mov [edi+ebx*4], edx
    mov edx, 0
    mov edi, boards
    dec ebx
    cmp ecx, 0
    jnz func

pop esi
pop edi
pop edx
pop ecx
pop ebx
pop eax
ret
func2 ENDP
END