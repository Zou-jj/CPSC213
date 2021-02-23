CC = gcc
CFLAGS = -g -std=gnu11 -Og -Wall -Wno-unused-function

main: main.o implicit.o

clean:
	-/bin/rm -rf main main.o implicit.o
tidy: clean
	-/bin/rm -rf *~ .*~

main.o: main.c implicit.h	
implicit.o: implicit.c implicit.h	
