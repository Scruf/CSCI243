#include "display.h"
#include "helper.h"
#include "Shiflet.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>
int main(int argc, char *argv[]){
  int cycles=0,size=0,probability=0,density=0,proportion=0;
  float _probability = 0.0,_density=0.0,_proportion=0.0;

  if (argc<5 || argc>7){

    fprintf(stderr,"usage: wildfire [-pN] size probability treeDensity proportionBurning\n"
      "The -pN option tells the simulation to print N cycles and stop.\n"
      "The probability is the probability a tree will catch fire.\n");
      exit(0);
  }else{
    size = str_to_int(argv[2]);
    probability = str_to_int(argv[3]);
    density = str_to_int(argv[4]);
    proportion = str_to_int(argv[5]);
    _probability = ((float)probability)/100;
    _density=((float)density)/100;
    _proportion = ((float)proportion)/100;
  }
  if(argc==6){
      char pn_option[sizeof(argv[1])];
      strcpy(pn_option,argv[1]);
      int flag = check_pn_option(pn_option);

      if(flag==0){
        printf("-pN option is Invalid");

        exit(0);
      }
      if(size>40 || size<5){
        printf("The size (X) must be an integer in [5...40].\n");
        exit(0);
      }
      if(probability < 0 || probability > 100){
			    printf("The probability (X) must be an integer in [0...100].\n");
          exit(0);
        }
        if(density < 0 || density > 100){
  			    printf("The density (X) must be an integer in [0...100].\n" );
            exit(0);
          }
          if(proportion<0 || proportion>100){
             printf("The proportion (X) must be an integer in [0...100].\n" );
             exit(0);
          }
      cycles = get_pn_option(pn_option);
      char forest[size][size];
      init_forest(size,forest);
      apply_fire(size,forest,density,_proportion);
      apply_burn(size,forest,6,0,_probability,_density,_proportion,cycles);

  }
  if(argc==5){

      if(size>40 || size<5){
        printf("The size (X) must be an integer in [5...40].\n");
        exit(0);
      }
      if(probability < 0 || probability > 100){
          printf("The probability (X) must be an integer in [0...100].\n");
          exit(0);
        }
        if(density < 0 || density > 100){
            printf("The density (X) must be an integer in [0...100].\n" );
            exit(0);
          }
          if(proportion<0 || proportion>100){
             printf("The proportion (X) must be an integer in [0...100].\n" );
             exit(0);
          }
      
      char forest[size][size];
      init_forest(size,forest);
      apply_fire(size,forest,density,_proportion);
      apply_burn(size,forest,6,0,_probability,_density,_proportion,0);

  }

}
