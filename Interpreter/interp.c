#include "stackNode.h"
#include "stack.h"
#include "symTbl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interp.h"
#include "parser.h"


int main(int argc,char* argv[]){
        if (argc==1)
        {
                buildTable(NULL);
        }
        else if(argc>1) {
                buildTable(argv[1]);
        }
        else{
                printf("Ussage: interp [sym-table]\n");
                exit(-1);
        }
        dumpTable();
        char arr[MAX_LINE];
        printf("Enter postfix expressions (CTRL-D to exit): \n");
        for(;; ) {
                printf(">");
                fgets(arr,MAX_LINE,stdin);
                for(int j=0; j<strlen(arr)+1; j++) {
                        if(arr[j]=='\n') {
                                arr[j]='\0';
                        }
                }
                parse(arr);
                ParserError parse = getParserError();
        }
        return 0;
}
