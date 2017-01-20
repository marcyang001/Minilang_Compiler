# Makefile

OBJS	= bison.o lex.o main.o

CC	= g++
CFLAGS	= -g -Wall -ansi -pedantic

minilang:		$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o minilang -ll

lex.o:		lex.c
		$(CC) $(CFLAGS) -c lex.c -o lex.o

lex.c:		minilang.lex 
		flex minilang.lex
		cp lex.yy.c lex.c

bison.o:	bison.c
		$(CC) $(CFLAGS) -c bison.c -o bison.o

bison.c:	minilang.y
		bison -d -v minilang.y
		cp minilang.tab.c bison.c
		cmp -s minilang.tab.h tok.h || cp minilang.tab.h tok.h

main.o:		main.cc
		$(CC) $(CFLAGS) -c main.cc -o main.o

lex.o yac.o main.o	: heading.h
lex.o main.o		: tok.h

clean:
	rm -f *.o *~ lex.c lex.yy.c bison.c tok.h minilang.tab.c minilang.tab.h minilang.output minilang
