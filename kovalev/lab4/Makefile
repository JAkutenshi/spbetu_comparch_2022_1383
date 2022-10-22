##
# LR4
#
# @file
# @version 0.1

CC = gcc
CFLAGS ?= -Wall -Wextra -ggdb -masm=intel

all: main

main: main.o
	$(CC) $(CFLAGS) -o $@ $<

main.s: main.c
	$(CC) $(CFLAGS) -S -fverbose-asm -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o main

.PHONY: all

# end
