/*
 ============================================================================
 Name        : Project1_Wildfire.c
 Author      : Bernie Cecchini
 Version     :
 Copyright   : Your copyright notice
 Description : Forest fire simulation
 ============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


int str_to_int(char str_score[]) {
	int value = 0;
	for (int j = 0; str_score[j] != '\0'; ++j) {
		if (isdigit(str_score[j])) {
			value = value * 10 + (str_score[j] - '0');
		}
		else {
			// stop on finding the first non-numeric digit.
			break;   // the value is not an integer.
		}
	}
	return value;
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

void applyDensityandBurn(int size, char matrix[size][size], int density, int proportionBurning) {

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

void applySpread(int size, char matrix[size][size], char spread[size][size]){

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(spread[i][j] == '*'){
				matrix[i][j] = '*';
			}
			if(spread[i][j] == '_'){
				matrix[i][j] = '_';
			}
		}
	}
}

void spread(int size, char matrix[size][size], int probability){

	srand ( time(NULL) );
	int randNum = 0;

	int count = 0;
	char temp[size][size];

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++){

			count = 0;

			if(matrix[i][j] == 'Y'){
				//NW
				if(i-1 >= 0 && j-1 >= 0){
					if(matrix[i-1][j-1] == '*'){
						count++;
					}
				}
				//N
				if(i-1 >= 0){
					if(matrix[i-1][j] == '*'){
						count++;
					}
				}
				//NE
				if(i-1 >= 0 && j+1 < size){
					if(matrix[i-1][j+1] == '*'){
						count++;
					}
				}
				//W
				if(j-1 >= 0){
					if(matrix[i][j-1] == '*'){
						count++;
					}
				}
				//E
				if(j+1 < size){
					if(matrix[i][j+1] == '*'){
						count++;
					}
				}
				//SW
				if(i+1 < size && j-1 >= 0){
					if(matrix[i+1][j-1] == '*'){
						count++;
					}
				}
				//S
				if(i+1 < size){
					if(matrix[i+1][j] == '*'){
						count++;
					}
				}
				//SE
				if(i+1 < size && j+1 < size){
					if(matrix[i+1][j+1] == '*'){
						count++;
					}
				}
				if(count >= 2){
					randNum = rand() % 100;
					if(randNum < probability){
						temp[i][j] = '*';
					}
				}
			}
			if(matrix[i][j] == '*'){
				randNum = rand() % 100;
				if(randNum < probability){
				temp[i][j] = '_';
				}
			}
		}
	}

	applySpread(size, matrix, temp);

}

int main(int argc, char *argv[]) {

		int size;
		int probability, treeDensity, proportionBurning;
		float prob, treeDens, initialBurn;
		int results[argc];
		int count;
		int cycles = 0;
		int changes = 0;
		int totalChanges = 0;
		int n = 0;
		char pN [sizeof(argv[1])];

		if (argc < 5 || argc > 6 ) {
				printf("usage: wildfire [-pN] size probability treeDensity proportionBurning\n"
							"The -pN option tells the simulation to print N cycles and stop.\n"
							"The probability is the probability a tree will catch fire.\n");
				getchar();
				exit(-1);
		}
		if (argc == 6){
			strcpy(pN,argv[1]);
			int flag = check_pn_option(pN);
			size = str_to_int(argv[2]);
			probability = str_to_int(argv[3]);
			treeDensity = str_to_int(argv[4]);
			proportionBurning = str_to_int(argv[5]);

			if (flag == 0){
				printf("The -pN option was invalid.\n" );
				getchar();
				exit(-1);
			}
			else if(pN[2] == '-'){
				printf("The -pN option was negative.\n" );
				getchar();
				exit(-1);
			}
			else{
				n = get_pN(pN);
			}
			if(size > 40 || size < 5){
			    printf("The size (X) must be an integer in [5...40].\n");
			    getchar();
			    exit(-1);
			}
			else{
				size = str_to_int(argv[2]);
			}
			if(probability < 0 || probability > 100){
			    printf("The probability (X) must be an integer in [0...100].\n");
			    getchar();
				exit(-1);
			}
			else{
				probability = str_to_int(argv[3]);
			}
			if(treeDensity < 0 || treeDensity > 100){
			    printf("The density (X) must be an integer in [0...100].\n" );
			    getchar();
			    exit(-1);
			}
			else{
				treeDensity = str_to_int(argv[4]);
			}
			if(proportionBurning < 0 || proportionBurning > 100){
			    printf("The proportion (X) must be an integer in [0...100].\n" );
			    getchar();
			    exit(-1);
			}
			else{
				proportionBurning = str_to_int(argv[5]);
			}
		}
		if (argc == 5){
			size = str_to_int(argv[1]);
			probability = str_to_int(argv[2]);
			treeDensity = str_to_int(argv[3]);
			proportionBurning = str_to_int(argv[4]);
			if(size > 40 || size < 5){
			    printf("The size (X) must be an integer in [5...40].\n");
			    getchar();
			    exit(-1);
			}
			else{
				size = str_to_int(argv[1]);
			}
			if(probability < 0 || probability > 100){
			    printf("The probability (X) must be an integer in [0...100].\n");
			    getchar();
				exit(-1);
			}
			else{
				probability = str_to_int(argv[2]);
			}
			if(treeDensity < 0 || treeDensity > 100){
			    printf("The density (X) must be an integer in [0...100].\n" );
			    getchar();
			    exit(-1);
			}
			else{
				treeDensity = str_to_int(argv[3]);
			}
			if(proportionBurning < 0 || proportionBurning > 100){
			    printf("The proportion (X) must be an integer in [0...100].\n" );
			    getchar();
			    exit(-1);
			}
			else{
				proportionBurning = str_to_int(argv[4]);
			}
		}

		prob = ((double)probability) /100;
		treeDens = ((double)treeDensity) /100;
		initialBurn = ((double)proportionBurning) / 100;

		char grid[size][size];
		char temp[size][size];
		//populate forest with trees
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++) {
				grid[i][j] = 'Y';
			}
		}

		 applyDensityandBurn(size, grid, treeDensity, proportionBurning);

		 for(int i = 0; i < size; i++) {
		 	for(int j = 0; j < size; j++){
		 		if(grid[i][j] == '*'){
		 			count++;
		 		}
		 	}
		 }

		 for(int i = 0; i < size; i++) {
		 	for(int j = 0; j < size; j++){
		 		temp[i][j] = grid[i][j];
		 	}
		 }

		 if(argc == 6){
			 n = n+1;
			while(count > 0){

				if(n == 0){
					exit(-1);
				}
				 count = 0;
				 changes = 0;

				 for(int i = 0; i < size; i++){
					 for(int j = 0; j < size; j++){
						 printf("%c", grid[i][j]);
					 }
					 printf("\n");
				 }
				 printf("\n");
				 printf("cycles %d, size %d, probability %.2f, density %.2f, proportion %.2f, changes %d \n",
								 cycles, size, prob, treeDens, initialBurn, changes);
				 n--;

				 spread(size, grid, probability);

				 for(int i = 0; i < size; i++) {
					 for(int j = 0; j < size; j++){
						if(grid[i][j] == '*'){
							count++;
						}
					}
				 }
				 cycles++;

				 for(int i = 0; i < size; i++) {
					for(int j = 0; j < size; j++){
						if(grid[i][j] != temp[i][j]){
							changes++;
						}
					}
				 }
				 totalChanges += changes;
				 for(int i = 0; i < size; i++) {
					for(int j = 0; j < size; j++){
						temp[i][j] = grid[i][j];
					}
				 }
			 }
			 for(int i = 0; i < size; i++){
				 for(int j = 0; j < size; j++){
					 printf("%c", grid[i][j]);
				 }
				 printf("\n");
			 }
			 printf("\n");

			 printf("cycles %d, size %d, probability %.2f, density %.2f, proportion %.2f, changes %d \n",
					 cycles, size, prob, treeDens, initialBurn, changes);
		 }
		 if(argc == 5){
			 while(count > 0){

				 count = 0;
				 changes = 0;
				 spread(size, grid, probability);
				 for(int i = 0; i < size; i++) {
					 for(int j = 0; j < size; j++){
						if(grid[i][j] == '*'){
							count++;
						}
				 	}
				 }
				 cycles++;

				 for(int i = 0; i < size; i++) {
				 	for(int j = 0; j < size; j++){
				 		if(grid[i][j] != temp[i][j]){
				 			changes++;
				 		}
				 	}
				 }
				 totalChanges += changes;
				 for(int i = 0; i < size; i++) {
				 	for(int j = 0; j < size; j++){
				 		temp[i][j] = grid[i][j];
				 	}
				 }
			 }

		 for(int i = 0; i < size; i++){
			 for(int j = 0; j < size; j++){
				 printf("%c", grid[i][j]);
			 }
			 printf("\n");
		 }
		 printf("\n");

		 printf("cycles %d, size %d, probability %.2f, density %.2f, proportion %.2f, changes %d \n",
				 cycles, size, prob, treeDens, initialBurn, changes);
		 }

		 printf("fires are out after %d cumulative changes.\n", totalChanges);

	return 0;
}
