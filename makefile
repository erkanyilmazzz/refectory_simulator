all:	 program
program: program.o arg.o
	gcc -o program  program.o arg.o -lpthread -Wall

arg.o : arg.c
	gcc -c	arg.c

program.o :program.c
	gcc -c	program.c

clear:
	rm *.o