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
 // Construct an expression node dynamically on the heap.
 // Assume the following order when determining which
 // type to create:
 //	1. the operators
 //  	2. literal
 //	3. integer literal
 //	4. symbol
 // @param token The next C string token in the expression
 // @param left Pointer to left node (NULL if none)
 // @param right Pointer to right node (NULL if none)
 // @return The new node
ExpNode* makeExpNode(char token[],ExpNode*left, ExpNode* right){
  ExpNode *current = (ExpNode *)calloc(1,sizeof(ExpNode));

  current->left = left;
  current->right = right;


  for(int i=0;i<=strlen(token+1);i++){
    if(token[i]=='.'){
      current->type=DOUBLE;
      current->value.type=TYPE_DOUBLE;
      current->value.value.dVal = atof(token);
      return current;
    }
  }

  int i;
  if (sscanf(token, "%d", &i) == 1) { // token is integer literal
      current->type = INTEGER;
      current->value.type = TYPE_INT;
      current->value.value.iVal = i;
      return current;
  }


  if(strcmp(token,ADD_OP_STR)==0) {
          current->type=ADD_OP;
          return current;
  }

  else if(strcmp(token,SUB_OP_STR)==0)
  {
          current->type = SUB_OP;
          return current;
  }

  else if(strcmp(token,MUL_OP_STR)==0) {
          current->type = MUL_OP;
          return current;
  }

  else if(strcmp(token,DIV_OP_STR)==0) {
          current->type = DIV_OP;
          return current;
  }

  else if(strcmp(token,MOD_OP_STR)==0) {
          current->type=MOD_OP;
          return current;
  }
  else if(strcmp(token,ASSIGN_OP_STR)==0) {
          current->type = ASSIGN_OP;
          return current;
  }
  else{
    current->type = SYMBOL;
    strcpy(current->symbol,token);
    return current;
  }

}
