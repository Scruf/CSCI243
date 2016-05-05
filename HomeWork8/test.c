#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  char *name;
  char *back = "-->";
  char *random = "Bob";
  int size = strlen(back)+strlen(random);
  name = (char*)malloc(size);
  strncpy(name,back,strlen(back));
  size =strlen(name);
  strcat(name,random);
  printf("%c",name[strlen(name)-1]);

  return 0;
}
