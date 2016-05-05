#include "display.h"
#include "racer.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void initRacers(long milliseconds);
Racer *makeRacer(char *name, int position);
void destroyRacer(Racer *racer);
void *run(void *racer);


static int MAX_WAIT_TIME = DEFAULT_WAIT;
void initRacers(long milliseconds){
  if (milliseconds!=0){
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




  racer->dist = 0;
  racer->row = position;
}
void destroyRacer(Racer *racer){
  free(racer->graphic);
  free(racer);
}
 void *run(void *racer){
   Racer * race = (Racer * )racer;

   set_cur_pos(race->row, race->dist);

   int wait;
   clear();

   while(race->dist < FINISH_LINE - MAX_NAME_LEN / 2){
     set_cur_pos(race->row, race->dist - 1);
     put(' ');

     //random wait time
     wait = rand() % MAX_WAIT_TIME;

     //check to see if a racer gets a flat tire
     if (wait < 3){
       //add the flat tire
       race->graphic[1] = 'X';

       int j = 0;
       //print out the racer witht the flat tire
       while (j < MAX_CAR_LEN){
         set_cur_pos(race->row, race->dist + j);
         put(race->graphic[j]);
         j++;
       }
       //exit becasue the racer is out of the race
       pthread_exit(NULL);
     }

     //print out a racer if they don't have a flat tire
     int c = 0;
     while (c < MAX_CAR_LEN){
       set_cur_pos(race->row, race->dist + c);
       put(race->graphic[c]);
       c++;
     }

     usleep(wait * 1000);
     race->dist++;
     set_cur_pos(race->row, race->dist);
   }
   pthread_exit(NULL);
 }
