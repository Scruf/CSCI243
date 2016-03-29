#include "stackNode.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
        StackNode* stack = NULL;
        push(&stack, "A");
        push(&stack, "B");
        push(&stack, "C");
        while(emptyStack(stack) == 0) {
                char* tk = top(stack);
                printf("%s\n", tk);
                pop(&stack);
        }
        return 0;
}
