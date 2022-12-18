; Стек  программы
AStack    SEGMENT  STACK
          DW 1024 DUP(?)  ; Отводится 1024 слов памяти
AStack    ENDS

; Данные программы
DATA      SEGMENT
          KEEP_CS DW 0  ; для хранения сегмента
          KEEP_IP DW 0  ; и смещения прерывания
          LEN DW 0
DATA      ENDS

; Код программы
CODE	SEGMENT
	ASSUME CS:CODE, DS:DATA, SS:AStack

BEEP  PROC FAR
	PUSH AX  ; сохранение изменяемых регистров
	PUSH CX
	PUSH DX
; действия по обработке прерывания

	MOV AL,10110110B ; Установка
	OUT 43H,AL       ; режима таймера

	IN AL,61H        ; Состояние динамика
	OR AL,00000011b  ; Включение
	OUT 61H, AL      ; динамика

	OUT 42H,AL
	MOV AL,AH
	OUT 42H,AL
	MOV CX,001eh
	mov dx,8480h
	;задержка
	mov ah,86h
	int 15h    ;15h - 86H прерывание ожидания
	;CX,DX = сколько микросекунд ждать
	IN AL,61H ; Выключение динамика
	AND AL,11111100B
	OUT 61H,AL

; восстановление регистров
	POP DX
	POP CX
	POP AX
	MOV AL, 20H
	OUT 20H, AL
	IRET
BEEP ENDP

; Головная процедура
Main	PROC  FAR
	PUSH DS
	sub AX,AX
	PUSH AX

	mov AX,DATA
	mov DS,AX

	mov ax, len
	MOV AH, 35H
	MOV AL, 23H
	INT 21H
	MOV KEEP_IP, BX
	MOV KEEP_CS, ES
	PUSH DS
	MOV DX, OFFSET BEEP
	MOV AX, SEG BEEP
	MOV DS, AX
	MOV AH, 25H
	MOV AL, 23H
	INT 21H
	POP DS

	skipnotcntrlc:
	mov ah, 0
	int 16h
	cmp al, 3
	jne skipnotcntrlc

	mov ah, 0
	int 16h ; считывание 1-9
	sub al, 31
	cmp al, 8
	jl seted
	mov al, 9
seted:
	mov cl, 100
	mul cx
	mov LEN, ax

	int 23h

	CLI
	PUSH DS
	MOV DX, KEEP_IP
	MOV AX, KEEP_CS
	MOV DS, AX
	MOV AH, 25H
	MOV AL, 23H
	INT 21H
	POP DS
	STI
	RET far

Main	ENDP
CODE	ENDS
	END Main
