int main(int argc, char **argv)
{
    int tok;
    if(argc < 2)
    {
        fprintf(stderr,"Call: ./a.out file_name\n");
        exit(1);
    }
    yyin = fopen(argv[1], "r");
    hashInit();
    while(running)
    {  
        tok = yylex();
        if(!running)
        {
            break;
        }
        switch(tok)
        {
            case KW_INT: printf("Encontrei KW_INT\n"); break;
            case LIT_INTEGER: printf("Encontrei LIT_INT\n"); break;
            case TOKEN_ERROR: printf("Unexpected tokken %d\n",tok); break;
            default: printf("Encontrei %c\n", yytext[0]); break;
        }
    }
    printf("Main done! File has %d lines.\n", lineNumber);
    hashPrint();
    exit(0);
}