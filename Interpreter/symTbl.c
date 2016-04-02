#include "symblTbl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static int number_of_symbols;
static Symbol symbol[MAX_SYMBOLS];
void buildTable(char filename){
        FILE *file = fopen(filename,"r");
        if (file==0) {
                printf("Error loading symbol table]n");
                exit(-1);
        }
        int counter=0;
        while(counter<MAX_SYMBOLS && !feof(file)) {
                char *token_type = (char *)malloc(1024);
                char *token_name = (char *)malloc(1024);
                char *token_value = (char *)malloc(1024);
                if (fscanf(file),"%s %s %s",token_type,token_name,token_value!=3) {
                        printf("Invlid format or number of arguments");
                        break;
                }
                else{
                        if (strcmp(token_type,"int")==0) {
                                Symbol temp = createSymbol(TYPE_INT,token_name,token_value);
                                symbol[counter] = temp;
                        }
                        if(strcmp(token_type,"double")==0) {
                                Symbol temp = createSymbol(TYPE_DOUBLE,token_name,token_value);
                                symbol[counter]=temp;
                        }
                }
                counter++;
        }
        number_of_elements=counter;
        fclose(file);
        return;
}

void dumpTable(void){
        printf("SYMBOL TABLE:\n");
        for (int i=0; i<number_of_elements; i++) {
                if(symbol[i].value.type==TYPE_INT) {
                        printf("Type int, Name: %s, Value: %d\n",symbol[i].varName,symbol[i].value.value.iVal);
                }
                if(symbol[i].value.type==TYPE_DOUBLE) {
                        printf("Type: double, Name: %s, Value: %f\n",symbol[i].varName, symbol[i].value.value.dVal);
                }
        }
}

Symbol* lookupTable(char variable[]){
  for(int i=0;i<number)
}
