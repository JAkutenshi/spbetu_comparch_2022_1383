.model flat
.code
public C func1
func1 proc PROC C array:dword, arr_size:dword, raspr_arr:dword, Xmin:dword

push eax
push ebx
push ecx
push edx
push edi
push esi

mov esi, array
mov edi, raspr_arr
mov ecx, 0
mov eax, 0
mov ebx, 0
loop1:
	mov eax, [esi][ecx*4]
	sub eax, Xmin
	mov ebx, [edi+4*eax]
	add ebx, 1
	mov [edi+4*eax], ebx
	;iteration
	add ecx, 1
	cmp ecx, arr_size
	jl loop1




pop esi
pop edi
pop edx
pop ecx
pop ebx
pop eax

ret

func1 ENDP
END