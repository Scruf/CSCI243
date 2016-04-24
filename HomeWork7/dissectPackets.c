#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<byteswap.h>

int main(char argc, char *argv[]){
  if(argc==1){
    printf("No file was specified");
    exit(1);
   }
  
  else{
    FILE *file;
    file = fopen(argv[1],"rb");
      size_t buffer_size = 2048;
      char *buffer;
      int num;
      fread(&num, sizeof(int),1,file);
      buffer = (char*)malloc(buffer_size);
      fread(buffer,sizeof(buffer_size),1,file);
      printf("%d",num);
      free(buffer);
      fclose(file);
   
      
    
  }
}
