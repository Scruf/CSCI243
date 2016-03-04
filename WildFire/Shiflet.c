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
void apply_fire(int size,char arr[size][size],int density,float proportion){


  int part_on_fire = (square(size)*density)/100,
      emptyies=part_on_fire*proportion;
  int row = rand()%(size);
  int col = rand()%(size);
  for(int i=0;i<part_on_fire;){
    if(arr[row][col]=='Y')
      arr[row][col]='*';
    else{
      row = rand()%(size);
      col = rand()%(size);
      i++;
    }
  }
  for(int i=0;i<emptyies;){
    if(arr[row][col]=='Y'){
      arr[row][col]=' ';
    }
    else{
      row=rand()%(size);
      col=rand()%(size);
      i++;
    }
  }
}
static float calc_neighbors(int row,int col,char forest[row][col]){
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
static int spread(int row,int col, char forest [row][col],double probability){
        if(calc_neighbors(row,col,forest)>=25 && forest[row][col]=='Y') {
                return rand()%101 < probability ? 1 : 0;
        }
}

void apply_burn(int size,char forest[size][size],int arguments,int changes,float probability,float density,float proportion,int pn_option){
  int amount_of_changes = 0,cycles=0;

  if (arguments==5 ){


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
        printf("-------------------------------------------------------");
        sleep(4);
    }
  }
    else if(arguments==6){

      changes = 0;
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
        if(pn_option==0)
          break;
        pn_option--;
        cycles++;
        amount_of_changes+=changes;
        for(int i=0;i<size;i++){
          for(int j=0;j<size;j++){
            printf("%c",forest[i][j]);
          }
          printf("\n");
        }

        printf("cycles %i size %i probability %.2f density %.2f proportion %.2f changes %i \n", cycles, size, probability, density, proportion, changes);
        printf("-------------------------------------------------------\n");
        sleep(4);
      }
    }

  }
