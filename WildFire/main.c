#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include <string.h>
int check_pn_option(char arr[]){
  //check whether the first parameter is minus
  if(arr[0]!='-'){
    return 0;
  }
  //check whether the second argument is p
  if(arr[1]!='p'){
    return 0;
  }

  //check if the rest of arguments are integers
  else{
    for(int i=2;arr[i]!='\0';++i){
      if(arr[i]!=' ')
        if(!isdigit(arr[i])){
          return 0;
        }
      }
    return 1;
  }
}
int get_pN(char arr[]){
  int value = 0;
  for ( int j = 2; arr[j] != '\0'; ++j ) {

     if ( isdigit( arr[j] ) ) {
        value = value * 10 + (arr[j] - '0');

     } else {
        // stop on finding the first non-numeric digit.
        break;   // the value is not an integer.
     }
  }
  return value;
}
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
  char pN [sizeof(argv[1])];
  int size=0,probability=0,treeDensity=0,proportionBurning=0;
      if(argc<2){
        printf("usage: wildfire [-pN] size probability treeDensity proportionBurning\n");
        printf("The -pN option tells the simulation to print N cycles and stop.\n");
        printf("The probability is the probability a tree will catch fire.");
    }

      if(argc>4){
        strcpy(pN,argv[1]);
        int flag =check_pn_option(pN);
        if (flag==0)
          printf("The -pN option was invalid.\n" );
        if(pN[2]=='-')
          printf("The -pN option was negative.\n" );
        size = str_to_int(argv[2]);
        if(size>40 || size<=4)
          printf("The size (X) must be an integer in [5...40].\n");
        probability = str_to_int(argv[3]);
        if(probability<0 || probability>101)
          printf("The probability (X) must be an integer in [0...100].\n");
        treeDensity = str_to_int(argv[4]);
        if(treeDensity<0 || treeDensity>101)
          printf("The density (X) must be an integer in [0...100].\n" );
        proportionBurning = str_to_int(argv[5]);
        if(proportionBurning<0 || proportionBurning>101)
          printf("The proportion (X) must be an integer in [0...100].\n" );
        printf("%d\n",get_pN(pN));
      }
      else{
        size = str_to_int(argv[2]);
        probability = str_to_int(argv[3]);
        treeDensity = str_to_int(argv[4]);
        proportionBurning = str_to_int(argv[5]);
      }


  }
