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

%token TK_IDENTIFIER     

%token LIT_INTEGER       
%token LIT_CHAR          
%token LIT_STRING        

%token TOKEN_ERROR

%%

programa: decl
    ;

decl: dec resto
    |
    ;

resto: ';' dec resto
    |
    ;

dec: tipo ':' TK_IDENTIFIER '=' literal
    | tipo '['LIT_INTEGER OPERATOR_RANGE LIT_INTEGER']' ':' TK_IDENTIFIER inic_array
    | tipo ':' TK_IDENTIFIER '(' ')' body
    ;

body: '{' lcmd '}'
    ;

lcmd: cmd lcmd
    |
    ;

cmd: TK_IDENTIFIER '=' expr
    ;

expr: LIT_INTEGER
    | LIT_CHAR
    | LIT_STRING
    | TK_IDENTIFIER
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr OPERATOR_EQ expr
    | '(' expr ')'
    ;

literal:
	LIT_INTEGER
	| LIT_CHAR
	;

tipo:
    KW_CHAR
	| KW_INT
	| KW_FLOAT
	;

inic_array:
    '=' literal cont_inic_array
    |
    ;

cont_inic_array:
    literal cont_inic_array
    |
    ;
%%

int yyerror()
{
    fprintf(stderr,"Syntaxe error %s at line %d\n", yytext, getLineNumber());
    exit(3);
}