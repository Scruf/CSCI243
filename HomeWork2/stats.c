#include "stats.h"
double average(int count,int scores[]){
  int temp=0;
  for(int i=0;i<count;i++){
    temp+=scores[i];
  }
  int av = count-1;
  return temp/av;
}
double std_dev(int count,int scores[],double mean){
  int sum=0;
  for(int i=0;i<count;i++){
    sum += (mean-scores[i])*(mean-scores[i]);
  }
  printf("%d\n",sum );

  return sum/count;
}
