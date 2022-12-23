all: main

main: task_.o task.o
	gcc task_.o task.o -o main -z noexecstack

task_.o: task_.c
	gcc -c task_.c

task.o: task.s
	as task.s -msyntax=intel -mnaked-reg -mmnemonic=intel -o task.o

clean:
	rm -f *.o main
