#include "stats.h"


double average(int count ,const int []scores){
  double average = 0;
  for(int i=0;i<count;i++)
    average+=scores[i];
  return average/count;
}
