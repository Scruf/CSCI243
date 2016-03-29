#include "stackNode.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  StackNode* stack = NULL;
  printf("Pushing");
  push(&stack, "A");
  push(&stack, "B");
  push(&stack, "C");
  printf("%d is stack empty",emptyStack(stack));
  while(emptyStack(stack) == 0) {
    char* tk = top(stack);
    printf("%s\n", tk);
    pop(&stack);
  }
  return EXIT_SUCCESS;
}
