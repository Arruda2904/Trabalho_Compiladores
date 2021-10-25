#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_COPY 4
#define TAC_JFALSE 5
#define TAC_LABEL 6
#define TAC_MULT 7
#define TAC_DIV 8
#define TAC_LESS 9
#define TAC_GREATER 10
#define TAC_OR 11
#define TAC_AND 12
#define TAC_NOT 13
#define TAC_LE 14
#define TAC_GE 15
#define TAC_EQ 16
#define TAC_DIF 17
#define TAC_ASSIGN_ARRAY 18 
#define TAC_RETURN 19
#define TAC_READ 20
#define TAC_JUMP 21
#define TAC_BEGIN_FUNC 22
#define TAC_END_FUNC 23
#define TAC_INIC_ARRAY 24
#define TAC_CONT_INIC_ARRAY 25
#define TAC_PRINT 26
#define TAC_COMEFROM 27
#define TAC_DATA 28
#define TAC_DEC_VAR 29
#define TAC_DEC_ARRAY 30


typedef struct tac_node {
    int type;
    HASH_NODE * res;
    HASH_NODE * op1;
    HASH_NODE * op2;
    struct tac_node* prev;
    struct tac_node* next;
} TAC;

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC* tac);
TAC* tacJoin(TAC* l1, TAC* l2);

// CODE GENERATION

TAC* generateCode(AST *node);

#endif