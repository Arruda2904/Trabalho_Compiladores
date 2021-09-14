// AST- Abstract Syntax Tree

#include "hash.h"
#ifndef AST_HEADER

#define AST_HEADER
#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3
#define AST_ATTR 4
#define AST_LCMD 5
#define AST_IF 6
#define AST_IFE 7
#define AST_UNTIL 8
#define AST_PRINT 9
#define AST_RETURN 10
#define AST_CMD_LCMD 11
#define AST_PRINT_PARAM 12
#define AST_ASSIGN_ARRAY 13
#define AST_MULT 14
#define AST_DIV 15
#define AST_LESS 16
#define AST_GREATER 17
#define AST_OR 18
#define AST_AND 19
#define AST_PARENTH 20
#define AST_LE 21
#define AST_GE 22
#define AST_EQ 23
#define AST_DIF 24
#define AST_LEXPR 25
#define AST_LEXPR_PARAM 26
#define AST_NOT 27
#define AST_EXPR_ARRAY 28
#define AST_CHAR 29
#define AST_INT 30
#define AST_FLOAT 31
#define AST_INIC_ARRAY 32
#define AST_CONT_INIC_ARRAY 33
#define AST_PARAM_FUNC 34
#define AST_CONT_PARAM_FUNC 35
#define AST_FUNC 36
#define AST_FUNC_LIST 37
#define AST_LEXPR_CONT 38
#define AST_COMEFROM 39
#define AST_IDENTIFIER 40
#define AST_READ 41
#define AST_DATA 42
#define AST_DECL_DATA 43
#define AST_DEC_VAR 44
#define AST_DEC_ARRAY 45
#define AST_VEC_SIZE 46


typedef struct astnode
{
    int type;
    HASH_NODE *symbol;
    struct astnode *son[MAX_SONS];
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1,AST* s2,AST* s3);
void astPrint(AST *node,int level);


#endif

//END OF FILE