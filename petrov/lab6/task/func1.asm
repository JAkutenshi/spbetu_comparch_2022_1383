.MODEL FLAT
.CODE
public func1
func1 proc PROC C array : dword, res : dword, len : dword, min : dword, mass : dword

push eax
push ebx
push ecx
push edx
push edi
push esi


mov eax, 0
mov esi, array
mov edi, res


temp:
	cmp eax, len
	je exit
	mov ebx, [esi + 4*eax]
	mov ecx, ebx
	sub ebx, min
	mov edx, [edi + 4*ebx]
	inc edx
	mov [edi + 4*ebx], edx
	

	mov edi, mass
	add [edi + 4*ebx], ecx
	mov edi, res
	inc eax
	jmp temp


exit:
	pop eax
	pop ebx
	pop ecx
	pop edx
	pop edi
	pop esi

	ret
func1 ENDP
END