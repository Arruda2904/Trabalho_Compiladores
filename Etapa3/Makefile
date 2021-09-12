#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 3
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in lexer.l
#

etapa3: main.o lex.yy.o y.tab.o hash.o
	gcc -c main.o lex.yy.o y.tab.o hash.o -o etapa3

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

y.tab.o: y.tab.c 
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l 

clean:
	rm lex.yy.c y.tab.c *.o etapa3