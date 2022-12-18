.model flat
.code

public C func2
func2 PROC C arr1:dword, arr2:dword, res:dword, arr1_len:dword, index:dword, Xmin:dword

push eax
push ebx
push ecx
push edx
push esi
push edi

mov esi, arr1
mov edi, arr2
mov ecx, arr1_len ;i
mov edx, index

sub ecx, 1
sub edx, 1

loop1:
	cmp edx, 0
	jl finish
	mov ebx, [edi][edx*4]
	sub ebx, Xmin
	cmp ecx, ebx
	jl met1
		push edi
		mov edi, res
		mov ebx, [esi][ecx*4]
		mov eax, [edi+edx*4]
		add eax, ebx
		
		mov [edi+edx*4], eax
		pop edi
		jmp iter
	met1:
		sub edx, 1
		add ecx, 1
	iter:
	sub ecx, 1
	cmp ecx, 0
	jge loop1

finish:
pop edi
pop esi
pop edx
pop ecx
pop ebx
pop eax
ret
func2 endp
End