
#include "tacs.h"

// IMPLEMENTATION

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2) {
    TAC* newtac = 0;
    newtac = (TAC*) calloc(1,sizeof(TAC));
    newtac->type = type;
    newtac->res = res;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->next = 0;
    newtac->prev = 0;
}
void tacPrint(TAC* tac) {
    if(!tac) return;
    if(tac->type == TAC_SYMBOL) return;

    fprintf(stderr, "TAC(");

    switch(tac->type) {
        case TAC_SYMBOL: fprintf(stderr,"TAC_SYMBOL"); break;
        case TAC_ADD: fprintf(stderr,"TAC_ADD"); break;
        case TAC_SUB: fprintf(stderr,"TAC_SUB"); break;
        case TAC_MULT: fprintf(stderr,"TAC_MULT"); break;
        case TAC_DIV: fprintf(stderr,"TAC_DIV"); break;
        case TAC_LESS: fprintf(stderr,"TAC_LESS"); break;
        case TAC_GREATER: fprintf(stderr,"TAC_GREATER"); break;
        case TAC_OR: fprintf(stderr,"TAC_OR"); break;
        case TAC_AND: fprintf(stderr,"TAC_AND"); break;
        case TAC_NOT: fprintf(stderr,"TAC_NOT"); break;
        case TAC_LE: fprintf(stderr,"TAC_LE"); break;
        case TAC_GE: fprintf(stderr,"TAC_GE"); break;
        case TAC_EQ: fprintf(stderr,"TAC_EQ"); break;
        case TAC_DIF: fprintf(stderr,"TAC_DIF"); break;
        case TAC_READ: fprintf(stderr,"TAC_READ"); break;
        case TAC_INIC_ARRAY: fprintf(stderr,"TAC_INIC_ARRAY"); break;
        case TAC_CONT_INIC_ARRAY: fprintf(stderr,"TAC_CONT_INIC_ARRAY"); break;
        case TAC_PRINT: fprintf(stderr,"TAC_PRINT"); break;
        case TAC_COMEFROM: fprintf(stderr,"TAC_COMEFROM"); break;
        case TAC_ASSIGN_ARRAY: fprintf(stderr,"TAC_ASSIGN_ARRAY"); break;
        case TAC_RETURN: fprintf(stderr,"TAC_RETURN"); break;
        case TAC_COPY: fprintf(stderr,"TAC_COPY"); break;
        case TAC_JFALSE: fprintf(stderr,"TAC_JFALSE"); break;
        case TAC_LABEL: fprintf(stderr,"TAC_LABEL"); break;
        case TAC_JUMP: fprintf(stderr,"TAC_JUMP"); break;
        case TAC_BEGIN_FUNC: fprintf(stderr,"TAC_BEGIN_FUNC"); break;
        case TAC_END_FUNC: fprintf(stderr,"TAC_END_FUNC"); break;
        case TAC_DATA: fprintf(stderr,"TAC_DATA"); break;
        case TAC_DEC_VAR: fprintf(stderr,"TAC_DEC_VAR"); break;
        case TAC_DEC_ARRAY: fprintf(stderr,"TAC_DEC_ARRAY"); break;
        case TAC_UNTIL: fprintf(stderr,"TAC_UNTIL"); break;
        
        default: fprintf(stderr,"TAC_UNKNOWN"); break;
    }

    fprintf(stderr,",%s", (tac->res) ? tac->res->text : "0");
    fprintf(stderr,",%s", (tac->op1) ? tac->op1->text : "0");
    fprintf(stderr,",%s", (tac->op2) ? tac->op2->text : "0");
    fprintf(stderr, ");\n");

}
void tacPrintBackwards(TAC* tac) {
    if(!tac)
        return;
    else {
        tacPrintBackwards(tac->prev);
        tacPrint(tac);
    }
}

TAC* tacJoin(TAC* l1, TAC* l2) {
    TAC *point;
    if(!l1) return l2;
    if(!l2) return l1;
    for(point = l2; point->prev != 0; point = point->prev)
        ;
    point->prev = l1;
    return l2;
}


// CODE GENERATION
TAC *makeBinOp(TAC* code[], int type);
TAC *makeIf(TAC* code0, TAC* code1, TAC* code2);
TAC* makeFunc(TAC* symbol, TAC* code1, TAC* code2);
TAC *makeUntil(TAC* code0, TAC* code1);

