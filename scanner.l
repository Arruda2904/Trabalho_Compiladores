%{
    #include "tokens.h"
    #include "hash.h"
    int running = 1;  
    int lineNumber = 1;  
%}

%x COMMENT

%%

data                     {return KW_DATA;}
char                     {return KW_CHAR;}
int                      {return KW_INT;}
float                    {return KW_FLOAT;}
if                       {return KW_INT;}
else                     {return KW_ELSE;}
until                    {return KW_UNTIL;}
comefrom                 {return KW_COMEFROM;}
read                     {return KW_READ;}
print                    {return KW_PRINT;}
return                   {return KW_RETURN;}

[a-z_0-9]+               {hashInsert(yytext,LIT_INTEGER); return LIT_INTEGER;}
[-;:(){}+*/<>|&~=]       {return (int)yytext[0];}
"["                      {return (int)yytext[0];}
"]"                      {return (int)yytext[0];}

[ \t]    
"\n"                    {++lineNumber;}   
"//".*              
"/*"                    {BEGIN(COMMENT);}
.                       {return TOKEN_ERROR;} 

<COMMENT>"*/"           {BEGIN(INITIAL);}
<COMMENT>"\n"           {++lineNumber;}
<COMMENT>.

%%

#include "main.c"
#include "hash.c"

int getLineNumber(void)
{   
    return lineNumber;
}

int isRunning(void)
{
    return running;
}

int yywrap()
  {
    running = 0;
    return 1;
  }