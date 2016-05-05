/*
   ===========================================================================
   Name        : dissectPackets.c
   Author      : Egor Kozitski
   Version     :
   Copyright   : Your copyright notice
   Description :
   ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "display.h"
#include "racer.h"

/// main - driver function
///
/// @param argc - number of arguments
/// @param argv[] - arguments
///
int main(int argc, char * argv[]){
  if(argc < 2 )
  {
    printf("Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
    exit(0);
  }
  if (atoi(argv[1]) && argc < 4){
    printf("Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
    exit(0);
  }
  int time = 0;
  if (!atoi(argv[1]) && argc<2){
    printf("Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
    exit(0);
  }
  if (atoi(argv[1]) && argc >2){
    for(int i=2;i<argc;i++){
      if(strlen(argv[i])>=6){
         printf("Error: racer names must not exceed length 6.\n");
         exit(0);
      }
    }
  }
  if(!atoi(argv[1])&& argc>2){
    for(int i=1;i<argc;i++){
      if(strlen(argv[i])>=6){
        printf("Error: racer names must not exceed length 6.\n");
        exit(0);
      }
    }
  }

  int duration = atoi(argv[1]);
	//if it is an int
	if (duration != 0){
		initRacers((long)duration);
		time = 1;
	}
	//first arg was not an int



	Racer * racers[argc - time - 1];

	int i = 1 + time;
	while (i < argc){
		racers[i - time - 1] = makeRacer(argv[i], i - time);
		i++;
	}

	srand(42);

	int number_of_racers = argc - time - 1;
	pthread_t threads[number_of_racers];
	void *retval;

	for (int t = 0; t < number_of_racers; t++){
		pthread_create(&threads[t], NULL, run, racers[t]);
	}

	for (int t = 0; t < number_of_racers; t++){
		pthread_join(threads[t], &retval);
	}

	set_cur_pos(number_of_racers + 1, 0);

	return(0);
}
