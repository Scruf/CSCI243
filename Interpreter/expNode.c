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
  ExpNode *current = (ExpNode *)calloc(1,sizeof(ExpNode));

  current->left = left;
  current->right = right;
  if (check_if_double(token)==1) {
          current->type = DOUBLE;
          current->value.value.dVal = atof(token);
  }
  int flag = 0;
  for(int i=0; i<strlen(token)+1; i++) {
          if (isdigit(token[i])==0) {
                  flag = 1;
          }
  }
  if (flag==1) {
          current->type = INTEGER;
          current->value.value.iVal = str_to_int(token);
  }

  if(strcmp(token,ADD_OP_STR)==0)
          current->type=ADD_OP;
  else if(strcmp(token,SUB_OP_STR)==0)
          current->type = SUB_OP;
  else if(strcmp(token,MUL_OP_STR)==0)
          current->type = MUL_OP;
  else if(strcmp(token,DIV_OP_STR)==0)
          current->type = DIV_OP;
  else if(strcmp(token,MOD_OP_STR)==0)
          current->type=MOD_OP;
  else if(strcmp(token,ASSIGN_OP_STR)==0)
          current->type = ASSIGN_OP;
  else{
          current->type = SYMBOL;
          strcpy(current->symbol,token);
  }
  return current;
}
