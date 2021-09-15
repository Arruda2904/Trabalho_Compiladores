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
%token<symbol> KW_READ           
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
%type<ast> lexpr
%type<ast> lexpr_cont
%type<ast> literal
%type<ast> tipo
%type<ast> inic_array
%type<ast> cont_inic_array
%type<ast> param_func
%type<ast> cont_param_func
%type<ast> func
%type<ast> func_list
%type<ast> data
%type<ast> decl_data
%type<ast> dec_var
%type<ast> programa

%left '&' '|' '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'

%%

programa: data func_list                          {$$ = astCreate(AST_PROG,0,$1,$2,0,0); astPrint($$,0); astDecompile($$);}
    ;

data:  KW_DATA '{' decl_data '}'                    {$$ = astCreate(AST_DATA,0,$3,0,0,0);};
    ;

decl_data: dec_var decl_data                                 {$$ = astCreate(AST_DECL_DATA,0,$1,$2,0,0);}
    |                                                        {$$ = 0;}
    ;

dec_var: tipo ':' TK_IDENTIFIER '=' literal ';'              {$$=astCreate(AST_DEC_VAR,$3,$1,$5,0,0);}                                   
    | tipo '['LIT_INTEGER OPERATOR_RANGE LIT_INTEGER']' ':' TK_IDENTIFIER inic_array ';' {$$=astCreate(AST_DEC_ARRAY,$8,$1,astCreate(AST_VEC_SIZE,$3,0,0,0,0),astCreate(AST_VEC_SIZE,$5,0,0,0,0),$9);}  
    ;

func_list: func func_list                                    {$$=astCreate(AST_FUNC_LIST,0,$1,$2,0,0);}
    |                                                        {$$ = 0;}
    ;

func: tipo ':' TK_IDENTIFIER '(' param_func ')' '{' lcmd '}' {$$=astCreate(AST_FUNC,$3,$1,$5,$8,0);}	
    ;

lcmd: cmd ';' lcmd                       {$$ = astCreate(AST_LCMD,0,$1,$3,0,0);}
    |                                    {$$ = 0;}
    ;

cmd:  atribuicao                         {$$ = $1;}      
    | controle_fluxo                     {$$ = $1;}
    | KW_PRINT cmd_print                 {$$ = astCreate(AST_PRINT,0,$2,0,0,0);}
    | KW_RETURN expr                     {$$ = astCreate(AST_RETURN,0,$2,0,0,0);}
    | KW_COMEFROM ':' TK_IDENTIFIER      {$$ = astCreate(AST_COMEFROM,$3,0,0,0,0);}
    | '{' lcmd '}'                       {$$ = astCreate(AST_CMD_LCMD,0,$2,0,0,0);}
    | TK_IDENTIFIER                      {$$ = astCreate(AST_IDENTIFIER,$1,0,0,0,0);}
    |                                    {$$ = 0;}
    ;

