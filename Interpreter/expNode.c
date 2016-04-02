#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "helper.h"
#include "expNode.h"
#include "symTbl.h"

/*
   ADD_OP_STR	"+"
   SUB_OP_STR	"-"
   MUL_OP_STR	"*"
   DIV_OP_STR	"/"
   MOD_OP_STR	"%"
   ASSIGN_OP_STR	"="

 */

ExpNode* makeExpNode(char token[],ExpNode*left, ExpNode* right){
        ExpNode *current = (ExpNode *)calloc(1,sizeof(ExpNode)){
                current->left = left;
                current->right = right;
                if (check_if_double(token)==1) {
                        current->type = DOUBLE;
                        current->value.value.dVal = atof(token);
                }
                int flag = 0;
                for(int i=0; i<strrlen(token)+1; i++) {
                        if (isdigit(token[i])==0) {
                                flag = 1;
                        }
                }
                if (flag==1) {
                        current->type = INTEGER;
                        curren->value.value.iVal = str_to_int(token);
                }
                switch(token) {
                case ADD_OP_STR:
                        current->type=ADD_OP;
                        break;
                case SUB_OP_STR:
                        current->type = SUB_OP;
                        break;
                case MUL_OP_STR:
                        current->type = MUL_OP;
                        break;
                case DIV_OP_STR:
                        current->type = DIV_OP;
                        break;
                case MOD_OP_STR:
                        current->type=MOD_OP;
                        break;
                case ASSIGN_OP_STR:
                        current->type = ASSIGN_OP;
                        break;
                default:
                        current->type = SYMBOL;
                        strcpy(current->symbol,token);
                        break;
                }
        }
        return current;
}
