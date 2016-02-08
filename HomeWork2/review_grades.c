#include <stdio.h>
#include "stats.h"
#include<ctype.h>
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
  const int* scores[argc];
  int current=1;
  for(int i=0;i<argc;i++){
    int digit = str_to_int(argv[++i]);
    scores[i]=digit;
    current++;
  }
  int population = argc - 1;
  double average_score = average(population,scores);
  printf("%f\n",average_score );


  return 0;
}
