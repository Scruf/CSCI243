#include <stdio.h>
#include "stats.h"
#include<ctype.h>
#include <stdlib.h>
#include <math.h>
int str_to_int( char str_score[] ) {

   int value = 0;
   for ( int j = 0; str_score[j] != '\0'; ++j ) {

      if ( isdigit( str_score[j] ) ) {
         value = value * 10 + (str_score[j] - '0');

      } else {
         // stop on finding the first non-numeric digit.
         break;   // the value is not an integer.
      }
   }
   return value;
}
int main(int argc, char *argv[]) {
  int population = argc - 1;
  int result[argc];
  int current=1;
  for(int i=0;i<argc;i++){
    if(current<argc){
      int digit = str_to_int(argv[current]);
      result[i]=digit;
      current++;
    }
  }
  double average_score = average(argc,result);
  double mean_score = std_dev(argc,result,average_score);
  printf("population: %d\n",population);
  for(int i=0;i<argc;i++){
    if(result[i]!=0)
      printf("%d ",result[i]);
  }
  printf("\n");
  printf("mean: %f\n",average_score );
  printf("std deviation: %f\n",mean_score);
  return 0;


}
