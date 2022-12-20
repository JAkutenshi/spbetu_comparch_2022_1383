.486
.MODEL FLAT
.CODE
public func
func proc PROC C array:dword, 
Numbers:dword, LGrInt:dword, NInt:dword, result:dword

push eax
push ebx
push edi
push esi

mov esi, array
mov edi, LGrInt
mov eax, 0

start: 
	mov ebx, 0	;индекс текущего интервала
	next_border:
 		cmp ebx, NInt
		jge this_border		;если ebx>=NInt выходим из цикла
		push eax
		mov eax, [esi + 4 * eax]	;кладем в eax элемент массива array
		cmp eax, [edi + 4 * ebx]	;сравниваем элемент с текущей левой границей
		pop eax
		jl this_border	;если eax<[edi + 4 * ebx] выходим из цикла
		inc ebx 
		jmp next_border	;иначе переходим к следующему интервалу

	this_border:	;когда вышли из цикла
		dec ebx
		cmp ebx, -1
		je next_num		;если вышли за границу интервалов 
		mov edi, result
		push eax
		mov eax, [edi + 4 * ebx]	;помещаем в eax помещаем элемент массива 
									;result с индексом ebx
		inc eax
		mov [edi + 4 * ebx], eax	;устанавливаем полученное значение 
									;обратно в массив result
		pop eax
		mov edi,LGrInt

	next_num:
		inc eax		;индекс следующего числа
		cmp eax, Numbers
		jg exit
jmp start		;начинаем новую итерацию

exit:
pop esi
pop edi
pop ebx
pop eax

ret

func ENDP
END