all: lab6.o getSpread.o 
	gcc lab6.o getSpread.o -masm=intel -Wall 
lab6.o: lab6.c 
	gcc lab6.c -c 
getSpread.o: getSpread.s
	as -msyntax=intel -mnaked-reg -mmnemonic=intel --gstabs getSpread.s -o getSpread.o
clean:
	rm lab6.o getSpread.o
