#include <stdlib.h>
#include "stackNode.h"
#include "stack.h"


void push(StackNode** stack, char* data){
        StackNode* node  = makeStackNode(data, *stack);
        *stack = node;
}
char* top (StackNode* stack){
        if(emptyStack(stack)==0) {
                return stack->data;
        }
        exit(-1);
}
void pop(StackNode** stack){
        if(emptyStack(*stack)==0) {
                StackNode* node = *stack;
                *stack = (*stack)->next;
                free(node->data);
                free(node);
                return;
        }
        exit(-1);
}
int emptyStack(StackNode* stack){
      return stack==NULL;
}
