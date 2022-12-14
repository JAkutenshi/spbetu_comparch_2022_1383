; Учебная программа  лабораторной работы №2 по дисциплине "Архитектура компьютера"
;
;
EOL  EQU  '$'
ind  EQU   2
n1   EQU  500
n2   EQU  -50

; Стек  программы

AStack    SEGMENT  STACK
          DW 12 DUP(?)
AStack    ENDS

; Данные программы

DATA      SEGMENT

;  Директивы описания данных

mem1      DW    0
mem2      DW    0
mem3      DW    0
vec1      DB    31,32,33,34,38,37,36,35
vec2      DB    50,60,-50,-60,70,80,-70,-80
matr      DB    -4,-3,7,8,-2,-1,5,6,-8,-7,3,4,-6,-5,1,2

DATA      ENDS

; Код программы

CODE      SEGMENT
          ASSUME CS:CODE, DS:DATA, SS:AStack

; Головная процедура
Main      PROC  FAR
          push  DS
          sub   AX,AX
          push  AX
          mov   AX,DATA
          mov   DS,AX

;  ПРОВЕРКА РЕЖИМОВ АДРЕСАЦИИ НА УРОВНЕ СМЕЩЕНИЙ
;  Регистровая адресация
          mov  ax,n1
          mov  cx,ax
          mov  bl,EOL
          mov  bh,n2
;  Прямая   адресация
          mov  mem2,n2
          mov  bx,OFFSET vec1
          mov  mem1,ax
;  Косвенная адресация
          mov  al,[bx]
          mov  ax,[bx]
          mov  mem3,ax
;  Базированная адресация
          mov  al,[bx]+3
          mov  cx,3[bx]
;  Индексированная адресация
          mov  di,ind
          mov  al,vec2[di]
          mov  cl,vec2[di]
;  Адресация с базированием и индексированием
          mov  bx,3
          mov  al,matr[bx][di]
          mov  cl,matr[bx][di]
          shl  bx,1
          shl  bx,1
          mov  al,matr[bx][di]

;  ПРОВЕРКА АДРЕСАЦИИ С УЧЕТОМ СЕГМЕНТОВ
;  Переопределение сегмента
;  ------ вариант 1
          mov  ax, SEG vec2
          mov  es, ax
          mov  ax, es:[bx]
          mov  ax, 0
;  ------ вариант 2
          mov  es, ax
          push ds
          pop  es
          mov  cx, es:[bx-1]
          xchg cx,ax
;  ------ вариант 3
          mov  di,ind
          mov  es:[bx+di],ax
;  ------ вариант 4
          mov  bp,sp
          add  bx,bp
          mov  al,matr[bx]
          add  di,si
          add  bp,di
          mov  al,matr[bp]
;  Использование сегмента стека
          push  mem1
          push  mem2
          mov   bp,sp
          mov   dx,[bp]+2
          ret   
Main      ENDP
CODE      ENDS
          END Main
