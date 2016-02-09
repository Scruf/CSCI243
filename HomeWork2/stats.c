#include "stats.h"
#include <math.h>
double average(int count,int scores[]){
  int temp=0;
  for(int i=0;i<count;i++){
    temp+=scores[i];
  }
  int av = count-1;
  return temp/av;
}
double std_dev(int count,int scores[],double mean){
  double sum=0.0;
  for(int i=0;i<count;i++){
    if(scores[i]!=0){
    double res = scores[i]-mean;
    sum+=res*res;
    }
  }
  int av = count - 2;

  sum/=av;
  printf("The value of the sum is %f\n",sum );
  return sqrt(sum);
}
