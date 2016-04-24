#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(char argc, char *argv[]){
  if(argc==1){
    printf("No file was specified");
    exit(1);
   }
  else{
    FILE *file;
    file = fopen(argv[1],"rb");
    if(file==0)
      printf("File does not exists");
    else{
      printf("File actually exists lol");
    }
  }
}
