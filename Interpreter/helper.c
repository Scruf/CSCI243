#include "helper.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int str_to_int( char str_score[] ) {

        int value = 0;
        for ( int j = 0; str_score[j] != '\0'; ++j ) {

                if ( isdigit( str_score[j] ) ) {
                        value = value * 10 + (str_score[j] - '0');

                }
                else {
                        // stop on finding the first non-numeric digit.
                        break; // the value is not an integer.
                }
        }
        return value;
}
