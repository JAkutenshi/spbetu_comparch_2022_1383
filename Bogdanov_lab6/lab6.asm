.686p
.MODEL FLAT, C
.CODE
counter PROC C USES EDI ESI, arr:dword, siz:dword, LGrInt:dword, NInt:dword, ans:dword
	push eax
	push ebx
	push ecx
	push edi
	push esi

	mov ecx, siz
	mov esi, arr
	mov edi, LGrInt
	mov eax, 0

	CYCLE:
		mov ebx, 0
	SEARCH:
 		cmp ebx, NInt
		jge O

		push eax
		mov eax, [esi + 4 * eax]

		cmp eax, [edi + 4 * ebx]
		pop eax
		jl O

		add ebx,1
		jmp SEARCH

	O:
		sub ebx,1
		cmp ebx, -1
		je NUMBER

		mov edi, ans
		push eax

		mov eax, [edi + 4 * ebx]
		add eax,1

		mov [edi + 4 * ebx], eax

		pop eax
		mov edi, LGrInt

	NUMBER:
		add eax,1

	loop CYCLE

	pop esi
	pop edi
	pop ecx
	pop ebx
	pop eax

ret

counter ENDP
END
