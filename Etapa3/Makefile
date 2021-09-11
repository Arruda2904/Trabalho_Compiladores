#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 3
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in lexer.l
#

etapa3: y.tab.c lex.yy.c
	gcc -o etapa3 lex.yy.c
y.tab.c: parser.y
	yacc -d parser.y
lex.yy.c: scanner.l
	lex scanner.l 
clean:
	rm *.o lex.yy.c etapa3 y.output y.tab.c y.tab.h