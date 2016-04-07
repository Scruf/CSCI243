// #include "helper.h"
#include "stack.h"
#include "expNode.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


ParserError parser = NONE;

StackNode *stack = NULL;
ExpNode* insert(void) {
    ExpNode* current = NULL;
    if (emptyStack(stack)) {
        parser = TOO_FEW_TOKENS;
        printf("Invalid expression, not enough tokens\n");
        return current;
    }
    current = makeExpNode(top(stack), NULL, NULL);
    pop(&stack);

    if (current->type == INTEGER || current->type == DOUBLE || current->type == SYMBOL) {
    	return current;
    }

    current->right = insert();
    current->left = insert();
    return current;
}
void infixTree(ExpNode * node)
{
	if (node->type == INTEGER) {
		printf("%d", node->value.value.iVal);
		return;
	}

	if (node->type == DOUBLE) {
		printf("%f", node->value.value.dVal);
		return;
	}

	if (node->type == SYMBOL) {
		printf("%s", node->symbol);
		return;
	}

	printf("(");
	infixTree(node->left);
	if (node->type == ADD_OP) {
		printf(" + ");
	}
	else if (node->type == SUB_OP) {
		printf(" - ");
	}
	else if (node->type == MUL_OP) {
		printf(" * ");
	}
	else if (node->type == DIV_OP) {
		printf(" / ");
	}
	else if (node->type == MOD_OP) {
		printf("%s", " % ");
	}
	else if (node->type == ASSIGN_OP) {
		printf(" = ");
	}
	infixTree(node->right);
	printf(")");
}
ExpNode * parseTree(char expr[])
{
	char *token;
	token = strtok(expr, " ");

	ExpNode *newNode;

	while (token != NULL) {
		push(&stack, token);
	    token = strtok(NULL, " ");
	}

	newNode = insert();

	// If there are excess nodes, there were too many tokens.
	if (emptyStack(stack) == 0) {
		fprintf(stderr, "Invalid expression, too many tokens\n");
		parser = TOO_MANY_TOKENS;
		while(emptyStack(stack) == 0){
			pop(&stack);
		}
	}
	return newNode;
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
        return parser;
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
        if(node==0) {
                return unknown;
        }
        switch(node->type) {
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
                        parser = UNKNOWN_SYMBOL;
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
                        parser = INVALID_ASSIGNMENT;
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
                        if(symb->value.type!=rightValue.type) {
                                parser = INVALID_ASSIGNMENT;
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
        switch(node->type) {
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
                if(right_value.value.iVal == 0 || right_value.value.dVal==0) {
                        parser = DIVISION_BY_ZERO;
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
                if((left_value.type == TYPE_DOUBLE && right_value.type==TYPE_INT) || (left_value.type ==TYPE_INT && right_value.type==TYPE_DOUBLE) ) {
                        parser = INVALID_MODULUS;
                        printf("Modulus requires both types to be int\n");
                        return unknown;
                }
                if(right_value.value.iVal==0 || right_value.value.dVal == 0) {
                        parser == DIVISION_BY_ZERO;
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
