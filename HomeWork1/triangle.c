#include <stdio.h>

void print_triangle(int size){
    char dest[size];
    for(int i=0;i<size;i++)
      dest[i]=' ';
    int counter=size;
  
    if(size%2==1){
      dest[--size]='*';
      for(int i=0;i<counter;i++){
        printf("%c",dest[i]);
      }
      printf("\n");
      int first,second=0;
      while(size>=0){
          if(size==0)
            break;
          first = size - 1;
          second = size - 2;
          dest[first]='*';
          dest[second]='*';

          for(int i=0;i<counter;i++){
            printf("%c",dest[i]);
          }
          printf("\n");
          size = size - 2;
        }

    }
}
int main(){
  print_triangle(7);
  return 0;
}
