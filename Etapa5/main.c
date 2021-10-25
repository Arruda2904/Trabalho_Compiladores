/*Gabriel Arruda dos Santos 00290400*/
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

int isRunning(void);
int getLineNumber(void);
void initMe(void);
int yyparse();
extern FILE *yyin;
FILE *out;

int main(int argc, char **argv)
{
    int tok;

    if (0==(yyin = fopen("input.txt","r")))
    {
        printf("Cannot open file input.txt \n");
        exit(1);
    }
    if (0==(out = fopen("output.txt","w"))) 
    {
        printf("Cannot open file output.txt \n");
        exit(1);
    }
    initMe();

    yyparse();

    hashPrint();

    fprintf(stderr, "Super! Compilation successful!\n");
    exit(0); // 0 is CODE for SUCCESS
}