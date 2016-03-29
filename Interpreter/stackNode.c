#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stackNode.h"

StackNode* makeStackNode(char* data, StackNode* next) {
        StackNode* node = malloc(sizeof(StackNode));
        node->next = next;
        node->data = malloc(sizeof(data) + 1);
        strcpy(node->data, data);
        return node;
}
