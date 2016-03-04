#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
int count_tess (int size,char arr[size][size]){
  int _burned_trees = 0;
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      if(arr[i][j]=='*')
      _burned_trees++;
    }
  }
  return _burned_trees;
}
int count_changes(int size,char original[size][size],char to_compare[size][size]){
  int counter = 0;
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      if(original[i][j]!=to_compare[i][j])
        counter++;
    }
  }
  return counter;
}
void print(int size,char arr[size][size]){
  for(int i=0;i<size;i++)
  {
    for(int j=0;j<size;j++){
      printf("%c",arr[i][j]);
    }
    printf("\n");
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
unsigned int round_num(unsigned int x,unsigned int y){
  return (x + (y / 2)) / y;
}
//@function populate_forst will populate arr with
//a right characters
void populate_forst(int row,char arr[row][row],char tree){
  for(int i=0;i<sizeof(arr[0]);i++)
    for(int j=0;j<sizeof(arr[0]);j++)
      arr[i][j]=tree;
}
void burn_trees(int size, char matrix[size][size], int density, int proportionBurning) {

	srand ( time(NULL) );

	int part = (size * size * density) / 100;
	int initialBurn = (part * proportionBurning) / 100;
	int randRow = rand() % size;
	int randCol = rand() % size;

		while(matrix[randRow][randCol] == 'Y' || part > 0){

			if(matrix[randRow][randCol] == 'Y'){
				matrix[randRow][randCol] = ' ';
				part--;
			}
			else{
				randRow = rand() % (size);
				randCol = rand() % (size);
			}
		}

		while(matrix[randRow][randCol] == 'Y' || initialBurn > 0){

							if(matrix[randRow][randCol] == 'Y'){
								matrix[randRow][randCol] = '*';
								initialBurn--;
							}
							else{
								randRow = rand() % (size);
								randCol = rand() % (size);
							}
						}
}
void apply_spread(int size,char arr[size][size],char arr2[size][size]){
  for(int i=0;i<size;i++)
  {
    for(int j=0;j<size;j++){
      if(arr2[i][j]=='*')
        arr[i][j]='*';
      if(arr2[i][j]=='_')
        arr[i][j]='_';
    }
  }
}
void spread(int size, char arr[size][size], int probability){

	srand ( time(NULL) );
	int random_number = 0;

	int count = 0;
	char temp[size][size];
	//check bounds and neighbors
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++){

			count = 0;

			if(arr[i][j] == 'Y'){
				//NW
				if(i-1 >= 0 && j-1 >= 0){
					if(arr[i-1][j-1] == '*'){
						count++;
					}
				}
				//N
				if(i-1 >= 0){
					if(arr[i-1][j] == '*'){
						count++;
					}
				}
				//NE
				if(i-1 >= 0 && j+1 < size){
					if(arr[i-1][j+1] == '*'){
						count++;
					}
				}
				//W
				if(j-1 >= 0){
					if(arr[i][j-1] == '*'){
						count++;
					}
				}
				//E
				if(j+1 < size){
					if(arr[i][j+1] == '*'){
						count++;
					}
				}
				//SW
				if(i+1 < size && j-1 >= 0){
					if(arr[i+1][j-1] == '*'){
						count++;
					}
				}
				//S
				if(i+1 < size){
					if(arr[i+1][j] == '*'){
						count++;
					}
				}
				//SE
				if(i+1 < size && j+1 < size){
					if(arr[i+1][j+1] == '*'){
						count++;
					}
				}
				//see if tree will catch fire
				if(count >= 2){
					random_number = rand() % 100;
					if(random_number < probability){
						temp[i][j] = '*';
					}
				}
			}
			//if tree on fire, see if it will burn out
			if(arr[i][j] == '*'){
				random_number = rand() % 100;
				if(random_number < probability){
				temp[i][j] = '_';
				}
			}
		}
	}
	//apply changes after cycle has completed
	apply_spread(size, arr, temp);

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


int main(int argc, char *argv[]){
  char pN_option [sizeof(argv[1])];
  int cycles=0,size=0,probability=0,amount_of_burned_trees=0,treeDensity=0,burning_trees=0,count=0,number_cycles=0,number_of_changes=0;
  float _probability=0.0,_tree_density=0.0,initial_burning=0.0;
//if the amount of arguments is invalid than the progtram will display an error
      if(argc<5 || argc>6){
        printf("usage: wildfire [-pN] size probability treeDensity burning_trees\n");
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
          burning_trees = str_to_int(argv[5]);

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


        if(burning_trees<0 || burning_trees>101){
          printf("The proportion (X) must be an integer in [0...100].\n" );
            exit(0);
          }
          _probability = ((float)probability)/100;
          _tree_density = ((float)treeDensity)/100;
          initial_burning = ((float)burning_trees)/100;

          char forest[size][size];


          populate_forst(size,forest,'Y');
          burn_trees(size,forest,treeDensity,burning_trees);
          char trees_after_burn[size][size];
          for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
              trees_after_burn[i][j]=forest[i][j];
            }
          }

          int _count_burining_trees=count_tess(size,forest);
          printf("%d\n",_count_burining_trees);
           number_cycles = number_cycles + 1;
           while(_count_burining_trees>0){
             if(number_cycles==0)
               exit(0);
               _count_burining_trees=0;
               number_of_changes=0;
               print(size,forest);
               printf("\ncycles %d, size %d, probability %.2f, density %.2f, proportion %.2f,changes %d\n",cycles,size,_probability,_tree_density,burning_trees,number_of_changes);
               number_cycles--;
               spread(size,forest,_probability);
               _count_burining_trees=count_tess(sizeof(forest[0]),forest);
               cycles++;
               number_of_changes=count_changes(size,trees_after_burn,forest);
               amount_of_burned_trees+=number_of_changes;

               print(sizeof(forest[0]),forest);
               printf("\ncycles %d, size %d, probability %.2f, density %.2f, proportion %.2f,changes %d\n",cycles,size,_probability,_tree_density,burning_trees,number_of_changes);
           }


           for(int i=0;i<size;i++)
           {
             for(int j=0;j<size;j++)
             {
               printf("%c",forest[i][j]);
             }
             printf("\n");
           }


            }

    if(argc==5){
      size = str_to_int(argv[2]);
      probability = str_to_int(argv[3]);
      treeDensity = str_to_int(argv[4]);
      burning_trees = str_to_int(argv[5]);
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


      if(burning_trees<0 || burning_trees>101){
        printf("The proportion (X) must be an integer in [0...100].\n" );
          exit(0);
        }
    }
    // _probability = ((float)probability)/100;
    // _tree_density = ((float)treeDensity)/100;
    // initial_burning = ((float)burning_trees)/100;
    // int _count_burining_trees=0;
    // char forest[size][size];
    //
    //
    // if(treeDensity==0)
    //   populate_forst(sizeof(forest[0]),forest,' ');
    // else
    //   populate_forst(sizeof(forest[0]),forest,'Y');
    // burn_trees(sizeof(forest[0]),forest,treeDensity,burning_trees);
    // for(int i=0;i<size;i++)
    // {
    //   for(int j=0;j<size;j++)
    //   {
    //     if(forest[i][j]=='*')
    //       _count_burining_trees++;
    //   }
    // }
    //
    // for(int i=0;i<size;i++)
    // {
    //   for(int j=0;j<size;j++)
    //   {
    //     printf("%c",forest[i][j]);
    //   }
    //   printf("\n");
    // }

  }
