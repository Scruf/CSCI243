#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expNode.h"

/// makeExpNode makes a new expression node
/// @param token the C string token in the expression
/// @param left node to the left, NULL if none
/// @param right node to the right NULL if none
/// @return the new node
ExpNode* makeExpNode(char token[], ExpNode* left, ExpNode* right) {
    ExpNode* newNode = malloc(sizeof(ExpNode));

    newNode->left = left;
    newNode->right = right;

    if (!strcmp(token, ADD_OP_STR)) {
        newNode->type = ADD_OP;
        return newNode;
    }
    if (!strcmp(token, SUB_OP_STR)) {
        newNode->type = SUB_OP;
        return newNode;
    }
    if (!strcmp(token, MUL_OP_STR)) {
        newNode->type = MUL_OP;
        return newNode;
    }
    if (!strcmp(token, DIV_OP_STR)) {
        newNode->type = DIV_OP;
        return newNode;
    }
    if (!strcmp(token, MOD_OP_STR)) {
        newNode->type = MOD_OP;
        return newNode;
    }
    if (!strcmp(token, ASSIGN_OP_STR)) {
        newNode->type = ASSIGN_OP;
        return newNode;
    }
    double d;
    if (sscanf(token, "%lf", &d) == 1 && strchr(token, '.') != NULL) {
                                 // token must contain '.' to be double,
                                 // else all integers would reach this code
        newNode->type = DOUBLE;
        newNode->value.type = TYPE_DOUBLE;
        newNode->value.value.dVal = d;
        return newNode;
    }
    int i;
    if (sscanf(token, "%d", &i) == 1) { // token is integer literal
        newNode->type = INTEGER;
        newNode->value.type = TYPE_INT;
        newNode->value.value.iVal = i;
        return newNode;
    }

    // token is symbol
    newNode->type = SYMBOL;
    strcpy(newNode->symbol, token);
    return newNode;
}