expr: LIT_INTEGER                     {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    | LIT_CHAR                        {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    | TK_IDENTIFIER                   {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    | expr '+' expr                   {$$ = astCreate(AST_ADD,0,$1,$3,0,0);}
    | expr '-' expr                   {$$ = astCreate(AST_SUB,0,$1,$3,0,0);}
    | expr '*' expr                   {$$ = astCreate(AST_MULT,0,$1,$3,0,0);}
    | expr '/' expr                   {$$ = astCreate(AST_DIV,0,$1,$3,0,0);}
    | expr '<' expr                   {$$ = astCreate(AST_LESS,0,$1,$3,0,0);}
    | expr '>' expr                   {$$ = astCreate(AST_GREATER,0,$1,$3,0,0);}
    | expr '|' expr                   {$$ = astCreate(AST_OR,0,$1,$3,0,0);}
    | expr '&' expr                   {$$ = astCreate(AST_AND,0,$1,$3,0,0);}
    | '~' expr                        {$$ = astCreate(AST_NOT,0,$2,0,0,0);}
    | expr OPERATOR_LE expr           {$$ = astCreate(AST_LE,0,$1,$3,0,0);}
    | expr OPERATOR_GE expr           {$$ = astCreate(AST_GE,0,$1,$3,0,0);}
    | expr OPERATOR_EQ expr           {$$ = astCreate(AST_EQ,0,$1,$3,0,0);}
    | expr OPERATOR_DIF expr          {$$ = astCreate(AST_DIF,0,$1,$3,0,0);}
    | '(' expr ')'                    {$$ = astCreate(AST_PARENTH,0,$2,0,0,0);}
    | KW_READ                         {$$ = astCreate(AST_READ,$1,0,0,0,0);}
    | TK_IDENTIFIER '(' lexpr ')'     {$$ = astCreate(AST_LEXPR,$1,$3,0,0,0);}
    | TK_IDENTIFIER '[' expr ']'      {$$ = astCreate(AST_EXPR_ARRAY,$1,$3,0,0,0);}
    ;

lexpr: expr lexpr_cont                {$$ = astCreate(AST_LEXPR_PARAM,0,$1,$2,0,0);}
    |                                 {$$ = 0;}
    ;

lexpr_cont: ',' expr lexpr_cont       {$$ = astCreate(AST_LEXPR_CONT,0,$2,$3,0,0);}
    |                                 {$$ = 0;}
    ;

literal:LIT_INTEGER                   {$$=astCreate(AST_SYMBOL,$1,0,0,0,0);}
	| LIT_CHAR                        {$$=astCreate(AST_SYMBOL,$1,0,0,0,0);}	
	;

tipo:KW_CHAR                          {$$=astCreate(AST_CHAR,0,0,0,0,0);}	
	| KW_INT                          {$$=astCreate(AST_INT,0,0,0,0,0);}
	| KW_FLOAT                        {$$=astCreate(AST_FLOAT,0,0,0,0,0);}
	;

inic_array:'=' literal cont_inic_array    {$$=astCreate(AST_INIC_ARRAY,0,$2,$3,0,0);}	
    |                                     {$$ = 0;}
    ;

cont_inic_array:literal cont_inic_array   {$$=astCreate(AST_CONT_INIC_ARRAY,0,$1,$2,0,0);}
    |                                     {$$ = 0;}
    ;

param_func:tipo ':' TK_IDENTIFIER cont_param_func {$$=astCreate(AST_PARAM_FUNC,$3,$1,$4,0,0);}
    |                                             {$$ = 0;}
    ;

cont_param_func:','tipo ':' TK_IDENTIFIER param_func {$$=astCreate(AST_CONT_PARAM_FUNC,$4,$2,$5,0,0);}
    |                                             {$$ = 0;}
    ;

atribuicao: TK_IDENTIFIER '=' expr              {$$ = astCreate(AST_ATTR,$1,$3,0,0,0);}
    | TK_IDENTIFIER '[' expr ']' '=' expr       {$$ = astCreate(AST_ASSIGN_ARRAY,$1,$3,$6,0,0);}
    ;

controle_fluxo: KW_IF '(' expr ')' cmd          {$$ = astCreate(AST_IF,0,$3,$5,0,0);}
    | KW_IF '(' expr ')' cmd KW_ELSE cmd        {$$ = astCreate(AST_IFE,0,$3,$5,$7,0);}
    | KW_UNTIL '(' expr ')' cmd                 {$$ = astCreate(AST_UNTIL,0,$3,$5,0,0);}
    ;

cmd_print: LIT_STRING cont_cmd_print            {$$ = astCreate(AST_PRINT_STRING,$1,$2,0,0,0);}
    | expr cont_cmd_print                       {$$ = astCreate(AST_PRINT_PARAM,0,$1,$2,0,0);}
    ;

cont_cmd_print: ',' LIT_STRING cont_cmd_print   {$$ = astCreate(AST_PRINT_STRING2,$2,$3,0,0,0);}
    | ',' expr cont_cmd_print                   {$$ = astCreate(AST_PRINT_PARAM2,0,$2,$3,0,0);}
    |                                           {$$ = 0;}
    ;

%%

int yyerror()
{
    fprintf(stderr,"Syntaxe error %s at line %d\n", yytext, getLineNumber());
    exit(3);
}