#include "symTbl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
static int number_of_symbols;
static Symbol symbol[MAX_SYMBOLS];
static Symbol createSymbol(Type type, char* varName, char* value);
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
void buildTable(char filename[]){
	if(filename==NULL){ //no filename, empty table.
return;
}
FILE *file=fopen(filename,"r");

if(file==NULL){
fprintf(stderr,"Error loading symbol table\n");
exit(EXIT_FAILURE);
}

int i=0;
while(i<MAX_SYMBOLS && !feof(file)){

char *typeToken=(char *)malloc(1024);
char *nameToken=(char *)malloc(1024);
char *valueToken=(char *)malloc(1024);

if(fscanf(file, "%s %s %s", typeToken, nameToken, valueToken)!=3){
break;
}


if(strcmp(typeToken,"int")==0){
Symbol nS=createSymbol(TYPE_INT, nameToken, valueToken);
symbol[i]=nS;
}else if(strcmp(typeToken,"double")==0){
Symbol nS=createSymbol(TYPE_DOUBLE, nameToken, valueToken);
symbol[i]=nS;
}

i++;
}
number_of_symbols=i;

fclose(file);

return;

}
void dumpTable(void){
								printf("SYMBOL TABLE:\n");
								for (int i=0; i<number_of_symbols; i++) {
																if(symbol[i].value.type==TYPE_INT) {
																								printf("Type int, Name: %s, Value: %d\n",symbol[i].varName,symbol[i].value.value.iVal);
																}
																if(symbol[i].value.type==TYPE_DOUBLE) {
																								printf("Type: double, Name: %s, Value: %f\n",symbol[i].varName, symbol[i].value.value.dVal);
																}
								}
}

Symbol* lookupTable(char variable[]){
								for(int i=0; i<number_of_symbols; i++) {
																if(strcmp(variable, symbol[i].varName)==0) {
																								return &symbol[i];
																}
								}
								return 0;
}
int addTable(Symbol symbol1){
								if (number_of_symbols<MAX_SYMBOLS) {
																symbol[number_of_symbols]=symbol1;
																number_of_symbols++;
																return number_of_symbols;
								}
								else{
																return 0;
								}
}
Symbol createSymbol(Type type, char* varName, char* value){
								struct Symbol temp;
								strcpy(temp.varName,varName);
								temp.value.type = type;
								if(type==TYPE_INT) {
																temp.value.value.iVal=str_to_int(value);

								}
								if(type==TYPE_DOUBLE) {
																temp.value.value.dVal = atof(value);
								}
								return temp;
}
