#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "stackNode.h"
StackNode* makeStackNode(char* data, StackNode* next){
  StackNode* node = malloc(sizeof(StackNode));
  node->data = malloc(strlen(data)+1);
  strcpy(node->data,data);
  node->next = next;
  return next;
}
