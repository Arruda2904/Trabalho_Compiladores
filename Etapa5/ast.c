/*Gabriel Arruda dos Santos 00290400*/
// AST- Abstract Syntax Tree

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
extern FILE *out;

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
    if(!node)
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
        case AST_FUNC:  fprintf(stderr, "AST_FUNC"); break;
        case AST_FUNC_LIST:  fprintf(stderr, "AST_FUNC_LIST"); break;
        case AST_LEXPR_CONT:  fprintf(stderr, "AST_LEXPR_CONT"); break;
        case AST_COMEFROM:  fprintf(stderr, "AST_COMEFROM"); break;
        case AST_IDENTIFIER:  fprintf(stderr, "AST_IDENTIFIER"); break;
        case AST_READ:  fprintf(stderr, "AST_READ"); break;
        case AST_DATA:  fprintf(stderr, "AST_DATA"); break;
        case AST_DECL_DATA:  fprintf(stderr, "AST_DECL_DATA"); break;
        case AST_DEC_VAR:  fprintf(stderr, "AST_DEC_VAR"); break;
        case AST_DEC_ARRAY:  fprintf(stderr, "AST_DEC_ARRAY"); break;
        case AST_VEC_SIZE:  fprintf(stderr, "AST_VEC_SIZE"); break;
        case AST_PROG:  fprintf(stderr, "AST_PROG"); break;
        case AST_PRINT_STRING:  fprintf(stderr, "AST_PRINT_STRING"); break;
        case AST_PRINT_STRING2:  fprintf(stderr, "AST_PRINT_STRING2"); break;
        case AST_PRINT_PARAM2:  fprintf(stderr, "AST_PRINT_PARAM2"); break;
        default:  fprintf(stderr, "AST_UNKNOWN"); break;
    }
    if (node->symbol)
        fprintf(stderr,",%s\n",node->symbol->text);
    else
        fprintf(stderr," \n");
    for (i=0; i<MAX_SONS; ++i)
        astPrint(node->son[i], level+1);
}

