.586p
.MODEL FLAT, C
.CODE
BORDER PROC C USES EDI ESI, array:dword, len:dword, LGrInt:dword, NInt:dword, maximums:dword, answer:dword

	push eax
	push ebx
	push ecx
	push edi
	push esi


	mov ecx, len
	mov esi, array
	mov edi, LGrInt
	mov eax, 0

cycle:
	mov ebx, 0
		search:
 			cmp ebx, NInt
			jge outside

			push eax
			mov eax, [esi + 4 * eax]
			cmp eax, [edi + 4 * ebx]
			pop eax
			jl outside
			inc ebx
			jmp search

		outside:
			dec ebx

			cmp ebx, -1
			je number
			mov edi, answer
			push eax
			mov eax, [edi + 4 * ebx]
			inc eax
			mov [edi + 4 * ebx], eax
			pop eax

			; task
			push eax
			mov edi, maximums
			mov eax, [esi + 4 * eax]
			cmp eax, [edi + 4 * ebx]
			jl task_end
			mov [edi + 4 * ebx], eax
		task_end:
			pop eax
			; task end

			mov edi, LGrInt

	number:
		inc eax

loop cycle

pop esi
pop edi
pop ecx
pop ebx
pop eax

ret

BORDER ENDP
END