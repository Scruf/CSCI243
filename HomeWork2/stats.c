#include "stats.h"
double average(int count, const int scores[]){
  double temp=0.0;
  for(int i=0;i<count;i++){
    temp+=scores[i];
  }

  return temp;
}
