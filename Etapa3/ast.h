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