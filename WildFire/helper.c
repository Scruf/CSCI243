#include "helper.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


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
int get_pn_option(char arr[]){
        int value = 0;
        for ( int j = 2; arr[j] != '\0'; ++j ) {

                if ( isdigit( arr[j] ) ) {
                        value = value * 10 + (arr[j] - '0');

                } else {
                        // stop on finding the first non-numeric digit.
                        break; // the value is not an integer.
                }
        }
        return value;
}

int count_trees(int size,char arr[size][size]){
        int _burned_trees = 0;
        for(int i=0; i<size; i++) {
                for(int j=0; j<size; j++) {
                        if(arr[i][j]=='*')
                                _burned_trees++;
                }
        }
        return _burned_trees;
}

int square(int s){
  return s*s;
}
int check_pn_option(char arr[]){
        //check whether the first parameter is minus
        if(arr[0]!='-') {
                return 0;
        }
        //check whether the second argument is p
        if(arr[1]!='p') {
                return 0;
        }

        //check if the rest of arguments are integers
        else{
                for(int i=2; arr[i]!='\0'; ++i) {
                        if(arr[i]!=' ')
                                if(!isdigit(arr[i])) {
                                        return 0;
                                }
                }
                return 1;
        }
}

void print (int size, char arr[size][size]){
        for(int i=0; i<size; i++) {
                for(int j=0; j<size; j++) {
                        printf("%c",arr[i][j]);
                }
                printf("\n");
        }
}
