#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include "display.h"
#include "racer.h"
int str_to_int( char str_score[] ) {

        int value = 0;
        for ( int j = 0; str_score[j] != '\0'; ++j ) {

                if ( isdigit( str_score[j] ) ) {
                        value = value * 10 + (str_score[j] - '0');

                } else {
                        // stop on finding the first non-numeric digit.
                        break; // the value is not an integer.
                }
        }
        return value;
}

int main(int argc, char *argv[]){

  if (argc<=2){

    printf("Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]");
    exit(0);
  }
  if (argc>2){
    // char float_test [strlen(argv[1])+1];
    // strcpy(float_test,argv[1]);
    // for (int i=0;i<strlen(argv[1]);i++){
    //   printf("%c\n",float_test[i]);
    // }
    // if ((float_test[0]=='.' || float_test[1]=='.') && strlen(float_test)>1)
    //   printf("Its a float");
    // else
    //   printf("Its not a float");
    // int num=str_to_int(argv[1]);
    // printf("%d\n",num);
    for(int i=2;i<argc;i++){
        if (strlen(argv[i])<=6){
          printf("You are good to go my friend");
        }else{
          printf("Error: racer names must not exceed length 6.");
          exit(0)
        }
      }
  }


}
