#include <stdio.h>

void print_triangle(int size){
    char dest[size];
    for(int i=0;i<size;i++)
      dest[i]=' ';
    int counter=size;
    if(size%2==0){

      while(size>=0){
        if(size>=0){
          dest[size]='*';
          dest[--size]='*';
          for(int i=0;i<counter;i++)
            printf("%c",dest[i]);
        printf("\n");
        }
      }
    }
    while(size>=0){
    dest[size]='*';
      for(int i=0;i<counter;i++)
        printf("%c",dest[i]);
    printf("\n");
    size--;
    }
}


int main(){
  print_triangle(6);
  return 0;
}
