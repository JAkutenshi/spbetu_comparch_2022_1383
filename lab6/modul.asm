.586p
.model flat, c
.code

inter proc c uses edi esi, arr:dword, len:dword, LGrInt:dword, NInt:dword, res:dword

push eax
push ebx
push ecx
push edi
push esi

mov esi, arr
mov edi, LGrInt

mov ecx, len
sub eax, eax

for0:
sub ebx, ebx
mov eax, len
sub eax, ecx

for1:

push ecx
mov ecx, [esi + 4*eax]
cmp ecx, [edi + 4*ebx]
pop ecx

jl end_for1
inc ebx

cmp ebx, NInt
jge end_for1
jmp for1

end_for1:
dec ebx
mov edi, res
mov eax, [edi + 4*ebx]
inc eax
mov [edi + 4*ebx], eax
mov edi, LGrInt

loop for0

pop esi
pop edi
pop ecx
pop ebx
pop eax

ret

inter endp
end