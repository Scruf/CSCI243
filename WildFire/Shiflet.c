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

void apply_burn(int size,char forest[size][size],int arguments,int changes,int probability,int density,int proportion){
  int amount_of_changes = 0,cycles=0;
  if (arguments==5){

  print(size,forest);
    while(count_trees(size,forest)>0){

        for(int i=0;i<size;i++){
          for(int j=0;j<size;j++){
            if(forest[i][j]=='*' && rand()%101<probability){
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
    }

  }
}
int main(void){
  char arr[10][10];
  init_forest(10,arr);


  apply_burn(10,arr,5,0,50,50,50);
}
