#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 5
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in lexer.l
#

etapa3: y.tab.o lex.yy.o hash.o ast.o main.o tacs.o
	gcc main.o lex.yy.o y.tab.o hash.o ast.o tacs.o -o etapa5

main.o: main.c
	gcc -c main.c

tacs.o: tacs.c
	gcc -c tacs.c

hash.o: hash.c
	gcc -c hash.c

ast.o: ast.c
	gcc -c ast.c

y.tab.o: y.tab.c 
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l 

clean:
	rm lex.yy.c y.tab.c *.o etapa5 output.txt y.tab.h