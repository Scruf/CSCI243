/// pt-cruisers.c - a driver for initiating the race
/// @author bpc2189@rit.edu
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "display.h"
#include "racer.h"


int main(int argc, char * argv[]){

  int flag = 0;

	int maxTime = atoi(argv[1]);
	if (flag!=0 ){
		initRacers((long)maxTime);
		flag = 1;
	}
	//first arg was not an int
	if (flag == 0){
		if(argc < 3){
			printf("Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
			exit(0);
		}
	}
	//first arg was an int
	if (flag == 1){
		if (argc < 3){
			printf("Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
			exit(0);
		}
	}

	Racer * racers[argc - flag - 1];

	int i = 1 + flag;
	while (i < argc){
		racers[i - flag - 1] = makeRacer(argv[i], i - flag);
		i++;
	}

	srand(42);

	int num_racers = argc - flag - 1;
	pthread_t threads[num_racers];
	void *retval;

	for (int t = 0; t < num_racers; t++){
		pthread_create(&threads[t], NULL, run, racers[t]);
	}

	for (int t = 0; t < num_racers; t++){
		pthread_join(threads[t], &retval);
	}

	set_cur_pos(num_racers + 1, 0);

	return(0);
}
