all: lab6_t.o getSpread_t.o 
	gcc lab6_t.o getSpread_t.o -masm=intel -Wall 
lab6_t.o: lab6_t.c 
	gcc lab6_t.c -c 
getSpread_t.o: getSpread_t.s
	as -msyntax=intel -mnaked-reg -mmnemonic=intel --gstabs getSpread_t.s -o getSpread_t.o
clean:
	rm lab6_t.o getSpread_t.o
