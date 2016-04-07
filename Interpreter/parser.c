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
//insert node into a tree

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
/// Displays the infix expression for the tree, using
/// parentheses to indicate the precedence, e.g.:
///
/// expression: 10 20 + 30 *
/// infix string: ((10 + 20) * 30)
///
/// @precondition:  This routine should not be called if there
///   is a parser error.
void infixTree(ExpNode * node)
{

        switch(node->type) {
        case INTEGER:
                printf("%d",node->value.value.iVal);
                return;
        case DOUBLE:
                printf("%lf",node->value.value.dVal);
                return;
        case SYMBOL:
                printf("%s",node->symbol);
                return;
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
        case MOD_OP:
                printf("%%");
                break;
        case ASSIGN_OP:
                printf("=");
                break;
        default:
                break;
        }

        infixTree(node->right);
        printf(")");
}
/// Constructs the expression tree from the expression.  It
/// must use the stack to order the tokens.  It must also
/// deallocate the memory associated with the stack in all cases.
/// If a symbol is encountered, it should be stored in the node
/// without checking if it is in the symbol table - evaluation will
/// resolve that issue.
/// @param expr the postfix expression as a C string
/// @return the root of the expression tree
/// @exception There are 2 error conditions that you must deal
///   with.  In each case, the memory associated with the
///	tree must be cleaned up before returning.  Neither
///	stops execution of the program.
///
///	1. If there are too few tokens, set the parser error
///	to TOO_FEW_TOKENS and display the message to standard error:
///
///	Invalid expression, not enough tokens
///
///	2. If there are many tokens (stack is not empty after building),
///	set the parser error to TOO_MANY_TOKENS and display the message
///	to standard error:
///
///   Invalid expression, too many tokens
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


        if (emptyStack(stack) == 0) {
                printf("Invalid expression, too many tokens\n");
                parser = TOO_MANY_TOKENS;
                while(emptyStack(stack) == 0) {
                        pop(&stack);
                }
        }
        return newNode;
}
/// The main parse routine that handles the entire parsing
/// process, using the rest of the routines defined here.
/// @param exp The expression as a string
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
/// Evaluates the tree and returns the result.
/// @param node The node in the tree
/// @precondition:  This routine should not be called if there
///   is a parser error.
/// @return the evaluated value.  Note:  A symbol evaluates
///	to its stored value.
///
///	The evaluator needs to be able to deal with the multiple
///	types our interpreter supports (TYPE_INT and TYPE_DOUBLE).
///
///	1. If a symbol is not in the table, and the table isn't full
///	It should be added to the table taking on the type of the
///	rhs (right hand side) of the assignment.  Note that
///	a symbol will evaluate to its stored value (and type).
///
///	2. When performing the math operations (except for modulus),
///	the following rule applies.  If both lhs and rhs are int's,
///	the result is an int, otherwise the result is a double.
///
/// @exceptions There are 6 error conditions that can occur.  If
///	either occurs, set the correct parser error and display
///	an error message and return a Value of TYPE_UNKNOWN.   The main program
///	should check the parser error state before using the
///	return result.
///
/// 1. If a symbol is referenced on the left hand side during an
///   assignment, it should be added to the symbol table with
///   the value being the evaluation of the right hand side.  If
///   there is no more room in the symbol table, it should set
///   a SYMBOL_TABLE_FULL parser error and display the following
///   message to standard error
///
///   Symbol table full, cannot create new symbol
///
/// 2. An assignment is made to a left hand side expression
///	node that is not a symbol node.  It should set an
///	INVALID_ASSIGNMENT parser error and display the following
///	message to standard error:
///
///	Invalid assignment
///
/// 3. An assignment is made to a symbol with a value whose
///	type does not match the symbol's type (e.g. assigning
///	a double value to an int symbol).  It should set
///	an INVALID_ASSIGNMENT parser error, and display the following
///   message to standard error:
///
///	Assignment type mismatch
///
/// 4. If a math operation is being performed on a symbol that
///	that does not exist, you should set an UKNOWN_SYMBOL
///   parser error and display the following message to standard error
///     (where <symbol-name> is the name of the symbol):
///
///	Unknown symbol: <symbol-name>
///
/// 5. If modulus (%) is performed, both left and right hand side nodes
///	must be TYPE_INT.  If this happens, do not perform the operation,
///	instead set the parser error to INVALID_MODULUS and display
///   the following error to standard error:
///
///	Modulus requires both types to be int
///
/// 6. If division by zero (or modulus) is being performed, do not do it.
///     Instead set the parser error to DIVISION_BY_ZERO and display the
///	following error to standard error:
///
///	Division by zero
///
Value evalTree(ExpNode * node)
{

        Value unknown,left_value,right_value,result;
        Symbol *symb;
        unknown.type = TYPE_UNKNOWN;
        if(node==0) {
                return unknown;
        }
        //switch on a  node type and find out whether its Int double or symbol
        //if the symbol is unknowm the error will be thrown
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


                if (node->left->type != SYMBOL) {
                        parser = INVALID_ASSIGNMENT;
                        fprintf(stderr, "Invalid assignment\n");
                        return unknown;
                }


                Value rightValue = evalTree(node->right);
                if (rightValue.type == TYPE_UNKNOWN) {
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

                        if(addTable(temp)==0) {
                                parser = SYMBOL_TABLE_FULL;
                                printf("Symbol Table is full\n");
                                return unknown;
                        }
                        else{
                                return rightValue;
                        }
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


        left_value = evalTree(node->left);
        right_value = evalTree(node->right);


        if (left_value.type == TYPE_UNKNOWN) {
                return left_value;
        }
        else if (right_value.type == TYPE_UNKNOWN) {
                return right_value;
        }

        //switch on node type and perform arithmetic operations according
        //to the node type operator
        switch(node->type) {
          //addition
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



              //substraction
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
                //multiplication
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
                //division
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
                //modulus
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
                break;

        }
        return unknown;
}
ParserError getParserError(void){
    return parser;
}
