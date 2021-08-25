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

decl: dec ',' decl
    | dec
    ;

dec: KW_INT ':' TK_IDENTIFIER
    | KW_INT ':' TK_IDENTIFIER '(' ')' body
    ;

body: '{' lcmd '}'
    ;

lcmd: cmd lcmd
    |
    ;

cmd: TK_IDENTIFIER '=' LIT_INTEGER
    ;

%%

int yyerror()
{
    fprintf(stderr,"Syntaxe error %s at line %d\n", yytext, getLineNumber());
    exit(3);
}