.MODEL FLAT
.CODE
public func1
func1 proc PROC C array : dword, res : dword, len : dword, min : dword

push eax
push ebx
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
	sub ebx, min
	mov edx, [edi + 4*ebx]
	inc edx
	mov [edi + 4*ebx], edx
	inc eax
	jmp temp

exit:
	pop eax
	pop ebx
	pop edx
	pop edi
	pop esi
	ret
func1 ENDP
END