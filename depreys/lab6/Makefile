all: main.o asm_module.o
	gcc main.o asm_module.o -masm=intel -Wall

main.o: main.c
	gcc main.c -c

asm_module.o: asm_module.s
	as asm_module.s -msyntax=intel -mnaked-reg -mmnemonic=intel --gstabs -o asm_module.o