void astDecompile(AST *node)
{
    if (!node)
        return;
    switch (node->type)
    {

    case AST_PROG:
        astDecompile(node->son[0]);
        astDecompile(node->son[1]);
        break;
    case AST_DATA:
        fprintf(out, "data {\n");
        astDecompile(node->son[0]);
        fprintf(out, "\n}\n");
        break;
    case AST_DECL_DATA:
        astDecompile(node->son[0]);
        astDecompile(node->son[1]);
        break;
    case AST_FUNC_LIST:
        astDecompile(node->son[0]);
        astDecompile(node->son[1]);
        break;
    case AST_FUNC:
        astDecompile(node->son[0]);
        fprintf(out,":%s(",node->symbol->text);
        astDecompile(node->son[1]);
        fprintf(out,"){\n");
        astDecompile(node->son[2]);
        fprintf(out,"}\n");
        break;
    case AST_PARAM_FUNC:
        astDecompile(node->son[0]);
        fprintf(out,":%s",node->symbol->text);
        astDecompile(node->son[1]);
        break;
    case AST_CONT_PARAM_FUNC:
        fprintf(out,",");
        astDecompile(node->son[0]);
        break;
    case AST_LCMD:
        astDecompile(node->son[0]);
        fprintf(out,";\n ");
        astDecompile(node->son[1]);
        break;
    case AST_CMD_LCMD:
        fprintf(out,"{\n");
        astDecompile(node->son[0]);
        fprintf(out,"\n}");
        break;
    case AST_ATTR:
        fprintf(out,"%s", node->symbol->text);
        fprintf(out," = ");
        astDecompile(node->son[0]);
        break;
    case AST_ASSIGN_ARRAY:
        fprintf(out, "%s", node->symbol->text);
        fprintf(out, "[");
        astDecompile(node->son[0]);
        fprintf(out, "]");
        fprintf(out, " = ");
        astDecompile(node->son[1]);
        break;
    case AST_SYMBOL:
        fprintf(out,"%s",node->symbol->text);
        break;
    case AST_EXPR_ARRAY:
        fprintf(out, "%s", node->symbol->text);
        fprintf(out, "[");
        astDecompile(node->son[0]);
        fprintf(out, "]");
        break;
    case AST_PARENTH:
        fprintf(out, "(");
        astDecompile(node->son[0]);
        fprintf(out, ")");
        break;
    case AST_NOT:
        fprintf(out, "~");
        astDecompile(node->son[0]);
        break;
    case AST_LEXPR:
        fprintf(out,"%s", node->symbol->text);
        fprintf(out," (");
        astDecompile(node->son[0]);
        fprintf(out,")");
        break; 
    case AST_ADD:
        astDecompile(node->son[0]);
        fprintf(out, "+");
        astDecompile(node->son[1]);
        break;
    case AST_SUB:
        astDecompile(node->son[0]);
        fprintf(out, "-");
        astDecompile(node->son[1]);
        break;
    case AST_MULT:
        astDecompile(node->son[0]);
        fprintf(out, "*");
        astDecompile(node->son[1]);
        break;
    case AST_DIV:
        astDecompile(node->son[0]);
        fprintf(out, "/");
        astDecompile(node->son[1]);
        break;
    case AST_AND:
        astDecompile(node->son[0]);
        fprintf(out, "&");
        astDecompile(node->son[1]);
        break;
    case AST_OR:
        astDecompile(node->son[0]);
        fprintf(out, "|");
        astDecompile(node->son[1]);
        break;
    case AST_GREATER:
        astDecompile(node->son[0]);
        fprintf(out, ">");
        astDecompile(node->son[1]);
        break;
    case AST_LESS:
        astDecompile(node->son[0]);
        fprintf(out, "<");
        astDecompile(node->son[1]);
        break;
    case AST_LE:
        astDecompile(node->son[0]);
        fprintf(out, "<=");
        astDecompile(node->son[1]);
        break;
    case AST_GE:
        astDecompile(node->son[0]);
        fprintf(out, ">=");
        astDecompile(node->son[1]);
        break;
    case AST_EQ:
        astDecompile(node->son[0]);
        fprintf(out, "==");
        astDecompile(node->son[1]);
        break;
    case AST_DIF:
        astDecompile(node->son[0]);
        fprintf(out, "!=");
        astDecompile(node->son[1]);
        break;
    case AST_LEXPR_CONT:
        fprintf(out, ",");
        astDecompile(node->son[0]);
        astDecompile(node->son[1]);
        break;
    case AST_CHAR:
        fprintf(out, "char");
        break;
    case AST_INT:
        fprintf(out, "int");
        break;
    case AST_FLOAT:
        fprintf(out, "float");
        break;
    case AST_DEC_VAR:
        astDecompile(node->son[0]);
        fprintf(out, ": %s =", node->symbol->text);
        astDecompile(node->son[1]);
        fprintf(out, ";\n");
        break;
    case AST_DEC_ARRAY:
        astDecompile(node->son[0]);
        fprintf(out, "[");
        astDecompile(node->son[1]);
        fprintf(out, "..");
        astDecompile(node->son[2]);
        fprintf(out, "]:%s", node->symbol->text);
        astDecompile(node->son[3]);
        fprintf(out,";\n");
        break;
    case AST_INIC_ARRAY:
        fprintf(out, "=");
        astDecompile(node->son[0]);
        astDecompile(node->son[1]);
        break;
    case AST_CONT_INIC_ARRAY:
        fprintf(out, " ");
        astDecompile(node->son[0]);
        astDecompile(node->son[1]);
        break;
    case AST_VEC_SIZE:
        fprintf(out, "%s", node->symbol->text);
        break;
    case AST_IF:
        fprintf(out,"if(");
        astDecompile(node->son[0]);
        fprintf(out,")  \n");
        astDecompile(node->son[1]);
        fprintf(out," ");
        break;
    case AST_IFE:
        fprintf(out,"if(");
        astDecompile(node->son[0]);
        fprintf(out,")  ");
        astDecompile(node->son[1]);
        fprintf(out," ");
        fprintf(out,"else\n");
        astDecompile(node->son[2]);
        break;
    case AST_UNTIL:
        fprintf(out,"until (");
        astDecompile(node->son[0]);
        fprintf(out,")  ");
        astDecompile(node->son[1]);
        fprintf(out," ");
        break;
    case AST_PRINT:
        fprintf(out,"print ");
        astDecompile(node->son[0]);
        break;
    case AST_PRINT_STRING:
        fprintf(out,"%s",node->symbol->text);
        astDecompile(node->son[0]);
        break;
    case AST_PRINT_PARAM:
        astDecompile(node->son[0]);
        astDecompile(node->son[1]);
        break;
    case AST_PRINT_STRING2:
        fprintf(out,", %s",node->symbol->text);
        astDecompile(node->son[0]);
        break;
    case AST_PRINT_PARAM2:
        fprintf(out,",");
        astDecompile(node->son[0]);
        astDecompile(node->son[1]);
        break;
    case AST_READ:
        fprintf(out,"read ");
        break;
    case AST_RETURN:
        fprintf(out,"return ");
        astDecompile(node->son[0]);
        break;
    case AST_COMEFROM:
        fprintf(out,"comefrom: ");
        fprintf(out,"%s", node->symbol->text);
        break;
    }  
}
//END OF FILE