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
  racer->graphic = (char*)malloc(strlen(name));


  int back_size = 0;

  char *back = "~0=";
  strncpy(racer->graphic,back,strlen(back)+1);
  strcat(racer->graphic ,name);
  back_size = strlen(racer->graphic);

  int remaining = MAX_CAR_LEN - back_size;
  char *front;

  front = (char*)malloc(remaining);
  for(int x=0;x<remaining-3;x++)
    front[x]='-';
  char *rest = "o>";
  strcat(front,rest);
  strcat(racer->graphic,front);

   printf("%s\n",front);



  racer->dist = 0;
  racer->row = position;



}
