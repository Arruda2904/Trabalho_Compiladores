%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "hash.h"
    #include "ast.h"
    int yyerror();
    int yylex();
    int getLineNumber();
%}

%union
{
    HASH_NODE *symbol;
    AST *ast;
}

%token KW_CHAR           
%token KW_INT            
%token KW_FLOAT          
%token KW_DATA           

%token KW_IF             
%token KW_ELSE           
%token KW_UNTIL          
%token KW_COMEFROM       
%token KW_READ           
%token KW_PRINT          
%token KW_RETURN         

%token OPERATOR_LE       
%token OPERATOR_GE       
%token OPERATOR_EQ       
%token OPERATOR_DIF      
%token OPERATOR_RANGE    

%token<symbol> TK_IDENTIFIER     

%token<symbol> LIT_INTEGER       
%token<symbol> LIT_CHAR          
%token<symbol> LIT_STRING        

%token TOKEN_ERROR

%type<ast> expr
%type<ast> atribuicao
%type<ast> controle_fluxo
%type<ast> cmd_print
%type<ast> cont_cmd_print
%type<ast> lcmd
%type<ast> cmd

%left '&' '|' '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'

%%

programa: estrutura
    ;

estrutura: data func_list
    ;

data:  KW_DATA '{' decl_data '}'
    ;

decl_data: dec_var decl_data
    |
    ;

dec_var: tipo ':' TK_IDENTIFIER '=' literal ';'
    | tipo '['LIT_INTEGER OPERATOR_RANGE LIT_INTEGER']' ':' TK_IDENTIFIER inic_array ';'
    ;

func_list: func func_list
    | 
    ;

func: tipo ':' TK_IDENTIFIER '(' param_func ')' '{' lcmd '}' {astPrint($8,0);}
    ;

lcmd: cmd ';' lcmd                       {$$ = astCreate(AST_LCMD,0,$1,$3,0,0);}
    |                                    {$$ = 0;}
    ;

cmd:  atribuicao
    | controle_fluxo
    | KW_PRINT cmd_print                 {$$ = astCreate(AST_PRINT,0,$2,0,0,0);}
    | KW_RETURN expr                     {$$ = astCreate(AST_RETURN,0,$2,0,0,0);}
    | KW_COMEFROM ':' TK_IDENTIFIER      {$$ = astCreate(AST_SYMBOL,$3,0,0,0,0);}
    | '{' lcmd '}'                       {$$ = astCreate(AST_CMD_LCMD,0,$2,0,0,0);}
    | TK_IDENTIFIER                      {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    |                                    {$$ = 0;}
    ;

expr: LIT_INTEGER                     {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    | LIT_CHAR                        {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    | TK_IDENTIFIER                   {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    | expr '+' expr                   {$$ = astCreate(AST_ADD,0,$1,$3,0,0);}
    | expr '-' expr                   {$$ = astCreate(AST_SUB,0,$1,$3,0,0);}
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr '|' expr
    | expr '&' expr
    | '~' expr                        {$$ = 0;}
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | '(' expr ')'                    {$$ = $2;}
    | TK_IDENTIFIER '(' lexpr ')'     {$$ = 0;}
    | KW_READ                         {$$ = 0;}
    | TK_IDENTIFIER '[' expr ']'      {$$ = 0;}
    ;

lexpr: expr lexpr_cont
    |
    ;

lexpr_cont: ',' expr lexpr_cont
    |
    ;

literal:LIT_INTEGER
	| LIT_CHAR
	;

tipo:KW_CHAR
	| KW_INT
	| KW_FLOAT
	;

inic_array:'=' literal cont_inic_array
    |
    ;

cont_inic_array:literal cont_inic_array
    |
    ;

param_func:tipo ':' TK_IDENTIFIER cont_param_func
    |
    ;

cont_param_func:',' param_func
    |
    ;

atribuicao: TK_IDENTIFIER '=' expr              {$$ = astCreate(AST_ATTR,$1,$3,0,0,0);}
    | TK_IDENTIFIER '[' expr ']' '=' expr       {$$ = astCreate(AST_ASSIGN_ARRAY,$1,$3,$6,0,0);}
    ;

controle_fluxo: KW_IF '(' expr ')' cmd          {$$ = astCreate(AST_IF,0,$3,$5,0,0);}
    | KW_IF '(' expr ')' cmd KW_ELSE cmd        {$$ = astCreate(AST_IFE,0,$3,$5,$7,0);}
    | KW_UNTIL '(' expr ')' cmd                 {$$ = astCreate(AST_UNTIL,0,$3,$5,0,0);}
    ;

cmd_print: LIT_STRING cont_cmd_print            {$$ = astCreate(AST_PRINT_PARAM,$1,$2,0,0,0);}
    | expr cont_cmd_print                       {$$ = astCreate(AST_PRINT_PARAM,0,$1,$2,0,0);}
    ;

cont_cmd_print: ',' LIT_STRING cont_cmd_print   {$$ = astCreate(AST_PRINT_PARAM,$2,$3,0,0,0);}
    | ',' expr cont_cmd_print                   {$$ = astCreate(AST_PRINT_PARAM,0,$2,$3,0,0);}
    |                                           {$$ = 0;}
    ;

%%

int yyerror()
{
    fprintf(stderr,"Syntaxe error %s at line %d\n", yytext, getLineNumber());
    exit(3);
}