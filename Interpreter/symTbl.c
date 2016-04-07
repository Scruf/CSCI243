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
if(!feof(file)){
  for(;i<MAX_SYMBOLS;i++){
    char *token_type=calloc(1,1024);
    char *token_name=calloc(1,1024);
    char *token_value=calloc(1,1024);

    if(fscanf(file, "%s %s %s", token_type, token_name, token_value)!=3){
      break;
    }


    if(strcmp(token_type,"int")==0){
      Symbol int_symbol=createSymbol(TYPE_INT, token_name, token_value);
      symbol[i]=int_symbol;
    }else if(strcmp(token_type,"double")==0){
      Symbol double_symbol=createSymbol(TYPE_DOUBLE, token_name, token_value);
      symbol[i]=double_symbol;
    }
  }
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
