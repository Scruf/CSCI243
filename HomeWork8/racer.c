#include "display.h"
#include "racer.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define MAX_WAIT_TIME : DEFAULT_WAIT;
void initRacers(long milliseconds);
Racer *makeRacer(char *name, int position);
void destroyRacer(Racer *racer);
void *run(void *racer);



void initRacers(long milliseconds){
  if (!milliseconds){
    MAX_WAIT_TIME=milliseconds;
  }
}


Racer *makeRacer( char *name,int position){
    Racer *racer = calloc(1,sizeof(Racer));
    racer->graphic = calloc(MAX_NAME_LEN+1,sizeof(char));

}
