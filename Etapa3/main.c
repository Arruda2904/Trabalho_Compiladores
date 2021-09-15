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
    if (argc < 3)
    {
        printf("call: ./etapa3 input.txt output.txt\n");
        exit(1);
    }
    if (0==(yyin = fopen(argv[1],"r")))
    {
        printf("Cannot open file %s... \n",argv[1]);
        exit(1);
    }
    if (0==(out = fopen(argv[2],"w"))) 
    {
        printf("Cannot open file %s... \n",argv[2]);
        exit(1);
    }
    initMe();

    yyparse();

    hashPrint();

    fprintf(stderr, "Super! Compilation successful!\n");
    exit(0); // 0 is CODE for SUCCESS
}