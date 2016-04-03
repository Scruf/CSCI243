#include "helper.h"
#include "stack.h"
#include "expNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ParserError parser = NONE;
void infixTree(ExpNode* node){
        switch(node->type) {
        case DOUBLE:
                printf("%f",node->value.value.dVal);
                return;
                break;
        case INTEGER:
                printf("%d",node->value.value.iVal);
                return;
                break;
        case SYMBOL:
                printf("%s",node->symbol);
                break;
        default:
                break;
        }
        printf("(");
        infixTree(node->left);
        switch(node->type) {
        case ADD_OP:
                printf(ADD_OP);
                break;
        case SUB_OP:
                printf(SUB_OP);
                break;
        case MUL_OP:
                printf(MUL_OP);
                break;
        case DIV_OP:
                printf(DIV_OP);
                break;
        case ASSIGN_OP:
                printf(ASSIGN_OP);
                break;
        case MOD_OP:
                printf(" %% ");
                break;
        default:
                break;
        }
        infixTree(node->right);
        printf(")");

}
void parse(char exp[]){
        ExpNode *root = parseTree(exp);
        Value val = evalTree(root);
        if(parser==NONE) {
                infixTree(root);
                printf("%s",ASSIGN_OP_STR);
                if(val.type==TYPE_INT)
                        printf("%d\n",val.value.iVal);
                if(val.type==TYPE_DOUBLE)
                        printf("%f\n",val.value.dVal);
        }
        cleanupTree(root);
}
