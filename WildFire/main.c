#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
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

int main(int argc, char *argv[]){
  int pN=0,size=0,probability=0,treeDensity=0,proportionBurning=0;
  if(argc<2)
    printf("usage: wildfire [-pN] size probability treeDensity proportionBurning");
    printf("The -pN option tells the simulation to print N cycles and stop.");
    printf("The probability is the probability a tree will catch fire.");

    if(str_to_int(argv[1])<5)
    {
      printf("The size (4) must be an integer in [5...40].");
      printf("usage: wildfire [-pN] size probability treeDensity proportionBurning");
      printf("The -pN option tells the simulation to print N cycles and stop.");
      printf("The probability is the probability a tree will catch fire.");
    }
    else{
      if(argc>4){
        pN=str_to_int(argv[1]);
        size = str_to_int(argv[2]);
        probability = str_to_int(argv[3]);
        treeDensity = str_to_int(argv[4]);
        proportionBurning = str_to_int(argv[5]);
      }
      else{
        size = str_to_int(argv[2]);
        probability = str_to_int(argv[3]);
        treeDensity = str_to_int(argv[4]);
        proportionBurning = str_to_int(argv[5]);
      }
      }

  }
