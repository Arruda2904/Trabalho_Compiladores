#include <stdlib.h>
#include <stdio.h>

int isRunning(void);
int getLineNumber(void);
void initMe(void);

int main(int argc, char **argv)
{
    extern FILE *yyin;
    int tok;
    if(argc < 2)
    {
        fprintf(stderr,"Call: ./a.out file_name\n");
        exit(1);
    }

    if (0==(yyin = fopen(argv[1],"r")))
    {
        printf("Cannot open file %s... \n",argv[1]);
        exit(1);
    }
    
    initMe();

    yyparse();

    hashPrint();

    fprintf(stderr, "Super! Compilation successful!\n");
    exit(0); // 0 is CODE for SUCCESS
}