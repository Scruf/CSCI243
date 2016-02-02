#include <stdio.h>
/*
*@print_triangle(accept @param size)
* print the right angle triangle based on the size passed to a function
*/
void print_triangle(int size){
  //@param dest[] allocating size bytes of memory to an array of chars
  //@para []dest will be used as a placeholed to store '*'
    char dest[size];
    //filling the dest array with empty spaces
    for(int i=0;i<size;i++)
      dest[i]=' ';
    //assigninin a @size to a @counter so the size of the array could be used for printing
    int counter=size;
    //checking if the size of the array is even so as to know on how much the array will be
    //incremented
    if(size%2==0){
    //assigning a space to a last value in the array
      dest[--size]='*';
      //iterating over array and printing the values
      for(int i=0;i<counter;i++){
        printf("%c",dest[i]);
      }
      printf("\n");
      //@param first will hold the index of the next value where the '*' should be putted
      int first=0;
      //iterating over the size
      while(size>=0){
        //if the size is == 0 than while should be broken so as to prevent unecessary printing of
        //the array again
        if(size==0)
          break;
        first = size-1;
        dest[first]='*';
        //iterating over the array and printing the values
        for(int i=0;i<counter;i++)
          printf("%c",dest[i]);
        printf("\n");
        //decrementing the size of the array by as was said in the assignment
        size--;

      }


    }else{
      //otherwise the @size is odd
      dest[--size]='*';
      for(int i=0;i<counter;i++){
        printf("%c",dest[i]);
      }
      printf("\n");
      //@first,second will hold the indexes of where the start should be placed next
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
  print_triangle(1);
  print_triangle(5);
  print_triangle(7);
  return 0;
}
