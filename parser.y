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

programa: LIT_INTEGER 
    | TK_IDENTIFIER
    ;

%%

int yyerror()
{
    fprintf(stderr,"Syntaxe error.\n");
    return 1;
}