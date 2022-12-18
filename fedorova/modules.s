.global module
module:

next_elem:
	mov ebx, [rdi][(rcx - 1)*4]
	mov eax, 0
next_border:
	cmp ebx, [rsi][rax*4]
	jle write
	inc eax
	cmp eax, r8d
	jle next_border
	jmp end
write:
	incq [rdx][rax*4]
	inc eax
	cmp eax, r8d
	jl next_border
end:
	loop next_elem
ret

;	                  # rdi -- int* arr
;                   # rsi -- int* LGrInt
;                  # rdx -- int* res
;                   # ecx -- int NumRanDat
;                    # r8d -- int NInt
