#include <stdio.h>
#include <stdlib.h>
#include "symTbl.h"


int main(int argc,char* argv[]){
        if (argc==1)
        {
                buildTable(NULL);
        }
        else if(argc>1) {
                buildTable(argv[1])
        }
        else{
                printf("Ussage: interp [sym-table]\n");
                exit(-1);
        }
        dumpTable();
        char arr[MAX_LINE];
        printf("Enter postfix expressions (CTRL-D to exit): \n");
        for(;;){
          printf(">");
          fgets(arr,MAX_LINE,stdin);
          for(int j=0;j<strlen(arr)+1;j++){
            if(arr[j]=='\n'){
              arr[j]='\0';
            }
          }
          parse(arr);
          ParseError parse_error = getParserError();
        }
        return 0;
}
