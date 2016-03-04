#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include <string.h>
void populate_forst(int row,char arr[row][row],char tree){
  for(int i=0;i<sizeof(arr[0]);i++)
    for(int j=0;j<sizeof(arr[0]);j++)
      arr[i][j]=tree;
}
int check_pn_option(char arr[]){
  //check whether the first parameter is minus
  if(arr[0]!='-'){
    return 0;
  }
  //check whether the second argument is p
  if(arr[1]!='p'){
    return 0;
  }

  //check if the rest of arguments are integers
  else{
    for(int i=2;arr[i]!='\0';++i){
      if(arr[i]!=' ')
        if(!isdigit(arr[i])){
          return 0;
        }
      }
    return 1;
  }
}
int get_pN(char arr[]){
  int value = 0;
  for ( int j = 2; arr[j] != '\0'; ++j ) {

     if ( isdigit( arr[j] ) ) {
        value = value * 10 + (arr[j] - '0');

     } else {
        // stop on finding the first non-numeric digit.
        break;   // the value is not an integer.
     }
  }
  return value;
}
int str_to_int( char str_score[] ) {

   int value = 0;
   for ( int j = 0; str_score[j] != '\0'; ++j ) {

      if ( isdigit( str_score[j] ) ) {
         value = value * 10 + (str_score[j] - '0');

      } else {
         // stop on finding the first non-numeric digit.
         break;   // the value is not an integer.
      }
   }
   return value;
}

int main(int argc, char *argv[]){
  char pN_option [sizeof(argv[1])];
  int size=0,probability=0,treeDensity=0,proportionBurning=0,count=0,number_cycles=0,number_changes=0;
  float _probability=0.0,_tree_density=0.0,initial_burning=0.0;
//if the amount of arguments is invalid than the progtram will display an error
      if(argc<5 || argc>6){
        printf("usage: wildfire [-pN] size probability treeDensity proportionBurning\n");
        printf("The -pN option tells the simulation to print N cycles and stop.\n");
        printf("The probability is the probability a tree will catch fire.");
        exit(0);
    }
//if ammount of arguments is 6 than pN option was present
      if(argc==6){
        strcpy(pN_option,argv[1]);
        int flag =check_pn_option(pN_option);
        if (flag==0){
            printf("The -pN option was invalid.\n" );
            exit(0);
        }

        if(pN_option[2]=='-'){
          printf("The -pN option was negative.\n" );
          exit(0);
        }else{
          number_cycles=get_pN(pN_option);
        }

          size = str_to_int(argv[2]);
          probability = str_to_int(argv[3]);
          treeDensity = str_to_int(argv[4]);
          proportionBurning = str_to_int(argv[5]);

        if(size>40 || size<=4){
            printf("The size (X) must be an integer in [5...40].\n");
            exit(0);
        }



        if(probability<0 || probability>101){
            printf("The probability (X) must be an integer in [0...100].\n");
            exit(0);
        }



        if(treeDensity<0 || treeDensity>101){
            printf("The density (X) must be an integer in [0...100].\n" );
            exit(0);
        }


        if(proportionBurning<0 || proportionBurning>101){
          printf("The proportion (X) must be an integer in [0...100].\n" );
            exit(0);
          }



      }

    if(argc==5){
      size = str_to_int(argv[2]);
      probability = str_to_int(argv[3]);
      treeDensity = str_to_int(argv[4]);
      proportionBurning = str_to_int(argv[5]);
      if(size>40 || size<=4){
          printf("The size (X) must be an integer in [5...40].\n");
          exit(0);
      }



      if(probability<0 || probability>101){
          printf("The probability (X) must be an integer in [0...100].\n");
          exit(0);
      }



      if(treeDensity<0 || treeDensity>101){
          printf("The density (X) must be an integer in [0...100].\n" );
          exit(0);
      }


      if(proportionBurning<0 || proportionBurning>101){
        printf("The proportion (X) must be an integer in [0...100].\n" );
          exit(0);
        }
    }
    _probability = ((float)probability)/100;
    _tree_density = ((float)treeDensity)/100;
    initial_burning = ((float)proportionBurning)/100;
    char forest[size][size];


    if(treeDensity==0)
      populate_forst(sizeof(forest[0]),forest,' ');
    else
      populate_forst(sizeof(forest[0]),forest,'Y');
    for(int i=0;i<size;i++)
    {
      for(int j=0;j<size;j++)
      {
        printf("%c",forest[i][j]);
      }
      printf("\n");
    }

  }
