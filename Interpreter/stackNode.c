#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stackNode.h"

StackNode* makeStackNode(char* data, StackNode* next) {
        StackNode* node = calloc(1,sizeof(StackNode));
        node->next = next;
        node->data = calloc(1,sizeof(data) + 1);
        strcpy(node->data, data);
        return node;
}