TAC* generateCode(AST *node) {
    int i;
    TAC *result = 0;
    TAC *code[MAX_SONS];

    if(!node) return 0;

    // PROCESS CHILDREN
    for(i=0; i<MAX_SONS; i++)
        code[i] = generateCode(node->son[i]);

    // PROCESS THIS NODE
    switch(node->type) {
        case AST_SYMBOL: result = tacCreate(TAC_SYMBOL,node->symbol,0,0); break;
        case AST_ADD: result = makeBinOp(code, TAC_ADD); break;
        case AST_SUB: result = makeBinOp(code, TAC_SUB); break;
        case AST_MULT: result = makeBinOp(code, TAC_MULT); break;
        case AST_DIV: result = makeBinOp(code, TAC_DIV); break;
        case AST_LESS: result = makeBinOp(code, TAC_LESS); break;
        case AST_GREATER: result = makeBinOp(code, TAC_GREATER); break;
        case AST_OR: result = makeBinOp(code, TAC_OR); break;
        case AST_AND: result = makeBinOp(code, TAC_AND); break;
        case AST_NOT: result = makeBinOp(code, TAC_NOT); break;
        case AST_LE: result = makeBinOp(code, TAC_LE); break;
        case AST_GE: result = makeBinOp(code, TAC_GE); break;
        case AST_EQ: result = makeBinOp(code, TAC_EQ); break;
        case AST_DIF: result = makeBinOp(code, TAC_DIF); break;
        case AST_INIC_ARRAY: result = makeBinOp(code, TAC_INIC_ARRAY); break;
        case AST_CONT_INIC_ARRAY: result = makeBinOp(code, TAC_CONT_INIC_ARRAY); break;

        case AST_ATTR: result = tacJoin(code[0],tacCreate(TAC_COPY,node->symbol,
            code[0] ? code[0]->res : 0,code[1] ? code[1]->res : 0)); break;
      	case AST_ASSIGN_ARRAY: result = tacJoin(tacJoin(code[0],code[1]),tacCreate(TAC_ASSIGN_ARRAY,
          node->symbol,code[1] ? code[1]->res : 0,code[0] ? code[0]->res : 0)); break;
        case AST_RETURN: result = tacJoin(code[0],tacCreate(TAC_RETURN,code[0]->res,0,0)); break;
        case AST_PRINT: return makeBinOp(code, TAC_PRINT);
        case AST_READ: result = tacCreate(TAC_READ,node->symbol,0,0);break;
        case AST_COMEFROM: return makeBinOp(code, TAC_COMEFROM);

        case AST_IF: return makeIf(code[0],code[1], code[2]);break;
        case AST_IFE: return makeIf(code[0], code[1], code[2]);break;
        case AST_FUNC: return makeFunc(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), code[1], code[2]);
        case AST_DATA: return makeFunc(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), code[0], code[1]);
        case AST_DEC_VAR: return tacJoin(code[1],tacCreate(TAC_COPY,node->symbol,code[1] ? code[1]->res : 0,code[2] ? code[2]->res : 0));break;
        case AST_DEC_ARRAY: return tacJoin(tacJoin(code[1],code[2]),tacCreate(TAC_COPY,node->symbol,code[1] ? code[1]->res : 0,code[2] ? code[2]->res : 0));break;
        case AST_UNTIL: return makeUntil(code[0],code[1]);break;

        default: result = tacJoin(code[0],tacJoin(code[1], tacJoin(code[2], code[3]))); break;
    }

    return result;
}

TAC *makeBinOp(TAC* code[], int type)
{
	return tacJoin(code[0],tacJoin(code[1],
    tacCreate(type,makeTemp(),code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0)));
}

TAC *makeIf(TAC* code0, TAC* code1, TAC* code2) {
    TAC *jumptac = 0;
    TAC *labeltac = 0;
    HASH_NODE *newlabel = 0;
    newlabel = makeLabel();

    jumptac = tacCreate(TAC_JFALSE,newlabel,code0 ? code0->res : 0,0);
    jumptac->prev = code0;
    labeltac = tacCreate(TAC_LABEL,newlabel,0,0);
    labeltac->prev = code1;

    if(code2) {
        TAC *jumptacelse = 0;
        TAC *labeltacelse = 0;
        HASH_NODE *newlabelelse = 0;
        newlabelelse = makeLabel();

        jumptacelse = tacCreate(TAC_JUMP,newlabelelse,0,0);
        jumptacelse->prev = 0;
        labeltacelse = tacCreate(TAC_LABEL,newlabelelse,0,0);
        labeltacelse->prev = code2;

        return tacJoin(tacJoin(tacJoin(jumptac,labeltac),jumptacelse),labeltacelse);
    } else {
        return tacJoin(jumptac,labeltac);
    }
}

TAC* makeFunc(TAC* symbol, TAC* code1, TAC* code2)
{
	return tacJoin(tacJoin(tacJoin( tacCreate(TAC_BEGIN_FUNC, symbol->res, 0, 0), code1) ,
     code2 ), tacCreate(TAC_END_FUNC, symbol->res, 0, 0));
}

TAC *makeUntil(TAC* code0, TAC* code1) {
    TAC *jumptac = 0;
    TAC *labeltac = 0;
    HASH_NODE *newlabel = 0;

    newlabel = makeLabel();

    jumptac = tacCreate(TAC_JFALSE,newlabel,code0 ? code0->res : 0,0);
    jumptac->prev = code0;
    labeltac = tacCreate(TAC_LABEL,newlabel,0,0);
    labeltac->prev = code1;

    TAC *jumptacuntil = 0;
    TAC *labeltacuntil = 0;
    HASH_NODE *newlabeluntil = 0;
    
    newlabeluntil = makeLabel();
    
    jumptacuntil = tacCreate(TAC_JUMP,newlabeluntil,0,0);
    jumptacuntil->prev = 0;
    labeltacuntil = tacCreate(TAC_LABEL,newlabeluntil,0,0);
    labeltacuntil->prev = 0;
    return tacJoin(tacJoin(tacJoin(jumptac,labeltac),jumptacuntil),labeltacuntil);
    
}