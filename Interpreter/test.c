#include "stackNode.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
        int i = 0;
        double d = 0;
        char *token_type = (char *)malloc(sizeof(int)/2);

        printf("Woo %lu \n",sizeof(token_type));
        if (sizeof(token_type)==4)
          printf("\n Your are looking at int\n");
        return 0;
}
