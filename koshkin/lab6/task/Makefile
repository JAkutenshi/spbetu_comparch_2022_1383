all: main.o asmfunctions.o 
	gcc main.o asmfunctions.o -masm=intel -Wall 
main.o: main.c 
	gcc main.c -c 
asmfunctions.o: asmfunctions.s
	as -msyntax=intel -mnaked-reg -mmnemonic=intel --gstabs asmfunctions.s -o asmfunctions.o
clear:
	rm *.o
run:
	./a.out