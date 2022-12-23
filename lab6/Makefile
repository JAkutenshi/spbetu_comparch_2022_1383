all: main

main: main.o lab6.o
	gcc main.o lab6.o -o main -z noexecstack

main.o: main.c
	gcc -c main.c

lab6.o: lab6.s
	as lab6.s -msyntax=intel -mnaked-reg -mmnemonic=intel -o lab6.o

clean:
	rm -f *.o main
