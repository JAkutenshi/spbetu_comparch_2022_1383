all: main.o modules.o
	gcc main.o modules.o -masm=intel -Wall
main.o: main.c
	gcc main.c -c -o main.o
modules.o: modules.s
	as -msyntax=intel -mnaked-reg -mmnemonic=intel --gstabs modules.s -o modules.o
clear:
	rm *.o
txt:
	./a.out > a.txt
	gnuplot a.plot
