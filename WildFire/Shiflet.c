#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "display.h"
#include "helper.h"
#include "Shiflet.h"
void init_forest(int size,char forest[size][size]){
        for(int i=0; i<size; i++) {
                for(int j=0; j<size; j++) {
                        forest[i][j]='Y';
                }
        }

}
void apply_fire(int size,char arr[size][size],int density,int proportion){
  srand(time(NULL));
  int part_to_burn = (square(size)*density)/100,initial_ammount_burn=(part_to_burn*proportion)/100;
  int row = rand()%size;
  int col = rand()%size;
  while(arr[row][col]=='Y' || part_to_burn>0){
    if(arr[row][col]=='Y'){
      arr[row][col]= ' ';
      part_to_burn--;
    }
    else
    {
      row = rand()%size;
      col = rand()%size;
    }
  }
  while(arr[row][col]=='Y' || initial_ammount_burn>0){
    if(arr[row][col]=='Y'){
      arr[row][col]='*';
      initial_ammount_burn--;
    }else{
      row=rand()%size;
      col=rand()%size;
    }
  }

}
float calc_neighbors(int row,int col,char forest[row][col]){
        const int NEIGHBOR = 8;
        int trees_fire = 0,count = 0;
        if (row-1<0 || col-1 <0|| forest[row-1][col-1]==' ')
                count++;
        else if(forest[row-1][col-1]=='*')
                trees_fire++;
        if (row<0 || col-1<0 || forest[row][col-1]==' ')
                count++;
        else if(forest[row][col-1]=='*')
                trees_fire++;
        if(row+1<0 || col-1<0 || forest[row+1][col-1]==' ')
                count++;
        else if(forest[row+1][col-1]=='*')
                trees_fire++;
        if(row-1<0 || col<0 || forest[row-1][col]==' ')
                count++;
        else if(forest[row-1][col]=='*')
                trees_fire++;
        if(row+1<0 ||col<0 || forest[row+1][col]== ' ')
                count++;
        else if(forest[row+1][col]== '*')
                trees_fire++;
        if(row-1< 0 || col+1< 0 || forest[row-1][col+1] == ' ')
                count++;
        else if(forest[row-1][col+1] == '*')
                trees_fire++;
        if(row<0 || col+1< 0 || forest[row][col+1]== ' ')
                count++;
        else if(forest[row][col+1]== '*')
                trees_fire++;
        if(row+1<0 || col+1<0 || forest[row+1][col+1] == ' ')
                count++;
        else if(forest[row+1][col+1] == '*')
              trees_fire++;
        float total = (NEIGHBOR-count)/100;
        float percent = ((float)trees_fire/total);

}
int spread(int row,int col, char forest [row][col],double probability){
        if(calc_neighbors(row,col,forest)>26 && forest[row][col]=='Y') {
                return rand()%101 < probability ? 1 : 0;
        }
}

void apply_burn(int size,char forest[size][size],int arguments,int changes,double probability,double density,double proportion,int pn_option){
  int amount_of_changes = 0,cycles=0;
  if (arguments==5 ){


    while(count_trees(size,forest)>0){

        for(int i=0;i<size;i++){
          for(int j=0;j<size;j++){
            if(forest[i][j]=='*' && rand()%100<probability){
              forest[i][j]=' ';
              changes++;
            }
            if(spread(i,j,forest,probability)){
              forest[i][j]='*';
              changes++;
            }
          }
        }
        cycles++;
        amount_of_changes+=changes;
        print(size,forest);
        printf("cycles %i size %i probability %.2f density %.2f proportion %.2f changes %i \n", cycles, size, probability/100, density/100, proportion/100, changes);
        sleep(4);
    }
  }
    else if(arguments==6){
        print(size,forest);
      changes = 0;
      while(count_trees(size,forest)>0){
        for(int i=0;i<size;i++){
          for(int j=0;j<size;j++){
            if(forest[i][j]=='*' && rand()%100<probability){
              forest[i][j]='*';
              changes++;
            }
            if(spread(i,j,forest,probability)){
              forest[i][j]='*';
              changes++;
            }
          }
        }
        if(pn_option==0)
          break;
        pn_option--;
        cycles++;
        amount_of_changes+=changes;
        print(size,forest);
        printf("cycles %i size %i probability %.2f density %.2f proportion %.2f changes %i \n", cycles, size, probability/100, density/100, proportion/100, changes);
        sleep(4);
      }
    }

  }

int main(void){
  char arr[10][10];
  init_forest(10,arr);
  apply_fire(10,arr,50,50);
  apply_burn(10,arr,6,0,50,50,50,10);
}
