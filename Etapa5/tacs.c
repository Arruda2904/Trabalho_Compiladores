
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
    fprintf(stderr, "TAC(");

    switch(tac->type) {
        case TAC_SYMBOL: fprintf(stderr,"TAC_SYMBOL"); break;
        case TAC_ADD: fprintf(stderr,"TAC_ADD"); break;
        case TAC_SUB: fprintf(stderr,"TAC_SUB"); break;
        default: fprintf(stderr,"TAC_UNKNOWN"); break;
    }

    fprintf(stderr,",%s", (tac->res) ? tac->res->text : "0");
    fprintf(stderr,",%s", (tac->op1) ? tac->op1->text : "0");
    fprintf(stderr,",%s", (tac->op2) ? tac->op2->text : "0");
    fprintf(stderr, ");\n");

}
void tacPrintBackwards(TAC* tac) {

}

// CODE GENERATION

TAC* generateCode(AST *node) {

}