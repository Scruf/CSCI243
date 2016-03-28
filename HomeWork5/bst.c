#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "bst.h"
int str_to_int( char str_score[] ) {

        int value = 0;
        for ( int j = 0; str_score[j] != '\0'; ++j ) {

                if ( isdigit( str_score[j] ) ) {
                        value = value * 10 + (str_score[j] - '0');

                }
                else if(str_score[j]=='-'){
                  continue;
                }
                else {
                        // stop on finding the first non-numeric digit.
                        break; // the value is not an integer.
                }
        }
        return value;
}
int main(int argc, char *argv[]){
        if (argc<2) {
                printf("Usage: bst #");
                exit(-1);
        }
        int number_of_elements=0;


      //  check if the number is negative
        char temp[sizeof(argv[1])];
        strcpy(temp,argv[1]);
        if (temp[0]=='-')
        {
          number_of_elements=str_to_int(temp)*(-1);

        }
        else {
          number_of_elements=str_to_int(argv[1]);
        }
        if(number_of_elements<=0){
          printf ("%d must be greater than 0",number_of_elements);
        }

        // else
        //         number_of_elements= str_to_int(argv[1]);
        // printf("%d number is  0",number_of_elements);
        // if(number_of_elements<=0){
        //   printf("%d must be greater than 0",number_of_elements);
        //   exit(-1);
        // }
        return 0;
}
