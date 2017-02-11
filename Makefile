# Makefile

OBJS	= bison.o lex.o main.o tree.o memory.o pretty.o typecheck.o symbol.o codegenerator.o

CC	= gcc
CFLAGS	= -g -Wall -pedantic

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

memory.o: memory.c memory.h
		$(CC) $(CFLAGS) -c memory.c -o memory.o

tree.o:  tree.c tree.h
		$(CC) $(CFLAGS) -c tree.c -o tree.o

pretty.o:  pretty.c pretty.h
		$(CC) $(CFLAGS) -c pretty.c -o pretty.o

typecheck.o:  typecheck.c typecheck.h
		$(CC) $(CFLAGS) -c typecheck.c -o typecheck.o

symbol.o:  symbol.c symbol.h
		$(CC) $(CFLAGS) -c symbol.c -o symbol.o

codegenerator.o:  codegenerator.c codegenerator.h
		$(CC) $(CFLAGS) -c codegenerator.c -o codegenerator.o

main.o:		main.c
		$(CC) $(CFLAGS) -c main.c -o main.o

lex.o yac.o main.o	: heading.h
lex.o main.o		: tok.h

clean:
	rm -f *.o *~ lex.c lex.yy.c bison.c tok.h minilang.tab.c minilang.tab.h minilang.output minilang
