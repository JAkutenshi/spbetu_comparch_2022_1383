

 DOSSEG                                      ; Задание сегментов под ДОС
   .MODEL  SMALL                               ; Модель памяти-SMALL(Малая)
   .STACK  100h                                ; Отвести под Стек 256 байт
   .DATA                                       ; Начало сегмента данных
	a dw 0
	b dw 0
	i dw 0
	k dw 0
	i1 dw 0
	i2 dw 0
	res dw 0
   .CODE                                ; Начало сегмента кода
   mov  ax, @data                        ; Загрузка в DS адреса начала
   mov  ds, ax                           ; сегмента данных
   
mov ax, a
mov cx, i 	;i
shl cx, 1	;2i
add cx, i	;3i
cmp ax, b	;сравниваем равны ли a и b.
jle second 	;выполняет короткий переход, если первый операнд > второго операнда
first:          ;if(a>b)
shl cx, 1	;6i
sub cx, 4	;6i-4
neg cx

mov ax, i	;i
sub ax, 5	;i-5
shl ax, 1	;2i-10
shl ax, 1	;4i-20
neg ax          ;20-4i  
jmp result

second:	        ;if(a<=b)
add cx, 6	;3i+6

mov ax, cx	;3i+6
neg ax	        ;-3i-6
add ax, 9	;-3i+3
shl ax, 1	;-6i+6 

result:
	mov [i1], cx
	mov [i2], ax

getabs_i1:
	neg cx
	js getabs_i1
	cmp k, 0
jge final2	;короткий переход, если первый операнд >= второго операнда
final1:
	getabs_i2:
		neg ax
		js getabs_i2
	add cx, ax
	jmp answer

final2:
	cmp cx, 6
	jge answer
	mov cx, 6
answer:
	mov [res], cx
	mov ah, 4ch
	int 21h                          ; завершение программы и выход в ДОС
	END
