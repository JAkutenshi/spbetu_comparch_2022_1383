STACKSG SEGMENT  PARA STACK 'Stack'
        DW       512 DUP(?)
STACKSG	ENDS

DATASG  SEGMENT  PARA 'Data'; SEG DATA
	KEEP_CS DW 0 ;
        MESSAGE1 DB '��ॢ�� �� ॣ���� AX � ��ப�: $'
        MESSAGE2 DB '��ॢ�� �� ��ப� � ॣ���� AX � ���⭮: $'
	STRING DB 35 DUP('#')
DATASG	ENDS; ENDS DATA


CODE SEGMENT; SEG CODE
ASSUME  DS:DataSG, CS:Code, SS:STACKSG
;-32 768:+32 767





AX_TO_STR PROC NEAR
	jmp start_1
	delete_nul DW 0
start_1:
	mov delete_nul, 0
	mov DI, 0h; DI - ������ ⥪�饣� ᨬ���� ��ப�
    cmp AX, 0
	jge positive
			
negative:
	mov STRING[DI], '-'
	add DI, 1 ;�������㥬 �᫮ � �ਡ���塞 �������
	not AX
	add AX,1
	jmp scan_ax

check_nul:
	cmp delete_nul, 0
	je skip_char
	jmp no_skip_char

positive:
	mov STRING[DI], '+'
	add DI, 1
	cmp AX, 0
	je case_nul

scan_ax:
	mov SI,AX ; �����뢠�� � si, ax
	mov	cx, 4		; � ᫮�� 4 ������ (���㡠��)

next_char:
	rol	ax, 1		; �뤢����� ����訥 4 ���
	rol	ax, 1
	rol	ax, 1
	rol	ax, 1
	push	ax		; ��࠭�� AX
	and	al, 0Fh		; ��⠢�塞 4 ������ ��� AL
	cmp	al, 0Ah		; �ࠢ������ AL � ���祭��� 10
	sbb	al, 69h		; 楫��᫥���� ���⠭�� � ��񬮬
	das			; BCD-���४�� ��᫥ ���⠭��
	cmp al, '0'
	je check_nul
	mov delete_nul, 1

no_skip_char:
	mov STRING[DI], al
	add DI, 1

skip_char:
	pop	ax		; ����⠭���� AX
	loop next_char
	jmp end_1

case_nul:
	mov STRING[DI], '0'
	add DI, 1

end_1: ; ����� ��諨 �� ॣ�����
	mov STRING[DI],'$' ; ������塞 � ����� ��ப� ᨬ��� ���� ��ப�
	mov DX,offset STRING ; �����뢠�� � dx ᤢ�� ��ப�
	ret
AX_TO_STR ENDP	






STR_TO_AX PROC FAR
	jmp start_2
	IS_NEG DB 0; �⢥砥� �� ���� �᫠

start_2:
	mov AX,0; ����塞 ax
	mov CX, 0
	mov SI,0; �� ������ ��ப� �㤥� �⢥��� si
	cmp STRING[SI],'-' ; �ࠢ������ ���� ����� ��ப� � ����ᮬ
	jne positive_parse; �᫨ �� ࠢ�� ������, � �᫮ ������⥫쭮�
	;�᫨ ࠢ�� � ����⥫쭮�
	mov IS_NEG,1; � is_neg �����뢠�� 1

positive_parse: ; �᫨ �᫮ ������⥫쭮
	mov SI,0 ; ������ � SI 0

len_loop: ; ��⠥� ����� ��ப�
	add SI,1
	cmp STRING[SI],'$' ; �ࠢ������ ����� ��ப� � $
	jne len_loop ; �᫨ �� ࠢ�� $ � �����頥��� � 横�

	mov DI, SI
	lea SI, STRING
	inc SI
	xor cx, cx
	cld

number_construct:
	xor AX, AX
	dec DI ; ���६��⨬ DI
	cmp DI,0 ; �ࠢ������ DI � 0
	jle done ; DI <= 0
	lodsb
	cmp al, 'A'
	jge bukva

continue:
	sub al, '0'
	xchg ax, cx
	mov dx, 10h
    mul dx
	add cx, ax
	jmp number_construct
done:
	mov ax, cx
	cmp IS_NEG, 1
	je check_negative
	jmp end_2

bukva:
	sub al, 7
	jmp continue

check_negative:
	not ax
	add ax, 1

end_2:
	ret
STR_TO_AX ENDP





Main PROC FAR
   	mov  ax, DATASG                     
   	mov  ds, ax   
	
        mov DX, offset MESSAGE1
        mov ah,09h;
	int 21h;
	mov AX, 0h ; ������ ॣ���� AX
	pushf
	call AX_TO_STR
	mov ah,09h;
	int 21h;
	
	mov dl, 10
	mov ah, 02h
	int 21h
	mov dl, 13
	mov ah, 02h
	int 21h

        mov DX, offset MESSAGE2
        mov ah,09h;
	int 21h;
	mov ax, 0
	call STR_TO_AX
	popf
	call AX_TO_STR

	mov ah,09h
	int 21h

	mov ah,4Ch;
	int 21h;
	
Main      ENDP
CODE      ENDS
END Main