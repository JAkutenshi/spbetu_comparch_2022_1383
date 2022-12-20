##
# LR6
#
# @file
# @version 0.1

CC = gcc
CFLAGS ?= -Wall -Wextra -ggdb -masm=intel

all: main

main: main.o lr6asm.o random.o
	$(CC) $(CFLAGS) -o $@ $^

%.s: %.c
	$(CC) $(CFLAGS) -S -fverbose-asm -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.s
	as -msyntax=intel -mnaked-reg -mmnemonic=intel --gstabs -o $@ $^

# %.o: %.asm
# 	nasm -f elf64 -o $@ $^

clean:
	rm -f *.o main

.PHONY: all clean

# end
