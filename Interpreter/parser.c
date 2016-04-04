#include "helper.h"
#include "stack.h"
#include "expNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ParserError parser = NONE;
Symbol createSymbol(Type type, char* varName, char* value);
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
                printf("+");
                break;
        case SUB_OP:
                printf("-");
                break;
        case MUL_OP:
                printf("*");
                break;
        case DIV_OP:
                printf("/");
                break;
        case ASSIGN_OP:
                printf("=");
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
ParserError getParserError(void){
        return parser_error;
}
void cleanupTree(ExpNode* node){
        if(node==0) {
                return;
        }
        else{
                cleanupTree(node->left);
                free(node->left);
                cleanupTree(node->right);
                free(node->right);
        }
}
ExpNode* parserTree(char expr[]){
  StackNode *stack = NULL;
  char *tokens=NULL;
  ExpNode *current;
  char *str_to_copy = calloc(1,strlen(expr)+1);
  char  temp_str = calloc(1,10);
  memcpy(str_to_copy,expr,sizeof(strlen(expr+1)));
}

Value evalTree(ExpNode* node){
  switch(node->type){
    case INTEGER:
      return node->value;
      break;
    case DOUBLE:
      return node->value;
      break;
    case SYMBOL:
    Symbol *symb;
    if(symbol=lookupTable(node->symbol)){
      return symbol->value;
    break;
    default:
      parser_error = UNKNOWN_SYMBOL;
      printf("Unknown symbol: %s\n",node->symbol);
      return val;
    break;
    }
  }
}
