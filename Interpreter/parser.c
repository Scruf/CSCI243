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

Value evalTree(ExpNode * node)
{
	//Value leftValue = evalTree(node->left);
	//Value rightValue = evalTree(node->right);
	// Create the empty unknown Value in case of an error.
	Value unknown,left_value,right_value,result;
	Symbol *symb;
  unknown.type = TYPE_UNKNOWN;
  if(node==0){
    return unknown;
  }
  switch(node->type){
    case INTEGER:
      return node->value;
      break;
    case DOUBLE:
      return node->value;
      break;
case SYMBOL:
	symb = lookupTable(node->symbol);
	if(symb!=0)
		return symb->value;
	else{
	parserError = UNKNOWN_SYMBOL;
	printf("Unknown symbol: %s\n",node->symbol);
	return unknown;
}
break;
    default:
    break;

  }



	// Assignment
	if (node->type == ASSIGN_OP) {

		// Check if the left side is a symbol
		if (node->left->type != SYMBOL) {
			parserError = INVALID_ASSIGNMENT;
			fprintf(stderr, "Invalid assignment\n");
			return unknown;
		}

		// Get the right value and make sure the types match the left value:
		//Value rightValue = evalTree(node->right);
		Value rightValue = evalTree(node->right);
		if (rightValue.type == TYPE_UNKNOWN) { //Return the unknown value if there was a problem with the expression
			return rightValue;
		}

		if(lookupTable(node->left->symbol)==0)
          {
            struct Symbol temp;
            memcpy(temp.varName,node->left->symbol,sizeof(node->left->symbol));
            temp.value.type = rightValue.type;
            if(rightValue.type == TYPE_INT)
              temp.value.value.iVal = node->right->value.value.iVal;
            if(rightValue.type == TYPE_DOUBLE)
              temp.value.value.dVal = node->right->value.value.dVal;
            addTable(temp);
            return rightValue;
          }
		else {

			  symb = lookupTable(node->left->symbol);
            if(symb->value.type!=rightValue.type){
              parserError = INVALID_ASSIGNMENT;
              printf("Assignment type mismatch\n");
              return unknown;
            }
            if(symb->value.type==TYPE_INT)
              symb->value.value.iVal = rightValue.value.iVal;
            else
              symb->value.value.dVal = rightValue.value.dVal;
            return rightValue;
		}
	}

	// Can get both values since were not doing assignment.
	left_value = evalTree(node->left);
	right_value = evalTree(node->right);

	//Divide by zero, invalid symbol, etc. Just need to keep passing it up.
	if (left_value.type == TYPE_UNKNOWN) {
		return left_value;
	}
	else if (right_value.type == TYPE_UNKNOWN) {
		return right_value;
	}

	// Addition
	switch(node->type){
		case ADD_OP:
			  if(left_value.type == TYPE_INT && right_value.type==TYPE_INT)
                {
                        result.type = TYPE_INT;
                        result.value.iVal = left_value.value.iVal + right_value.value.iVal;
                }
                if(left_value.type == TYPE_DOUBLE && right_value.type == TYPE_DOUBLE)
                {
                        result.type = TYPE_DOUBLE;
                        result.value.dVal = left_value.value.dVal + right_value.value.dVal;
                }
                if(left_value.type == TYPE_DOUBLE && right_value.type == TYPE_INT) {
                        result.type = TYPE_DOUBLE;
                        result.value.dVal = left_value.value.dVal + right_value.value.iVal;
                }
                if(left_value.type == TYPE_INT && right_value.type == TYPE_DOUBLE) {
                        result.type = TYPE_DOUBLE;
                        result.value.dVal = left_value.value.iVal + right_value.value.dVal;
                }
                return result;
	break;




	  case SUB_OP:
                if(left_value.type == TYPE_INT && right_value.type==TYPE_INT)
                {
                        result.type = TYPE_INT;
                        result.value.iVal = left_value.value.iVal - right_value.value.iVal;
                }
                if(left_value.type == TYPE_DOUBLE && right_value.type == TYPE_DOUBLE)
                {
                        result.type = TYPE_DOUBLE;
                        result.value.dVal = left_value.value.dVal - right_value.value.dVal;
                }
                if(left_value.type == TYPE_DOUBLE && right_value.type == TYPE_INT) {
                        result.type = TYPE_DOUBLE;
                        result.value.dVal = left_value.value.dVal - right_value.value.iVal;
                }
                     if(left_value.type == TYPE_INT && right_value.type == TYPE_DOUBLE) {
                        result.type = TYPE_DOUBLE;
                        result.value.dVal = left_value.value.iVal - right_value.value.dVal;
                }
                return result;
                break;
        case MUL_OP:
                if(left_value.type == TYPE_INT && right_value.type==TYPE_INT)
                {
                        result.type = TYPE_INT;
                        result.value.iVal = left_value.value.iVal * right_value.value.iVal;
                }
                if(left_value.type == TYPE_DOUBLE && right_value.type == TYPE_DOUBLE)
                {
                        result.type = TYPE_DOUBLE;
                        result.value.dVal = left_value.value.dVal * right_value.value.dVal;
                }
                if(left_value.type == TYPE_DOUBLE && right_value.type == TYPE_INT) {
                        result.type = TYPE_DOUBLE;
                        result.value.dVal = left_value.value.dVal * right_value.value.iVal;
                }
                      if(left_value.type == TYPE_INT && right_value.type == TYPE_DOUBLE) {
                        result.type = TYPE_DOUBLE;
                        result.value.dVal = left_value.value.iVal * right_value.value.dVal;
                }
                return result;
                break;
       case DIV_OP:
          if(right_value.value.iVal == 0 || right_value.value.dVal==0){
            parserError = DIVISION_BY_ZERO;
            printf("Division by zero\n");
            return unknown;
          }
          if(left_value.type == TYPE_INT && right_value.type==TYPE_INT)
          {
                  result.type = TYPE_INT;
                  result.value.iVal = left_value.value.iVal / right_value.value.iVal;
          }
          if(left_value.type == TYPE_DOUBLE && right_value.type == TYPE_DOUBLE)
          {
                  result.type = TYPE_DOUBLE;
                  result.value.dVal = left_value.value.dVal / right_value.value.dVal;
          }
          if(left_value.type == TYPE_DOUBLE && right_value.type == TYPE_INT) {
                  result.type = TYPE_DOUBLE;
                  result.value.dVal = left_value.value.dVal / right_value.value.iVal;
          }
                if(left_value.type == TYPE_INT && right_value.type == TYPE_DOUBLE) {
                  result.type = TYPE_DOUBLE;
                  result.value.dVal = left_value.value.iVal / right_value.value.dVal;
          }
          return result;
          break;
      case MOD_OP:
        if((left_value.type == TYPE_DOUBLE && right_value.type==TYPE_INT) || (left_value.type ==TYPE_INT && right_value.type==TYPE_DOUBLE) ){
            parserError = INVALID_MODULUS;
            printf("Modulus requires both types to be int\n");
            return unknown;
        }
        if(right_value.value.iVal==0 || right_value.value.dVal == 0){
          parserError == DIVISION_BY_ZERO;
          printf("Division by zero\n");
          return unknown;
        }
        else{
          result.type = TYPE_INT;
          result.value.iVal = left_value.value.iVal % right_value.value.iVal;
          return result;
        }
        default:
        return unknown;
                break;

        }
}
