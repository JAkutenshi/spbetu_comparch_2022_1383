.MODEL FLAT, C
.CODE

PUBLIC C func 
func PROC C array:dword, arr_size:dword, raspr_arr:dword, Xmin:dword, arr2:dword, res:dword, raspr_len:dword, index:dword 
	push esi
	push edi
	push eax
	push ebx
	push ecx
	push edx

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
	;----------------------------------------------------------------------------------
	mov esi, raspr_arr
	mov edi, arr2
	mov ecx, raspr_len ;i
	mov edx, index

	sub ecx, 1
	sub edx, 1

	loop2:
		cmp edx, 0
		jl fin
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
		;iteration
		sub ecx, 1
		cmp ecx, 0
		jge loop2

	fin:


	pop edx
	pop ecx
	pop ebx
	pop eax
	pop edi
	pop esi
ret
func ENDP
END 