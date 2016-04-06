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
								if(filename==NULL) {
																return;
								}
								FILE *file = fopen(filename,"r");
								if (file==0) {
																printf("Error loading symbol table]n");
																exit(-1);
								}
								int counter=0;
								if (!feof(file)) {
																for(int i=0; i<MAX_SYMBOLS; i++) {
																								char *variable_type = (char *)calloc(1,1000);
																								char *variable_name = (char *)calloc(1,1000);
																								char *variable_value = (char *)calloc(1,1000);
																								if(fscanf(file, "%s %s %s", variable_type, variable_name, variable_value)!=3) {
																																printf("Invalid number of format o arguments");
																																break;
																								}
																								else{
																																if (strcmp(variable_type,"int")==0) {
																																								Symbol temp = createSymbol(TYPE_INT,variable_name,variable_value);
																																								symbol[counter] = temp;
																																}
																																if(strcmp(variable_type,"double")==0) {
																																								Symbol temp = createSymbol(TYPE_DOUBLE,variable_name,variable_value);
																																								symbol[counter]=temp;
																																}
																								}
																								counter++;
																}
								}
								number_of_symbols=counter;
								fclose(file);

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
