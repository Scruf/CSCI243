#include "stats.h"
#include <math.h>
#include <stdio.h>
double average(int count,const int scores[]){
  int temp=0;
  for(int i=0;i<count;i++){
    temp+=scores[i];
  }
  int av = count-1;
  return temp/av;
}
double std_dev(int count,const int scores[],double mean){
  double sum=0.0;
  for(int i=0;i<count;i++){
    if(scores[i]!=0){
    double res = scores[i]-mean;
    sum+=res*res;
    }
  }
  int av = count - 2;

  sum/=av;

  return sqrt(sum);
}
void histogram(int count , const int scores[]){

  int a=0,a_minus=0,b_plus=0,b=0,b_minus=0,c_plus=0,c=0,c_minus=0,d=0,f=0;
  for(int i=0;i<count;i++){
    if (scores[i] > 92)
			a++;
		else if (scores[i] >= 90 && scores[i] <= 92)
			a_minus++;

		else if (scores[i] < 90 && scores[i] >= 87)
			b_plus++;

		else if (scores[i] < 87 && scores[i] >= 83)
		    b++;

		else if (scores[i] < 83 && scores[i] >= 80)
			b_minus++;

		else if (scores[i] < 80 && scores[i] >= 77)
		    c_plus++;

		else if (scores[i] < 77 && scores[i] >= 73)
		    c++;

		else if (scores[i] < 73 && scores[i] >= 70)
		    c_minus++;

		else if (scores[i] < 70 && scores[i] >= 60)
	     d++;

		else if (scores[i] < 60 && scores[i] >= 0)
		    f++;
    else
      printf("Hello World" );
		}
  printf("A:  %d\n", a);
	printf("A-: %d\n", a_minus);
	printf("B+: %d\n", b_plus);
	printf("B:  %d\n", b);
	printf("B-: %d\n", b_minus);
	printf("C+: %d\n", c_plus);
	printf("C:  %d\n", c);
	printf("C-: %d\n", c_minus);
	printf("D:  %d\n", d);
	printf("F:  %d\n", f);

}
