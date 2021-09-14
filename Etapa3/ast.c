// AST- Abstract Syntax Tree

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1,AST* s2,AST* s3)
{
    AST* newnode;
    newnode = (AST*) calloc(1,sizeof(AST));
    newnode->type = type;
    newnode->symbol = symbol;
    newnode->son[0] = s0;
    newnode->son[1] = s1;
    newnode->son[2] = s2;
    newnode->son[3] = s3;
    return newnode;
}
void astPrint(AST *node, int level)
{
    int i;
    if(node == 0)
        return;
    for (i=0; i < level; ++i)
        fprintf(stderr,"  ");
    fprintf(stderr,"ast(");
    switch(node->type)
    {
        case AST_SYMBOL:  fprintf(stderr, "AST_SYMBOL"); break;
        case AST_ADD:  fprintf(stderr, "AST_ADD"); break;
        case AST_SUB:  fprintf(stderr, "AST_SUB"); break;
        case AST_ATTR:  fprintf(stderr, "AST_ATTR"); break;
        case AST_LCMD:  fprintf(stderr, "AST_LCMD"); break;
        case AST_IF:  fprintf(stderr, "AST_IF"); break;
        case AST_IFE:  fprintf(stderr, "AST_IFE"); break;
        case AST_UNTIL:  fprintf(stderr, "AST_UNTIL"); break;
        case AST_PRINT:  fprintf(stderr, "AST_PRINT"); break;
        case AST_RETURN:  fprintf(stderr, "AST_RETURN"); break;
        case AST_PRINT_PARAM:  fprintf(stderr, "AST_PRINT_PARAM"); break;
        case AST_ASSIGN_ARRAY:  fprintf(stderr, "AST_ASSIGN_ARRAY"); break;
        case AST_MULT:  fprintf(stderr, "AST_MULT"); break;
        case AST_DIV:  fprintf(stderr, "AST_DIV"); break;
        case AST_LESS:  fprintf(stderr, "AST_LESS"); break;
        case AST_GREATER:  fprintf(stderr, "AST_GREATER"); break;
        case AST_OR:  fprintf(stderr, "AST_OR"); break;
        case AST_AND:  fprintf(stderr, "AST_AND"); break;
        case AST_PARENTH:  fprintf(stderr, "AST_PARENTH"); break;
        case AST_LE:  fprintf(stderr, "AST_LE"); break;
        case AST_GE:  fprintf(stderr, "AST_GE"); break;
        case AST_EQ:  fprintf(stderr, "AST_EQ"); break;
        case AST_DIF:  fprintf(stderr, "AST_DIF"); break;
        case AST_LEXPR:  fprintf(stderr, "AST_LEXPR"); break;
        case AST_LEXPR_PARAM:  fprintf(stderr, "AST_LEXPR_PARAM"); break;
        case AST_NOT:  fprintf(stderr, "AST_NOT"); break;
        case AST_EXPR_ARRAY:  fprintf(stderr, "AST_EXPR_ARRAY"); break;
        case AST_CHAR:  fprintf(stderr, "AST_CHAR"); break;
        case AST_INT:  fprintf(stderr, "AST_INT"); break;
        case AST_FLOAT:  fprintf(stderr, "AST_FLOAT"); break;
        case AST_INIC_ARRAY:  fprintf(stderr, "AST_INIC_ARRAY"); break;
        case AST_CONT_INIC_ARRAY:  fprintf(stderr, "AST_CONT_INIC_ARRAY"); break;
        case AST_PARAM_FUNC:  fprintf(stderr, "AST_PARAM_FUNC"); break;
        case AST_CONT_PARAM_FUNC:  fprintf(stderr, "AST_CONT_PARAM_FUNC"); break;
        default:  fprintf(stderr, "AST_UNKNOWN"); break;
    }
    if (node->symbol != 0)
        fprintf(stderr,",%s\n",node->symbol->text);
    else
        fprintf(stderr,"0\n");
    for (i=0; i<MAX_SONS; ++i)
        astPrint(node->son[i], level+1);
    /*for (i=0; i < level; ++i)
        fprintf(stderr,"  -");*/
}


//END OF FILE