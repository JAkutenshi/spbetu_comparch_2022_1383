STR_LEN equ 5 ; кол-во символов в строке для ввода

; Стек  программы
AStack    SEGMENT  STACK
          DW 1024 DUP(?)  ; Отводится 1024 слов памяти
AStack    ENDS

; Данные программы
DATA      SEGMENT
          KEEP_CS DW 0  ; для хранения сегмента
          KEEP_IP DW 0  ; и смещения прерывания

          INPUT DB 0Dh, 0Ah, STR_LEN dup("$"), '$'
;,0dh,0ah - нова стока
          GREETING  DB 0dh,0ah,'Student from 1383 - Fedorova Oksana $'
DATA      ENDS

; Код программы
CODE      SEGMENT
          ASSUME CS:CODE, DS:DATA, SS:AStack

WriteMsg  PROC  NEAR
          mov   AH,9
          int   21h  ; Вызов функции DOS по прерыванию
          ret
WriteMsg  ENDP

SUBR_INT  PROC FAR
          PUSH AX  ; сохранение изменяемых регистров
          PUSH CX
          PUSH DX
; действия по обработке прерывания
          mov cx, STR_LEN
          mov di, offset INPUT  ; получаем смещение на начало сообщения
          add di, 2
        mov ah, 01h

        int 21h     ; в al код символа ‘5’

        sub  al,30h   ; теперь в al число 5
        mov cx, 0
        mov cl, al
      write_loop:
          int 21h
          mov [di], al ; помещаем символ в строку
          add di, 1
          loop write_loop
; вывод строк (сообщений)
          mov dx, offset INPUT
          call WriteMsg
          mov dx, offset GREETING
          call WriteMsg
; восстановление регистров
          POP  AX
          POP  CX
          POP  DX
          MOV  AL, 20H  ; для разрешения обрабоки прерываний
          OUT  20H,AL  ; с более низкими уровнями, чем только что обработанное
          IRET
SUBR_INT  ENDP

; Головная процедура
Main            PROC  FAR
          push  DS       ;\  Сохранение адреса начала PSP в стеке
          sub   AX,AX    ; > для последующего восстановления по
          push  AX       ;/  команде ret, завершающей процедуру.
          mov   AX,DATA   ; Загрузка сегментного
          mov   DS,AX     ; регистра данных.

          ; Запоминание текущего вектора прерывания
          MOV  AH, 35H   ; функция получения вектора
          MOV  AL, 23H   ; номер вектора
          INT  21H
          MOV  KEEP_IP, BX  ; запоминание смещения
          MOV  KEEP_CS, ES  ; и сегмента
          ; Установка вектора прерывания
          PUSH DS
          MOV  DX, OFFSET SUBR_INT ; смещение для процедуры в DX
          MOV  AX, SEG SUBR_INT    ; сегмент процедуры
          MOV  DS, AX          ; помещаем в DS
          MOV  AH, 25H         ; функция установки вектора
          MOV  AL, 23H         ; номер вектора
          INT  21H             ; меняем прерывание
          POP  DS

          expt:
                mov ah, 0
                int 16h ;Клавиатурный ввод (чтение клавиш)
                cmp al, 3;код ctrlC
                jne expt;переход, если не то нажато
          int 23h
          ; Восстановление изначального вектора прерывания
          CLI
          PUSH DS
          MOV  DX, KEEP_IP
          MOV  AX, KEEP_CS
          MOV  DS, AX
          MOV  AH, 25H
          MOV  AL, 23H
          INT  21H          ; восстанавливаем вектор
          POP  DS
          STI
          RET

Main      ENDP
CODE      ENDS
          END Main
