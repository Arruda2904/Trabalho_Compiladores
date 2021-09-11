%{
    #include "hash.h"
    #include "y.tab.h"
    int running = 1;  
    int lineNumber = 1;  
%}

%x COMMENT

%%

data                     {return KW_DATA;}
char                     {return KW_CHAR;}
int                      {return KW_INT;}
float                    {return KW_FLOAT;}
if                       {return KW_IF;}
else                     {return KW_ELSE;}
until                    {return KW_UNTIL;}
comefrom                 {return KW_COMEFROM;}
read                     {return KW_READ;}
print                    {return KW_PRINT;}
return                   {return KW_RETURN;}

[-;,:(){}+*/<>|&~=]      {return (int)yytext[0];}
"["                      {return (int)yytext[0];}
"]"                      {return (int)yytext[0];}

[0-9]+                   {yylval.symbol = hashInsert(yytext,LIT_INTEGER); return LIT_INTEGER;}
['].[']                  {yylval.symbol = hashInsert(yytext,LIT_CHAR); return LIT_CHAR;}
\"(\\.|[^(\n|")])*\"     {hashInsert(yytext,LIT_STRING); return LIT_STRING;}

[a-zA-Z][a-zA-Z0-9 ]*[a-zA-Z0-9]|[a-zA-Z] {yylval.symbol = hashInsert(yytext,TK_IDENTIFIER); return TK_IDENTIFIER;}

"<="                     {return OPERATOR_LE;}
">="                     {return OPERATOR_GE;}
"=="                     {return OPERATOR_EQ;}
"!="                     {return OPERATOR_DIF;}
".."                     {return OPERATOR_RANGE;}

"##".*              
"#/"                     {BEGIN(COMMENT);}
[ \t]    
"\n"                     {++lineNumber;}   
.                        {return TOKEN_ERROR;} 

<COMMENT>"/#"            {BEGIN(INITIAL);}
<COMMENT>"\n"            {++lineNumber;}
<COMMENT>.

%%

#include "y.tab.c"
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

void initMe(void)
{
    hashInit();
}

int yywrap()
  {
    running = 0;
    return 1;
  }