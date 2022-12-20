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
	mov ebx, 0	;������ �������� ���������
	next_border:
 		cmp ebx, NInt
		jge this_border		;���� ebx>=NInt ������� �� �����
		push eax
		mov eax, [esi + 4 * eax]	;������ � eax ������� ������� array
		cmp eax, [edi + 4 * ebx]	;���������� ������� � ������� ����� ��������
		pop eax
		jl this_border	;���� eax<[edi + 4 * ebx] ������� �� �����
		inc ebx 
		jmp next_border	;����� ��������� � ���������� ���������

	this_border:	;����� ����� �� �����
		dec ebx
		cmp ebx, -1
		je next_num		;���� ����� �� ������� ���������� 
		mov edi, result
		push eax
		mov eax, [edi + 4 * ebx]	;�������� � eax �������� ������� ������� 
									;result � �������� ebx
		inc eax
		mov [edi + 4 * ebx], eax	;������������� ���������� �������� 
									;������� � ������ result
		pop eax
		mov edi,LGrInt

	next_num:
		inc eax		;������ ���������� �����
		cmp eax, Numbers
		jg exit
jmp start		;�������� ����� ��������

exit:
pop esi
pop edi
pop ebx
pop eax

ret

func ENDP
END